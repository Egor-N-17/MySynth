#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Common.h"

using namespace std;

//----------------------------------------------------------------------------

struct sPlayParams
{
	int iDeviceNumber;
	int iSampleRate;
	int iChannel;
	int iBlocks;
	int iBlockSample;

	int iC;
	int iCSharp;
	int iD;
	int iDSharp;
	int iE;
	int iF;
	int iFSharp;
	int iG;
	int iGSharp;
	int iA;
	int iASharp;
	int iH;

	bool empty()
	{
		if (iDeviceNumber == 0 &&
			iSampleRate == 0 &&
			iChannel == 0 &&
			iBlocks == 0 &&
			iBlockSample == 0)
		{
			return true;
		}
		return false;
	}

	void clearData()
	{
		iDeviceNumber = 0;
		iSampleRate = 0;
		iChannel = 0;
		iBlocks = 0;
		iBlockSample = 0;

		iC = 0;
		iCSharp = 0;
		iD = 0;
		iDSharp = 0;
		iE = 0;
		iF = 0;
		iFSharp = 0;
		iG = 0;
		iGSharp = 0;
		iA = 0;
		iASharp = 0;
		iH = 0;
	}
};

//----------------------------------------------------------------------------

class CPlayParams : public CSubject, public CSingleton<CPlayParams>
{
	friend class CSingleton<CPlayParams>;
public:

	bool Empty();
	void ClearData();

	sPlayParams GetPlayParams();
	void SetPlayParams(sPlayParams playParams);

protected:
	CPlayParams();

	sPlayParams m_PlayParams;
};

