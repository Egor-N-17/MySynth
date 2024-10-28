#pragma once
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <mutex>
#include "Play.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"

using namespace std;

//----------------------------------------------------------------------------

class CInstrumentBase
{
public:
	CInstrumentBase();

	virtual void SetInstrument(shared_ptr<COscillator> pInstrument) = 0;
	virtual shared_ptr<COscillator> GetInstrumentByNumber(wstring wstrIntr, int iNumber) = 0;
	virtual void DeleteInstrument(int iNumber) = 0;

	virtual double Sound(double dCurrentTime, double dFrequency, double dKeyDownTime) = 0;

	virtual int GetNumberOfInstruments();

	wstring GetName();

protected:
	array<shared_ptr<COscillator>, MAX_NUMBER_OF_SCILLATORS> m_arrMainOscillators;
	int m_iNumberOfInstruments;
	wstring m_wstrName;
};

//----------------------------------------------------------------------------

class CInstrumentSum : public CInstrumentBase
{
public:
	CInstrumentSum();

	void SetInstrument(shared_ptr<COscillator> pInstrument);
	shared_ptr<COscillator> GetInstrumentByNumber(wstring wstrIntr, int iNumber);
	void DeleteInstrument(int iNumber);

	double Sound(double dCurrentTime, double dFrequency, double dKeyDownTime);
};

//----------------------------------------------------------------------------

class CInstrumentMix : public CInstrumentBase
{
public:
	CInstrumentMix();

void SetInstrument(shared_ptr<COscillator> pInstrument);
shared_ptr<COscillator> GetInstrumentByNumber(wstring wstrIntr, int iNumber);
void DeleteInstrument(int iNumber);

double Sound(double dCurrentTime, double dFrequency, double dKeyDownTime);

void SetMixRatio(double dMixRatio);
double GetMixRatio();

protected:
double m_dMixRatio;
};

//----------------------------------------------------------------------------

class CInstrument
{
public:
	CInstrument();
	
	double Sound(double dCurrentTime, double dFrequency, double dKeyDownTime);

	void SetParam(wstring wstrParam, double dVal = 0);
	double GetParam(wstring wstrParam);

	void SetInstrument(wstring wstrParam);

	void SetParamToInstrument(wstring wstrInstr, wstring wstrParam, double dVal);
	double GetParamFromInstrument(wstring wstrInstr, wstring wstrParam);

	//MAIN OSCILLATORS
	shared_ptr<COscillator> GetOscillator(int iNumber);
	void SetOscillator(shared_ptr<COscillator> pOscillator);
	void DeleteOscillator(int iNumber);
	int GetNumberOfOscillator();
	double GetEnvEnd();
	bool IsMix();

	//Filters
	void UseFilter();
	void UnuseFilter();
	bool IsFilterUse();
	bool IsEnvelopeFilterUse();

private:
	void SetMix();
	void SetSum();

	shared_ptr<CInstrumentBase> m_pOscillators;
	shared_ptr<CLFO> m_pLFO_Frequency;
	shared_ptr<CLFO> m_pLFO_Amplitude;
	
	shared_ptr<CFilter> m_pFilter;
	
	shared_ptr<CEnvelope> m_pAmplEnvelope;
	shared_ptr<CEnvelope> m_pFilterEnvelope;
	mutex m_mutRealTime;
};