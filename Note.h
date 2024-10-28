#pragma once
#include "afxdialogex.h"
#include "Instrument.h"
#include <chrono>
#include <memory>
#include <chrono>

using namespace std;

class CInstrument;

class CNote
{
public:
	CNote(shared_ptr<CInstrument> pInstrument, int iNote);
	
	double Sound(double dCurrentTime);

	int GetNote();

	bool IsActive(double dCurTime);

	void ActivateNote(chrono::high_resolution_clock::time_point tStarPlay);
	void DeactivateNote();

private:
	void CalculateFrequency();

	int m_iNoteNumber;
	int m_iOctaveNumber;

	double m_dFrequency;

	double m_dKeyDown;
	double m_dKeyUp;
	double m_dEnvEnd;

	bool m_bButtonActive;
	bool m_bPlayActive;

	chrono::high_resolution_clock::time_point m_tStartRecord;

	shared_ptr<CInstrument> m_pInstrument;
};

