#include "stdafx.h"
#include "Filter.h"

//----------------------------------------------------------------------------

CFilter::CFilter()
{
	m_dTeta = 0;
	m_dD = 0;
	m_dQ = 0.707;
	m_dBeta = 0;
	m_dGamma = 0;

	m_dA0 = 0;
	m_dA1 = 0;
	m_dA2 = 0;
	m_dB1 = 0;
	m_dB2 = 0;

	m_wstrType = LOWPASS_MODE;

	for (int i = 0; i < 2; i++)
	{
		m_arrPreviousInput[i] = 0;
		m_arrPreviousOutput[i] = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		m_dXh[i] = 0;
	}

	m_dCutOffFreq = 1000;

	m_dIncrement = 0;

	shared_ptr<CPlayParams> pPlayParams = CPlayParams::Instance();
	pPlayParams->Attach(this);

	m_iSampleRate = pPlayParams->GetPlayParams().iSampleRate;
}

//----------------------------------------------------------------------------

CFilter::~CFilter()
{
	shared_ptr<CPlayParams> pPlayParams = CPlayParams::Instance();
	pPlayParams->Detach(this);
}

//----------------------------------------------------------------------------

double CFilter::Sound(double dValue)
{
	unique_lock<mutex> m(m_mutCalculate);

	double dRes = dValue * m_dA0 + m_arrPreviousInput[0] * m_dA1 + m_arrPreviousInput[1] * m_dA2 - m_arrPreviousOutput[0] * m_dB1 - m_arrPreviousOutput[1] * m_dB2;

	m_arrPreviousInput[1] = m_arrPreviousInput[0];
	m_arrPreviousInput[0] = dValue;

	m_arrPreviousOutput[1] = m_arrPreviousOutput[0];
	m_arrPreviousOutput[0] = dRes;

	return dRes;
}

//----------------------------------------------------------------------------

double CFilter::GetParam(wstring wstrParam)
{
	if (wstrParam == FILTER_MODE)
	{
		return GetFilterModeByString(m_wstrType);
	}
	if (wstrParam == CUTOFF)
	{
		return m_dCutOffFreq;
	}
	if (wstrParam == RESONANCE)
	{
		return m_dQ;
	}
	return 0;
}

//----------------------------------------------------------------------------

void CFilter::SetParam(wstring wstrParam, double dVal)
{
	if (wstrParam == FILTER_MODE)
	{
		m_wstrType = GetFilterModeByNumber((int)dVal);
	}
	if (wstrParam == CUTOFF)
	{
		m_dCutOffFreq = dVal;
	}
	if (wstrParam == RESONANCE)
	{
		m_dQ = dVal;
	}
	if (wstrParam == INCREMENT)
	{
		m_dIncrement = dVal;
	}
	Calculate();
}

//----------------------------------------------------------------------------

void CFilter::Update(CSubject * theChangedSubject)
{
	unique_lock<mutex> m(m_mutCalculate);
	m_iSampleRate = static_cast<CPlayParams*>(theChangedSubject)->GetPlayParams().iSampleRate;
}

//----------------------------------------------------------------------------

void CFilter::Calculate()
{
	m_dTeta = 2 * PI * (m_dCutOffFreq + m_dIncrement) / m_iSampleRate;
	double dD = 1 / m_dQ;

	double dBeta = 0.5 * (1 - dD / 2 * sin(m_dTeta)) / (1 + dD / 2 * sin(m_dTeta));
	double dGamma = (0.5 + dBeta) * cos(m_dTeta);
	m_dA0 = (0.5 + dBeta - dGamma) / 2;
	m_dA1 = 0.5 + dBeta - dGamma;
	m_dA2 = m_dA0;
	m_dB1 = -2 * dGamma;
	m_dB2 = 2 * dBeta;

	if (m_wstrType == HIGHPASS_MODE)
	{
		m_dA1 = -1* m_dA1;
	}
}
