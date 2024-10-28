#pragma once
#include <string>
#include "Common.h"
#include "PlayParams.h"

using namespace std;

class COscillatorBase : public CObserver
{
public:
	COscillatorBase();
	~COscillatorBase();

	virtual double GetParam(wstring wstrParam) = 0;

	virtual void SetParam(wstring wstrParam, double dVal) = 0;

	void Update(CSubject* theChangedSubject);

protected:
	double* m_LookUpTable;
	int m_iSampling;
	wstring m_wstrSingalType;
	double m_dDutyCycle;
	double m_dPhaseBias;
	int m_iSamplingRate;
	int m_iPreviousPhase[15];

	double m_dIncrement;

	void Calculate();
};

//----------------------------------------------------------------------------

class COscillator : public COscillatorBase
{
public:
	COscillator();

	double GetParam(wstring wstrParam);

	void SetParam(wstring wstrParam, double dVal);

	double Sound(double dFrequency, double dCurrentTime);

protected:
	int m_iUnisonNumber;
};

//----------------------------------------------------------------------------

class CLFO : public COscillatorBase
{
public:
	CLFO();

	double Sound(double dOldValue);

	double GetParam(wstring wstrParam);

	void SetParam(wstring wstrParam, double dVal);
	
private:
	double m_dFrequency;
	double m_dAmount;
};

