#include "stdafx.h"
#include "Play.h"

using namespace std;

//----------------------------------------------------------------------------

static void CALLBACK waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	((CPlay*)dwInstance)->waveOutProc(hWaveOut, uMsg, dwParam1, dwParam2);
}

//----------------------------------------------------------------------------

void CPlay::MainThread()
{
	double dCurrentTime = 0;
	double dTimeStep = 1.0 / (double)m_iSampleRate;

	short* pshBlockOfMemory = nullptr;
	WAVEHDR* pWaveHeaders = nullptr;

	wstring wstrText;
	MMRESULT mmResult = MMSYSERR_NOERROR;

	try
	{
		mmResult = waveOutOpen(&m_hwDevice, m_iOutputDevice, &m_wfFormat, (DWORD_PTR)waveOutProcWrap, (DWORD_PTR)this, CALLBACK_FUNCTION);
		if (mmResult != MMSYSERR_NOERROR)
		{
			throw false;
		}

		pshBlockOfMemory = new short[m_iBlocks*m_iBlockSample];
		if (pshBlockOfMemory == nullptr)
		{
			wstrText = NO_MEMORY;
			throw false;
		}
		ZeroMemory(pshBlockOfMemory, sizeof(short) * m_iBlocks * m_iBlockSample);

		pWaveHeaders = new WAVEHDR[m_iBlocks];
		if (pWaveHeaders == nullptr)
		{
			wstrText = NO_MEMORY;
			throw false;
		}
		ZeroMemory(pWaveHeaders, sizeof(WAVEHDR) * m_iBlocks);

		for (unsigned int n = 0; n < (unsigned int)m_iBlocks; n++)
		{
			pWaveHeaders[n].dwBufferLength = m_iBlockSample * sizeof(short);
			pWaveHeaders[n].lpData = (LPSTR)(pshBlockOfMemory + (n * m_iBlockSample));
		}

		m_pNotePlayer->SetStartTime();

		while (m_bPlay)
		{
			if (m_iBlockFree == 0)
			{
				unique_lock<mutex> lm(m_muxBlockNotZero);
				m_cvBlockNotZero.wait(lm);
			}

			m_iBlockFree--;

			mmResult = pWaveHeaders[m_iBlockCurrent].dwFlags;
			if (mmResult & WHDR_PREPARED)
			{
				mmResult = waveOutUnprepareHeader(m_hwDevice, &pWaveHeaders[m_iBlockCurrent], sizeof(WAVEHDR));
				if (mmResult != MMSYSERR_NOERROR)
				{
					throw false;
				}
			}

			short nNewSample = 0;
			int nCurrentBlock = m_iBlockCurrent * m_iBlockSample;

			for (unsigned int n = 0; n < (unsigned int)m_iBlockSample; n++)
			{
				nNewSample += (short)(m_pNotePlayer->Sound(dCurrentTime) * MAX_SAMPLE);
				pshBlockOfMemory[nCurrentBlock + n] = nNewSample;

				if (m_wfFormat.nChannels == 2 && n % (m_wfFormat.nChannels / 2) == 0)
				{
					n++;
					pshBlockOfMemory[nCurrentBlock + n] = nNewSample;
				}

				dCurrentTime += dTimeStep;
				nNewSample = 0;
			}

			mmResult = waveOutPrepareHeader(m_hwDevice, &pWaveHeaders[m_iBlockCurrent], sizeof(WAVEHDR));
			if (mmResult != MMSYSERR_NOERROR)
			{
				throw false;
			}
			mmResult = waveOutWrite(m_hwDevice, &pWaveHeaders[m_iBlockCurrent], sizeof(WAVEHDR));
			if(mmResult != MMSYSERR_NOERROR)
			{
				throw false;
			}

			m_iBlockCurrent++;
			m_iBlockCurrent %= m_iBlocks;
		}
	}
	catch(bool){}

	m_iBlockCurrent = 0;

	mmResult = waveOutReset(m_hwDevice);

	for (unsigned int n = 0; n < (unsigned int)m_iBlocks; n++)
	{
		mmResult = waveOutUnprepareHeader(m_hwDevice, &pWaveHeaders[n], sizeof(WAVEHDR));
	}

	mmResult = waveOutClose(m_hwDevice);
	m_hwDevice = NULL;
		
	if (pshBlockOfMemory != 0)
	{
		delete[] pshBlockOfMemory;
	}
	if (pWaveHeaders != 0)
	{
		delete[] pWaveHeaders;
	}

	if (mmResult != MMSYSERR_NOERROR)
	{
		wchar_t Text[MAX_PATH + 1] = L"";
		midiInGetErrorText(mmResult, Text, MAX_PATH);
		wstrText = Text;
	}
	if (wstrText.empty() == false)
	{
		AfxMessageBox(wstrText.c_str(), MB_OK | MB_ICONWARNING);
		::PostMessage(*m_phWndParent, WMUSER_ERROR, 0, 0);
	}
}

//----------------------------------------------------------------------------

void CPlay::waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwParam1, DWORD dwParam2)
{
	if (uMsg != WOM_DONE) return;

	m_iBlockFree++;
	unique_lock<mutex> lm(m_muxBlockNotZero);
	m_cvBlockNotZero.notify_one();
}

//----------------------------------------------------------------------------

void CPlay::Start()
{
	Stop();
	m_bPlay = true;
	m_thread = thread(&CPlay::MainThread, this);
}

//----------------------------------------------------------------------------

CPlay::CPlay(shared_ptr<CNotePlayer> pNotePlayer, HWND* hwndParent)
{
	m_pNotePlayer = pNotePlayer;
	shared_ptr<CPlayParams> pPlayParams = CPlayParams::Instance();

	pPlayParams->Attach(this);

	sPlayParams playParams = pPlayParams->GetPlayParams();
	SetPlayParams(playParams);

	m_bPlay = false;

	m_iBlockCurrent = 0;

	m_phWndParent = hwndParent;
}

//----------------------------------------------------------------------------

CPlay::~CPlay()
{
	Stop();

	shared_ptr<CPlayParams> pPlayParams = CPlayParams::Instance();

	pPlayParams->Detach(this);
}

//----------------------------------------------------------------------------

void CPlay::Stop()
{
	m_bPlay = false;
	if(m_thread.joinable())
	{
		m_thread.join();
	}
	m_pNotePlayer->Stop();
}

//----------------------------------------------------------------------------

void CPlay::SetPlayParams(sPlayParams playParams)
{
	m_iBlocks = playParams.iBlocks;
	m_iBlockSample = playParams.iBlockSample;
	m_iChannel = playParams.iChannel;
	m_iSampleRate = playParams.iSampleRate;
	m_iOutputDevice = playParams.iDeviceNumber;

	m_iBlockFree = m_iBlocks;

	WAVEFORMATEX waveFormat;
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = m_iSampleRate;
	waveFormat.wBitsPerSample = m_iBlocks;
	waveFormat.nChannels = m_iChannel;
	waveFormat.nBlockAlign = waveFormat.wBitsPerSample / 8 * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	::ZeroMemory(&m_wfFormat, sizeof(WAVEFORMATEX));
	m_wfFormat = waveFormat;
}

//----------------------------------------------------------------------------

void CPlay::Update(CSubject * theChangedSubject)
{
	sPlayParams playParams = static_cast<CPlayParams*>(theChangedSubject)->GetPlayParams();
	SetPlayParams(playParams);
}

//----------------------------------------------------------------------------

bool CPlay::IsPlay()
{
	return m_bPlay;
}

//----------------------------------------------------------------------------