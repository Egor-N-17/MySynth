#pragma once
#include <math.h>
#include "Common.h"
#include <array>
#include <mutex>
#include "PlayParams.h"
#include "Envelope.h"

using namespace std;

class CFilter : public CObserver
{
public:
	CFilter();
	~CFilter();

	double Sound(double dValue);
	
	double GetParam(wstring wstrParam);

	void SetParam(wstring wstrParam, double dVal);

	void Update(CSubject* theChangedSubject);

private:
	void Calculate();

	int m_iSampleRate;

	wstring m_wstrType;

	double m_dCutOffFreq;
	double m_dIncrement;

	array<double, 2> m_arrPreviousInput;
	array<double, 2> m_arrPreviousOutput;

	array<double, 3> m_dXh;

	mutex m_mutCalculate;

	double m_dTeta;
	double m_dD;
	double m_dQ;
	double m_dBeta;
	double m_dGamma;

	double m_dA0;
	double m_dA1;
	double m_dA2;
	double m_dB0;
	double m_dB1;
	double m_dB2;

	shared_ptr<CEnvelope> m_pEnvelope;
};

