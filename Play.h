#pragma once

#include <vector>
#include <string>
#include <mmeapi.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "PlayParams.h"
#include "NotePlayer.h"

using namespace std;

class CNotePlayer;

class CPlay : public CObserver
{
public:
	CPlay(shared_ptr<CNotePlayer> pNotePlayer, HWND* hwndParent);
	~CPlay();
	void Start();

	void Stop();
	void waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwParam1, DWORD dwParam2);

	void Update(CSubject* theChangedSubject);

	bool IsPlay();

private:
	void SetPlayParams(sPlayParams playParams);
	void MainThread();

	int m_iOutputDevice;
	int m_iSampleRate;
	int m_iChannel;
	int m_iBlocks;
	int m_iBlockSample;
	int m_iBlockCurrent;
	int m_iBlockFree;
	HWAVEOUT m_hwDevice;
	
	bool m_bPlay;

	thread m_thread;
	mutex m_muxBlockNotZero;
	condition_variable m_cvBlockNotZero;
	WAVEFORMATEX m_wfFormat;

	shared_ptr<CNotePlayer> m_pNotePlayer;

	HWND* m_phWndParent;
};

