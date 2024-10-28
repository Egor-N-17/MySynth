#pragma once
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

//----------------------------------------------------------------------------

inline wstring GetTextFormControl(CWnd &control)
{
	CString str;
	control.GetWindowText(str);
	return (wstring)str;
}

//----------------------------------------------------------------------------

const double PI = 2.0 * acos(0.0);
#define MAX_SAMPLE								65535
#define NUMBER_OF_SAMPLES					1000
#define MAX_NUMBER_OF_SCILLATORS	2
#define	MIX_RATIO									1000
#define	FILTER_RATIO							1000

//LFO
#define LFO_FREQUENCY_MAX					20
#define LFO_AMOUNT_MAX						100

//FILTER
#define FILTER_FREQUENCIES				10000
#define QUALITY_FACTOR_MAX				50000
#define QUALITY_FACTOR_MIN				707

//----------------------------------------------------------------------------
//				SIGNAL TYPE
//----------------------------------------------------------------------------

#define NOISE_SIGNAL			L"NOISE"
#define SAW_SIGNAL				L"SAW"
#define TRIANGLE_SIGNAL		L"TRIANGLE"
#define SQUARE_SIGNAL			L"SQUARE"
#define SIN_SIGNAL				L"SIN"

//----------------------------------------------------------------------------

static std::set<pair<int, wstring>> SignalTypes = { { 0, NOISE_SIGNAL},{ 1, SAW_SIGNAL },{ 2, TRIANGLE_SIGNAL },{ 3, SQUARE_SIGNAL },{ 4, SIN_SIGNAL } };

//----------------------------------------------------------------------------

inline int GetSignalTypeByString(wstring wstrType)
{
	std::set<pair<int, wstring>>::iterator it = std::find_if(SignalTypes.begin(), SignalTypes.end(), [wstrType](const pair<int, wstring> element) { return element.second == wstrType; });
	return it->first;
}

//----------------------------------------------------------------------------

inline wstring GetSignalTypeByNumber(int iVal)
{
	std::set<pair<int, wstring>>::iterator it = std::find_if(SignalTypes.begin(), SignalTypes.end(), [iVal](const pair<int, wstring> element) { return element.first == iVal; });
	return it->second;
}

//----------------------------------------------------------------------------
//				Instruments
//----------------------------------------------------------------------------

//OSCILLATOR
#define OSCILLATOR				L"Oscillator"
#define MIX_OSCILLATOR		L"Mix"
#define SUM_OSCILLATOR		L"Sum"
#define SIGNAL_TYPE				L"Signal type"
#define PHASE_BIAS				L"Phase Bias"
#define DUTY_CYCLE				L"Duty cycle"
#define	UNISONE						L"Unisone"
#define	INCREMENT					L"Increment"

//LFO
#define LFO_A							L"Amplitude LFO"
#define LFO_F							L"Frequency LFO"
#define LFO_FREQUENCY			L"Frequency"
#define LFO_AMOUNT				L"Amount"

//ENVELOPE
#define	ENVELOPE_AMPL			L"Amplitude Envelope"
#define	ENVELOPE_FREQ			L"Frequency Section"
#define V_ATTACK					L"A Attack"
#define V_DECAY						L"A Decay"
#define V_SUSTAIN					L"A Sustain"
#define V_RELEASE					L"A Release"
#define T_ATTACK					L"T Attack"
#define T_DECAY						L"T Decay"
#define T_SUSTAIN					L"T Sustain"
#define T_RELEASE					L"T Release"

//FILTER
#define	FILTER						L"Filter"
#define	FILTER_MODE				L"Filter mode"
#define CUTOFF						L"CutOff"
#define RESONANCE					L"Resonance"
#define ENVELOPE					L"Envelope"

//----------------------------------------------------------------------------
//				FILTER MODE
//----------------------------------------------------------------------------

#define HIGHPASS_MODE			L"High pass"
#define LOWPASS_MODE			L"Low pass"

static std::set<pair<int, wstring>> FilterMods = { { 0, HIGHPASS_MODE },{ 1, LOWPASS_MODE }};

inline int GetFilterModeByString(wstring wstrType)
{
	std::set<pair<int, wstring>>::iterator it = std::find_if(FilterMods.begin(), FilterMods.end(), [wstrType](const pair<int, wstring> element) { return element.second == wstrType; });
	return it->first;
}

inline wstring GetFilterModeByNumber(int iVal)
{
	std::set<pair<int, wstring>>::iterator it = std::find_if(FilterMods.begin(), FilterMods.end(), [iVal](const pair<int, wstring> element) { return element.first == iVal; });
	return it->second;
}

//----------------------------------------------------------------------------
//				SETTING FILE
//----------------------------------------------------------------------------

#define NUMBER_OF_BLOCKS	L"Blocks"
#define BLOCK_SAMPLE			L"Block Sample"
#define CHANNELS					L"Channels"
#define SAMPLE_RATE				L"Sample Rate"
#define DEVICE_NUMBER			L"Device Number"

//----------------------------------------------------------------------------
//				NOTES
//----------------------------------------------------------------------------

#define C_KEY	L"C"
#define CSHARP_KEY	L"C#"
#define D_KEY	L"D"
#define DSHARP_KEY	L"D#"
#define E_KEY	L"E"
#define F_KEY	L"F"
#define FSHARP_KEY	L"F#"
#define G_KEY	L"G"
#define GSHARP_KEY	L"G#"
#define A_KEY	L"A"
#define ASHARP_KEY	L"A#"
#define H_KEY	L"H"

//----------------------------------------------------------------------------
//				ERRORS
//----------------------------------------------------------------------------

#define WMUSER_ERROR	WM_USER+1

#define	NO_MEMORY			L"Not enough memory. Please, reload app"

//----------------------------------------------------------------------------
//				PATTERNS
//----------------------------------------------------------------------------

template <typename T>
class CSingleton
{
public:
	static std::shared_ptr<T> Instance()
	{
		static std::shared_ptr<T> _instanse(new T());
		return _instanse;
	}
protected:
	CSingleton() {}
	~CSingleton() {}
public:
	CSingleton(CSingleton const &) = delete;
	CSingleton& operator=(CSingleton const &) = delete;
};

//----------------------------------------------------------------------------

class CSubject;

class CObserver
{
public:
	virtual ~CObserver() {}
	virtual void Update(CSubject* theChangedSubject) = 0;
protected:
	CObserver() {}
};

class CSubject
{
public:
	virtual ~CSubject() {}
	virtual void Attach(CObserver* o)
	{
		_observers.push_back(o);
	}

	virtual void Detach(CObserver* o)
	{
		std::vector<CObserver*>::iterator iter = find(_observers.begin(), _observers.end(), o);
		_observers.erase(iter);
	}

	virtual void Notify()
	{
		for (auto i : _observers)
		{
			i->Update(this);
		}
	}
protected:
	CSubject() {}
	std::vector<CObserver*> _observers;
};