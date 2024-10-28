#pragma once
#include "PlayParams.h"
#include "Instrument.h"
#include "Note.h"
#include<mutex>

class CInstrument;
class CNote;

class CNotePlayer : public CObserver
{
public:
	CNotePlayer(shared_ptr<CInstrument> pInstrument);
	~CNotePlayer();

	void AddNote(MSG* pMsg);

	double Sound(double dCurrentTime);

	void Stop();

	void Update(CSubject* theChangedSubject);

	void SetStartTime();

protected:
	int ChooseNote(MSG* pMsg);

	shared_ptr<CInstrument> m_pInstrument;
	vector<shared_ptr<CNote>> m_activeNote;
	mutex m_mutAddNote;
	int m_iOctaveNumber;
	sPlayParams m_PlayParams;
	chrono::high_resolution_clock::time_point m_tStartPlay;
};

