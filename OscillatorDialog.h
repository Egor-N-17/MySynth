#pragma once
#include "afxdialogex.h"
#include "MySynth.h"
#include "Instrument.h"
#include "Common.h"
#include <memory>


using namespace std;

class COscillatorDialog :	public CDialogEx
{
	DECLARE_DYNAMIC(COscillatorDialog)

public:
	COscillatorDialog(CWnd* pParent = NULL, shared_ptr<COscillator> pInstrument = nullptr);
	virtual ~COscillatorDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OSCILLATOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void OnSelectSignalType();

	CEdit m_editDutyCycle;
	CComboBox m_comboType;
	CComboBox m_comboUnison;
	CEdit m_editPhaseBias;
	CEdit m_editIncrement;

	shared_ptr<COscillator> m_pOscillator;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelectUnison();
	shared_ptr<COscillator> GetOscillator();
};

