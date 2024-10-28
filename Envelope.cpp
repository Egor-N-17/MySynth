#include "stdafx.h"
#include "Envelope.h"

//----------------------------------------------------------------------------

CEnvelope::CEnvelope()
{
	m_dAttackValue = 0;
	m_dDecayValue = 0;
	m_dSustainValue = 1;
	m_dReleaseValue = 0;

	m_dAttackTime = 0;
	m_dDecayTime = 0;
	m_dSustainTime = 1;
	m_dReleaseTime = 0;
	m_dFilterMultipicator = 1;
}

//----------------------------------------------------------------------------

double CEnvelope::GetParam(wstring wstrParam)
{
	if (wstrParam == V_ATTACK)
	{
		return m_dAttackValue;
	}
	if (wstrParam == V_DECAY)
	{
		return m_dDecayValue;
	}
	if (wstrParam == V_SUSTAIN)
	{
		return m_dSustainValue;
	}
	if (wstrParam == V_RELEASE)
	{
		return m_dReleaseValue;
	}
	if (wstrParam == T_ATTACK)
	{
		return m_dAttackTime;
	}
	if (wstrParam == T_DECAY)
	{
		return m_dDecayTime;
	}
	if (wstrParam == T_SUSTAIN)
	{
		return m_dSustainTime;
	}
	if (wstrParam == T_RELEASE)
	{
		return m_dReleaseTime;
	}
	return 0;
}

//----------------------------------------------------------------------------

void CEnvelope::SetParam(wstring wstrParam, double dVal)
{
	if (wstrParam == T_ATTACK)
	{
		m_dAttackTime = dVal;
	}
	if (wstrParam == T_DECAY)
	{
		m_dDecayTime = dVal;
	}
	if (wstrParam == T_SUSTAIN)
	{
		m_dSustainTime = dVal;
	}
	if (wstrParam == T_RELEASE)
	{
		m_dReleaseTime = dVal;
	}
	if (wstrParam == V_ATTACK)
	{
		m_dAttackValue = dVal;
	}
	if (wstrParam == V_DECAY)
	{
		m_dDecayValue = dVal;
	}
	if (wstrParam == V_SUSTAIN)
	{
		m_dSustainValue = dVal;
	}
	if (wstrParam == V_RELEASE)
	{
		m_dReleaseValue = dVal;
	}
	if (wstrParam == ENVELOPE)
	{
		m_dFilterMultipicator = dVal;
	}
}

//----------------------------------------------------------------------------

double CEnvelope::Sound(double dCurrTime, double dKeyDown)
{
	if (dCurrTime < m_dAttackTime)
	{
		return Calculate(0, m_dAttackTime, 0, m_dFilterMultipicator * m_dAttackValue, dCurrTime);
	}
	else if (dCurrTime < m_dDecayTime)
	{
		return Calculate(m_dAttackTime, m_dDecayTime, m_dFilterMultipicator * m_dAttackValue, m_dFilterMultipicator * m_dDecayValue, dCurrTime);
	}
	else if (dCurrTime < dKeyDown - m_dReleaseTime)
	{
		return Calculate(m_dSustainTime, dKeyDown - m_dReleaseTime, m_dFilterMultipicator * m_dSustainValue, m_dFilterMultipicator * m_dSustainValue, dCurrTime);
	}
	else
	{
		return Calculate(dKeyDown - m_dReleaseTime, dKeyDown, m_dFilterMultipicator * m_dSustainValue, m_dFilterMultipicator * m_dReleaseValue, dCurrTime);
	}
	return 0;
}

//----------------------------------------------------------------------------

double CEnvelope::Calculate(double dStartTime, double dEndTime, double dStartParam, double dEndParam, double dCurrTime)
{
	if (dStartParam == dEndParam)
	{
		return dEndParam;
	}
	else
	{
		return dStartParam + (dEndParam - dStartParam) / (dEndTime - dStartTime) * (dCurrTime - dStartTime);
	}
}

//----------------------------------------------------------------------------