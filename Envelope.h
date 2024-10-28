#pragma once
#include <string>
#include <vector>
#include "Common.h"

using namespace std;

class CEnvelope
{
public:
	CEnvelope();
	
	void SetParam(wstring wstrParam, double dVal);

	double GetParam(wstring wstrParam);

	double Sound(double dCurrTime, double dKeyDown);

protected:
	double Calculate(double dStartTime, double dEndTime, double dStartParam, double dEndParam, double dCurrTime);

	double m_dFilterMultipicator;

	double m_dAttackValue;
	double m_dDecayValue;
	double m_dSustainValue;
	double m_dReleaseValue;

	double m_dAttackTime;
	double m_dDecayTime;
	double m_dSustainTime;
	double m_dReleaseTime;

};