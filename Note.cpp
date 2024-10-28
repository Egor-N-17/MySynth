#include "stdafx.h"
#include "Note.h"

//----------------------------------------------------------------------------

CNote::CNote(shared_ptr<CInstrument> pInstrument, int iNote)
{
	m_pInstrument = pInstrument;
	m_dKeyDown = 0.0;
	m_dKeyUp = 10000000000;

	m_iNoteNumber = iNote;
	m_iOctaveNumber = 4;

	CalculateFrequency();

	m_dEnvEnd = m_pInstrument->GetParam(T_RELEASE);
}

//----------------------------------------------------------------------------

double CNote::Sound(double dCurrentTime)
{
	if (IsActive(dCurrentTime) == false)
	{
		return 0;
	}
	else
	{
		dCurrentTime = dCurrentTime - m_dKeyDown;
		return m_pInstrument->Sound(dCurrentTime, m_dFrequency, (m_dKeyUp - m_dKeyDown) + m_dEnvEnd);
	}
}

//----------------------------------------------------------------------------

int CNote::GetNote()
{
	return m_iNoteNumber;
}

//----------------------------------------------------------------------------

bool CNote::IsActive(double dCurTime)
{
	if (m_dKeyUp == 10000000000)
	{
		return m_dKeyDown <= dCurTime && dCurTime <= m_dKeyUp;
	}
	else
	{
		return m_dKeyDown <= dCurTime && dCurTime <= max(m_dKeyUp + m_dEnvEnd, m_dKeyUp);
	}
}

//----------------------------------------------------------------------------

void CNote::ActivateNote(chrono::high_resolution_clock::time_point tStarPlay)
{
	m_tStartRecord = tStarPlay;
	m_dKeyDown = chrono::duration<double>(chrono::high_resolution_clock::now() - m_tStartRecord).count();
}

//----------------------------------------------------------------------------

void CNote::DeactivateNote()
{
	m_dKeyUp = chrono::duration<double>(chrono::high_resolution_clock::now() - m_tStartRecord).count();
}

//----------------------------------------------------------------------------

void CNote::CalculateFrequency()
{
	m_dFrequency = 16.352 * pow(1.0594630943592952645618252949463, m_iNoteNumber + 12 * m_iOctaveNumber);
}

//----------------------------------------------------------------------------