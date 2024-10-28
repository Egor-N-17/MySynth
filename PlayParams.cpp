#include "stdafx.h"
#include "PlayParams.h"

//----------------------------------------------------------------------------

sPlayParams CPlayParams::GetPlayParams()
{
	return m_PlayParams;
}

//----------------------------------------------------------------------------

void CPlayParams::SetPlayParams(sPlayParams playParams)
{
	m_PlayParams = playParams;
	Notify();
}

//----------------------------------------------------------------------------

CPlayParams::CPlayParams()
{
	m_PlayParams.iSampleRate = 44000;
	m_PlayParams.iChannel = 2;
	m_PlayParams.iBlocks = 8;
	m_PlayParams.iBlockSample = 512;
	m_PlayParams.iDeviceNumber = 0;
	m_PlayParams.iC = 0;
	m_PlayParams.iCSharp = 0;
	m_PlayParams.iD = 0;
	m_PlayParams.iDSharp = 0;
	m_PlayParams.iE = 0;
	m_PlayParams.iF = 0;
	m_PlayParams.iFSharp = 0;
	m_PlayParams.iG = 0;
	m_PlayParams.iGSharp = 0;
	m_PlayParams.iA = 0;
	m_PlayParams.iASharp = 0;
	m_PlayParams.iH = 0;
}

//----------------------------------------------------------------------------

bool CPlayParams::Empty()
{
	if (m_PlayParams.empty())
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------

void CPlayParams::ClearData()
{
	m_PlayParams.clearData();
}