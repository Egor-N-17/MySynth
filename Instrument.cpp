#include "stdafx.h"
#include "Instrument.h"
#include <stdlib.h> 
#include <math.h>

//----------------------------------------------------------------------------

CInstrument::CInstrument()
{
	m_pAmplEnvelope = make_shared<CEnvelope>();
	m_pLFO_Frequency = make_shared<CLFO>();
	m_pLFO_Amplitude = make_shared<CLFO>();
	m_pFilter = nullptr;
	m_pFilterEnvelope = nullptr;
	m_pOscillators = make_shared<CInstrumentSum>();
}

//----------------------------------------------------------------------------

void CInstrument::SetMix()
{
	shared_ptr<CInstrumentBase> pInstrument = make_shared<CInstrumentMix>();

	for (int i = 0; i < m_pOscillators->GetNumberOfInstruments(); i++)
	{
		pInstrument->SetInstrument(m_pOscillators->GetInstrumentByNumber(OSCILLATOR, i));
	}
	m_pOscillators.reset();
	m_pOscillators.swap(pInstrument);
}

//----------------------------------------------------------------------------

void CInstrument::SetSum()
{
	shared_ptr<CInstrumentBase> pInstrument = make_shared<CInstrumentSum>();

	for (int i = 0; i < m_pOscillators->GetNumberOfInstruments(); i++)
	{
		pInstrument->SetInstrument(m_pOscillators->GetInstrumentByNumber(OSCILLATOR, i));
	}
	m_pOscillators.reset();
	m_pOscillators.swap(pInstrument);
}

//----------------------------------------------------------------------------

shared_ptr<COscillator> CInstrument::GetOscillator(int iNumber)
{
	return m_pOscillators->GetInstrumentByNumber(OSCILLATOR, iNumber);
}

//----------------------------------------------------------------------------

double CInstrument::Sound(double dCurrentTime, double dFrequency, double dKeyDownTime)
{
	unique_lock<mutex> m(m_mutRealTime);
	if (m_pLFO_Frequency)
	{
		dFrequency = m_pLFO_Frequency->Sound(dFrequency);
	}

	double dAmplitude = 1;
	if (m_pLFO_Amplitude)
	{
		dAmplitude = m_pLFO_Amplitude->Sound(m_pAmplEnvelope->Sound(dCurrentTime, dKeyDownTime));
	}
	
	double dRes = 0;
	
	dRes = m_pOscillators->Sound(dCurrentTime, dFrequency, dKeyDownTime);

	if (m_pFilter)
	{
		dRes = m_pFilter->Sound(dRes);
		m_pFilter->SetParam(INCREMENT, m_pFilterEnvelope->Sound(dCurrentTime, dKeyDownTime));
	}

	return dRes / 2 * 0.1 * dAmplitude;
}

//----------------------------------------------------------------------------

void CInstrument::SetParam(wstring wstrParam, double dVal)
{
	if (wstrParam == MIX_OSCILLATOR)
	{
		static_cast<CInstrumentMix*>(m_pOscillators.get())->SetMixRatio(dVal);
	}
}

//----------------------------------------------------------------------------

double CInstrument::GetParam(wstring wstrParam)
{
	if (wstrParam == MIX_OSCILLATOR)
	{
		return static_cast<CInstrumentMix*>(m_pOscillators.get())->GetMixRatio();
	}
	if (wstrParam == T_RELEASE)
	{
		if (m_pAmplEnvelope && m_pFilterEnvelope)
		{
			return max(m_pAmplEnvelope->GetParam(wstrParam), m_pFilterEnvelope->GetParam(wstrParam));
		}
		else if(m_pAmplEnvelope)
		{
			return m_pAmplEnvelope->GetParam(wstrParam);
		}
		else if (m_pFilterEnvelope)
		{
			return m_pFilterEnvelope->GetParam(wstrParam);
		}
	}
	return 0.0;
}

//----------------------------------------------------------------------------

void CInstrument::SetInstrument(wstring wstrParam)
{
	if (wstrParam == SUM_OSCILLATOR)
	{
		SetSum();
	}
	if (wstrParam == MIX_OSCILLATOR)
	{
		SetMix();
	}
}

//----------------------------------------------------------------------------

void CInstrument::SetParamToInstrument(wstring wstrInstr, wstring wstrParam, double dVal)
{
	if (wstrInstr == LFO_A)
	{
		m_pLFO_Amplitude->SetParam(wstrParam, dVal);
	}
	if (wstrInstr == ENVELOPE_AMPL)
	{
		m_pAmplEnvelope->SetParam(wstrParam, dVal);
	}
	if (wstrInstr == LFO_F)
	{
		m_pLFO_Frequency->SetParam(wstrParam, dVal);
	}
	if (wstrInstr == FILTER)
	{
		m_pFilter->SetParam(wstrParam, dVal);
	}
	if (wstrInstr == ENVELOPE_FREQ)
	{
		m_pFilterEnvelope->SetParam(wstrParam, dVal);
	}
}

//----------------------------------------------------------------------------

double CInstrument::GetParamFromInstrument(wstring wstrInstr, wstring wstrParam)
{
	if (wstrInstr == LFO_A)
	{
		return m_pLFO_Amplitude->GetParam(wstrParam);
	}
	if (wstrInstr == ENVELOPE_AMPL)
	{
		return m_pAmplEnvelope->GetParam(wstrParam);
	}
	if (wstrInstr == LFO_F)
	{
		return m_pLFO_Frequency->GetParam(wstrParam);
	}
	if (wstrInstr == FILTER)
	{
		return m_pFilter->GetParam(wstrParam);
	}
	if (wstrInstr == ENVELOPE_FREQ)
	{
		return m_pFilterEnvelope->GetParam(wstrParam);
	}
	return 0.0;
}

//----------------------------------------------------------------------------

void CInstrument::SetOscillator(shared_ptr<COscillator> pOscillator)
{
	m_pOscillators->SetInstrument(pOscillator);
}

//----------------------------------------------------------------------------

void CInstrument::DeleteOscillator(int iNumber)
{
	m_pOscillators->DeleteInstrument(iNumber);
	if (m_pOscillators->GetName() == MIX_OSCILLATOR)
	{
		SetSum();
	}
}

//----------------------------------------------------------------------------

int CInstrument::GetNumberOfOscillator()
{
	return m_pOscillators->GetNumberOfInstruments();
}

//----------------------------------------------------------------------------

double CInstrument::GetEnvEnd()
{
	if (m_pFilterEnvelope && m_pAmplEnvelope)
	{
		return max(m_pAmplEnvelope->GetParam(T_RELEASE), m_pFilterEnvelope->GetParam(T_RELEASE));
	}
	if (m_pFilterEnvelope)
	{
		return m_pFilterEnvelope->GetParam(T_RELEASE);
	}
	if (m_pAmplEnvelope)
	{
		return m_pAmplEnvelope->GetParam(T_RELEASE);
	}
	return 0;

}

//----------------------------------------------------------------------------

bool CInstrument::IsMix()
{
	if (m_pOscillators->GetName() == MIX_OSCILLATOR)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//----------------------------------------------------------------------------

void CInstrument::UseFilter()
{
	unique_lock<mutex> m(m_mutRealTime);
	m_pFilter = make_shared<CFilter>();
	m_pFilterEnvelope = make_shared<CEnvelope>();
}

//----------------------------------------------------------------------------

void CInstrument::UnuseFilter()
{
	unique_lock<mutex> m(m_mutRealTime);
	if (m_pFilter)
	{
		m_pFilter.reset();
		m_pFilterEnvelope.reset();
	}
}

//----------------------------------------------------------------------------

bool CInstrument::IsFilterUse()
{
	unique_lock<mutex> m(m_mutRealTime);
	return m_pFilter == nullptr ? false : true;
}

//----------------------------------------------------------------------------

bool CInstrument::IsEnvelopeFilterUse()
{
	unique_lock<mutex> m(m_mutRealTime);
	return m_pFilterEnvelope == nullptr ? false : true;
}

//----------------------------------------------------------------------------

//							CInstrumentBase

//----------------------------------------------------------------------------

CInstrumentBase::CInstrumentBase()
{
	m_iNumberOfInstruments = 0;
}

//----------------------------------------------------------------------------

int CInstrumentBase::GetNumberOfInstruments()
{
	return m_iNumberOfInstruments;
}

//----------------------------------------------------------------------------

wstring CInstrumentBase::GetName()
{
	return m_wstrName;
}

//----------------------------------------------------------------------------

//							CInstrumentSum

//----------------------------------------------------------------------------

CInstrumentSum::CInstrumentSum()
{
	m_wstrName = SUM_OSCILLATOR;
}

//----------------------------------------------------------------------------

void CInstrumentSum::SetInstrument(shared_ptr<COscillator> pInstrument)
{
	m_arrMainOscillators[m_iNumberOfInstruments] = pInstrument;
	m_iNumberOfInstruments++;
}

//----------------------------------------------------------------------------

void CInstrumentSum::DeleteInstrument(int iNumber)
{
	array<shared_ptr<COscillator>, MAX_NUMBER_OF_SCILLATORS> newArr;
	int j = 0;
	for (int i = 0; i < m_iNumberOfInstruments; i++)
	{
		if (i != iNumber)
		{
			newArr[j] = m_arrMainOscillators[i];
			j++;
		}
	}
	m_arrMainOscillators.swap(newArr);
	m_iNumberOfInstruments--;
}

//----------------------------------------------------------------------------

shared_ptr<COscillator> CInstrumentSum::GetInstrumentByNumber(wstring wstrIntr, int iNumber)
{
	return m_arrMainOscillators[iNumber];
}

//----------------------------------------------------------------------------

double CInstrumentSum::Sound(double dCurrentTime, double dFrequency, double dKeyDownTime)
{
	double dRes = 0;
	for (int i = 0; i < m_iNumberOfInstruments; i++)
	{
		dRes += m_arrMainOscillators[0]->Sound(dFrequency, dCurrentTime);
	}
	return dRes;
}

//----------------------------------------------------------------------------

//							CInstrumentMix

//----------------------------------------------------------------------------

CInstrumentMix::CInstrumentMix()
{
	m_dMixRatio = 0.5;
	m_wstrName = MIX_OSCILLATOR;
}

//----------------------------------------------------------------------------

void CInstrumentMix::SetInstrument(shared_ptr<COscillator> pInstrument)
{
	m_arrMainOscillators[m_iNumberOfInstruments] = pInstrument;
	m_iNumberOfInstruments++;
}

//----------------------------------------------------------------------------

shared_ptr<COscillator> CInstrumentMix::GetInstrumentByNumber(wstring wstrIntr, int iNumber)
{
	return m_arrMainOscillators[iNumber];
}

//----------------------------------------------------------------------------

void CInstrumentMix::DeleteInstrument(int iNumber)
{
	array<shared_ptr<COscillator>, MAX_NUMBER_OF_SCILLATORS> newArr;
	int j = 0;
	for (int i = 0; i < m_iNumberOfInstruments; i++)
	{
		if (i != iNumber)
		{
			newArr[j] = m_arrMainOscillators[i];
			j++;
		}
	}
	m_arrMainOscillators.swap(newArr);
	m_iNumberOfInstruments--;
}

//----------------------------------------------------------------------------

double CInstrumentMix::Sound(double dCurrentTime, double dFrequency, double dKeyDownTime)
{
	return m_arrMainOscillators[0]->Sound(dFrequency, dCurrentTime) * m_dMixRatio + m_arrMainOscillators[1]->Sound(dFrequency, dCurrentTime) * (1 - m_dMixRatio);
}

//----------------------------------------------------------------------------

void CInstrumentMix::SetMixRatio(double dMixRatio)
{
	m_dMixRatio = dMixRatio;
}

//----------------------------------------------------------------------------

double CInstrumentMix::GetMixRatio()
{
	return m_dMixRatio;
}

//----------------------------------------------------------------------------