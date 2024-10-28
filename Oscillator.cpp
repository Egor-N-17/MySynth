#include "stdafx.h"
#include "Oscillator.h"

using namespace std;

//----------------------------------------------------------------------------

//												COscillatorBase

//----------------------------------------------------------------------------

COscillatorBase::COscillatorBase()
{
	m_wstrSingalType = SIN_SIGNAL;
	m_iSampling = NUMBER_OF_SAMPLES;
	m_LookUpTable = new double[m_iSampling];
	m_dDutyCycle = 0;
	m_dPhaseBias = 0;
	shared_ptr<CPlayParams> pPlayParams = CPlayParams::Instance();
	pPlayParams->Attach(this);
	m_iSamplingRate = pPlayParams->GetPlayParams().iSampleRate;
	for (int i = 0; i < 15; i++)
	{
		m_iPreviousPhase[i] = 0;
	}
	m_dIncrement = 0;
}

//----------------------------------------------------------------------------

COscillatorBase::~COscillatorBase()
{
	shared_ptr<CPlayParams> pPlayParams = CPlayParams::Instance();
	pPlayParams->Detach(this);
	delete[] m_LookUpTable;
}

//----------------------------------------------------------------------------

void COscillatorBase::Calculate()
{
	if (m_wstrSingalType == SIN_SIGNAL)
	{
		for (int i = 0; i < m_iSampling; i++)
		{
			m_LookUpTable[i] = sin(2 * PI * i / m_iSampling + m_dPhaseBias) / 2;
		}
	}
	else if (m_wstrSingalType == SQUARE_SIGNAL)
	{
		for (int i = 0; i < m_iSampling; i++)
		{
			m_LookUpTable[i] = sin(2 * PI * i / m_iSampling + m_dPhaseBias) - m_dDutyCycle > 0 ? 1 : -1;;
		}
	}
	else if (m_wstrSingalType == TRIANGLE_SIGNAL)
	{
		for (int i = 0; i < m_iSampling; i++)
		{
			m_LookUpTable[i] = asin(sin(2 * PI * i / m_iSampling + m_dPhaseBias)) * (2.0 / PI);
		}
	}
	else if (m_wstrSingalType == SAW_SIGNAL)
	{
		for (int i = 0; i < m_iSampling; i++)
		{
			m_LookUpTable[i] = (2.0 / PI) *atan(tan(2 * PI * i / m_iSampling + m_dPhaseBias));
		}
	}
}

//----------------------------------------------------------------------------

void COscillatorBase::Update(CSubject * theChangedSubject)
{
	m_iSamplingRate = static_cast<CPlayParams*>(theChangedSubject)->GetPlayParams().iSampleRate;
}

//----------------------------------------------------------------------------

//												COscillator

//----------------------------------------------------------------------------

COscillator::COscillator()
{
	m_iUnisonNumber = 1;
}

//----------------------------------------------------------------------------

double COscillator::GetParam(wstring wstrParam)
{
	if (wstrParam == SIGNAL_TYPE)
	{
		return GetSignalTypeByString(m_wstrSingalType);
	}
	if (wstrParam == PHASE_BIAS)
	{
		return m_dPhaseBias;
	}
	if (wstrParam == DUTY_CYCLE)
	{
		return m_dDutyCycle;
	}
	if (wstrParam == UNISONE)
	{
		return m_iUnisonNumber;
	}
	if (wstrParam == INCREMENT)
	{
		return m_dIncrement;
	}
	return 0;
}

//----------------------------------------------------------------------------

void COscillator::SetParam(wstring wstrParam, double dVal)
{
	if (wstrParam == SIGNAL_TYPE)
	{
		m_wstrSingalType = GetSignalTypeByNumber((int)dVal);
	}
	if (wstrParam == PHASE_BIAS)
	{
		m_dPhaseBias = dVal;
	}
	if (wstrParam == DUTY_CYCLE)
	{
		m_dDutyCycle = dVal;
	}
	if (wstrParam == UNISONE)
	{
		m_iUnisonNumber = (int)dVal;
	}
	if (wstrParam == INCREMENT)
	{
		m_dIncrement = dVal;
	}
	Calculate();
}

//----------------------------------------------------------------------------

double COscillator::Sound(double dFrequency, double dCurrentTime)
{
	double dResult = 0;
	int iNextStep = 0;
	double dSymbol = 0;
	if (m_wstrSingalType != NOISE_SIGNAL)
	{
		for (int i = 0; i < m_iUnisonNumber; i++)
		{
			dSymbol = i == 0 ? 0 : i % 2 == 0 ? 1 : -1;
			iNextStep = (int)fmod(m_iPreviousPhase[i] + m_iSampling * (dFrequency + dSymbol * m_dIncrement) / m_iSamplingRate, m_iSampling);
			dResult += m_LookUpTable[iNextStep] / m_iUnisonNumber;
			m_iPreviousPhase[i] = iNextStep;
		}
	}
	else
	{
		dResult = 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
	}

	return dResult;
}

//----------------------------------------------------------------------------

//												LFO

//----------------------------------------------------------------------------

CLFO::CLFO()
{
	m_dFrequency = 0;
	m_dAmount = 0;
}

//----------------------------------------------------------------------------

double CLFO::Sound(double dOldValue)
{
	if (m_dFrequency == 0)
	{
		return dOldValue;
	}
	
	double dRes = m_iSampling * m_dFrequency / m_iSamplingRate;
	int iNextStep = 0;

	if (dRes > 1)
	{
		iNextStep = (int)fmod(m_iPreviousPhase[0] + dRes, m_iSampling);
		m_iPreviousPhase[0] = iNextStep;
	}
	else
	{
		m_dIncrement += dRes;
		iNextStep = (int)fmod(m_iPreviousPhase[0] + dRes, m_iSampling);
		if (m_dIncrement > 1)
		{
			m_iPreviousPhase[0] = m_iPreviousPhase[0] + 1;
			m_dIncrement = 0;
		}
	}
	
	return dOldValue + dOldValue * m_LookUpTable[iNextStep] * m_dAmount;
}

//----------------------------------------------------------------------------

double CLFO::GetParam(wstring wstrParam)
{
	if (wstrParam == SIGNAL_TYPE)
	{
		return GetSignalTypeByString(m_wstrSingalType);
	}
	if (wstrParam == LFO_FREQUENCY)
	{
		return m_dFrequency;
	}
	if (wstrParam == LFO_AMOUNT)
	{
		return m_dAmount;
	}
	return 0;
}

//----------------------------------------------------------------------------

void CLFO::SetParam(wstring wstrParam, double dVal)
{
	if (wstrParam == SIGNAL_TYPE)
	{
		m_wstrSingalType = GetSignalTypeByNumber((int)dVal);
	}
	if (wstrParam == LFO_FREQUENCY)
	{
		m_dFrequency = dVal;
	}
	if (wstrParam == LFO_AMOUNT)
	{
		m_dAmount = dVal;
	}
	Calculate();
}
