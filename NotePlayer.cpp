#include "stdafx.h"
#include "NotePlayer.h"

//----------------------------------------------------------------------------

CNotePlayer::CNotePlayer(shared_ptr<CInstrument> pInstrument)
{
	m_pInstrument = pInstrument;
	shared_ptr<CPlayParams> pPlayParams = CPlayParams::Instance();
	m_PlayParams = pPlayParams->GetPlayParams();

	pPlayParams->Attach(this);
}

//----------------------------------------------------------------------------

CNotePlayer::~CNotePlayer()
{
	shared_ptr<CPlayParams> pPlayParams = CPlayParams::Instance();
	pPlayParams->Detach(this);
}

//----------------------------------------------------------------------------

void CNotePlayer::Update(CSubject * theChangedSubject)
{
	m_PlayParams = static_cast<CPlayParams*>(theChangedSubject)->GetPlayParams();
}

//----------------------------------------------------------------------------

void CNotePlayer::SetStartTime()
{
	m_tStartPlay = chrono::high_resolution_clock::now();
}

//----------------------------------------------------------------------------

void CNotePlayer::AddNote(MSG* pMsg)
{
	int iNote = 0;

	iNote = ChooseNote(pMsg);
	if (iNote == 0)
	{
		return;
	}

	auto it = find_if(m_activeNote.begin(), m_activeNote.end(), [&](shared_ptr<CNote> note)
	{
		return iNote == note->GetNote();
	});

	if (it == m_activeNote.end())
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			unique_lock<mutex> m(m_mutAddNote);
			shared_ptr<CNote> pNote = make_shared<CNote>(m_pInstrument, iNote);
			pNote->ActivateNote(m_tStartPlay);
			m_activeNote.emplace_back(pNote);
		}
	}
	else
	{
		if (pMsg->message == WM_KEYUP)
		{
			unique_lock<mutex> m(m_mutAddNote);
			(*it)->DeactivateNote();
		}
	}

}

//----------------------------------------------------------------------------

double CNotePlayer::Sound(double dCurrentTime)
{
	unique_lock<mutex> m(m_mutAddNote);
	double dResult = 0;
	for (vector<shared_ptr<CNote>>::iterator itNote = m_activeNote.begin(); itNote != m_activeNote.end(); itNote++)
	{
		if ((*itNote)->IsActive(dCurrentTime))
		{
			dResult += (*itNote)->Sound(dCurrentTime);
		}
		else
		{
			itNote = m_activeNote.erase(itNote);
			if (itNote == m_activeNote.end())
			{
				break;
			}
		}
	}
	return dResult;
}

//----------------------------------------------------------------------------

void CNotePlayer::Stop()
{
	m_activeNote.clear();
}

//----------------------------------------------------------------------------

int CNotePlayer::ChooseNote(MSG* pMsg)
{
	if (pMsg->wParam == m_PlayParams.iC)
	{
		return 1;
	}
	if (pMsg->wParam == m_PlayParams.iCSharp)
	{
		return 2;
	}
	if (pMsg->wParam == m_PlayParams.iD)
	{
		return 3;
	}
	if (pMsg->wParam == m_PlayParams.iDSharp)
	{
		return 4;
	}
	if (pMsg->wParam == m_PlayParams.iE)
	{
		return 5;
	}
	if (pMsg->wParam == m_PlayParams.iF)
	{
		return 6;
	}
	if (pMsg->wParam == m_PlayParams.iFSharp)
	{
		return 7;
	}
	if (pMsg->wParam == m_PlayParams.iG)
	{
		return 8;
	}
	if (pMsg->wParam == m_PlayParams.iGSharp)
	{
		return 9;
	}
	if (pMsg->wParam == m_PlayParams.iA)
	{
		return 10;
	}
	if (pMsg->wParam == m_PlayParams.iASharp)
	{
		return 11;
	}
	if (pMsg->wParam == m_PlayParams.iH)
	{
		return 12;
	}
	return 0;
}

//----------------------------------------------------------------------------
