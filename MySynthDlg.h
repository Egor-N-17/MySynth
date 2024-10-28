
// MySynthDlg.h : header file
//

#pragma once
#include "SettingsDlg.h"
#include "FileManager.h"
#include "OscillatorDialog.h"
#include "Play.h"
#include "NotePlayer.h"
#include "Instrument.h"

// CMySynthDlg dialog
class CMySynthDlg : public CDialogEx
{
// Construction
public:
	CMySynthDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSYNTH_DIALOG };
#endif

	protected:
	BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CMenu* m_pMenu;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	//KEYBOARD
	CButton m_butNoteC;
	CButton m_butNoteCSharp;
	CButton m_butNoteD;
	CButton m_butNoteDSharp;
	CButton m_butNoteE;
	CButton m_butNoteF;
	CButton m_butNoteFSharp;
	CButton m_butNoteG;
	CButton m_butNoteGSharp;
	CButton m_butNoteA;
	CButton m_butNoteASharp;
	CButton m_butNoteH;

	CStatic m_statStatus;

	void UpdateKeyBoard();
	void ActivateInstrumentControls(bool bActivate);

	//OSCILLATORS
	CListCtrl m_listOscillators;

	CButton m_butAddOscillator;
	CButton m_butEditOscillator;
	CButton m_butDeleteOscillator;

	CButton m_checkMix;
	CButton m_checkSum;

	CSliderCtrl m_sliderMix;

	void UpdateOscillators();

	//LFO FREQUENCY
	CComboBox m_comboSignalTypeFrequency;
	CSliderCtrl m_sliderLFOFFrequency;
	CSliderCtrl m_sliderLFOFAmount;

	//LFO AMPLITUDE
	CComboBox m_comboSignalTypeAmplitude;
	CSliderCtrl m_sliderLFOAFrequency;
	CSliderCtrl m_sliderLFOAAmount;

	//ENVELOPE
	CSliderCtrl m_sliderAttack;
	CSliderCtrl m_sliderDecay;
	CSliderCtrl m_sliderSustain;
	CSliderCtrl m_sliderRelease;

	CEdit m_editAttackTime;
	CEdit m_editDecayTime;
	CEdit m_editSustainTime;
	CEdit m_editReleaseTime;

	CEdit m_editFAttackTime;
	CEdit m_editFDecayTime;
	CEdit m_editFSustainTime;
	CEdit m_editFReleaseTime;

	//FILTERS
	CComboBox m_comboFilterType;
	CButton m_butFilterCheck;

	CSliderCtrl m_sliderCutoff;
	CSliderCtrl m_sliderResonance;
	CSliderCtrl m_sliderFilterEnvelope;

	CSliderCtrl m_sliderFAttack;
	CSliderCtrl m_sliderFDecay;
	CSliderCtrl m_sliderFSustain;
	CSliderCtrl m_sliderFRelease;

	void UpdateFilter(bool bActivate);
	void UpdateFilterEnvelope(bool bActivate);

	shared_ptr<CInstrument> m_pInstrument;
	shared_ptr<CNotePlayer> m_pNotePlayer;
	shared_ptr<CPlay> m_pPlay;
public:
	afx_msg void OnSettingsButton();
	afx_msg void OnBnClickPlay();
	afx_msg void OnBnClickStop();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar);
	
	afx_msg void OnBnClickedButtonAddOscillator();
	afx_msg void OnBnClickedButtonEditOscillator();
	afx_msg void OnBnClickedButtonDeleteOscillator();
	afx_msg void OnBnClickedCheckSum();
	afx_msg void OnBnClickedCheckMix();

	afx_msg void OnCbnSelchangeComboSignalTypeLfoA();

	afx_msg void OnCbnSelchangeComboSignalTypeLfoF();

	afx_msg void OnEnChangeEditAttackTime();
	afx_msg void OnEnChangeEditDecayTime();
	afx_msg void OnEnChangeEditSustainTime();
	afx_msg void OnEnChangeEditReleaseTime();

	afx_msg void OnBnClickedCheckFilterUse();
	afx_msg void OnCbnSelFilterType();

	afx_msg void OnEnChangeEditFAttackTime();
	afx_msg void OnEnChangeEditFDecayTime();
	afx_msg void OnEnChangeEditFSustainTime();
	afx_msg void OnEnChangeEditFReleaseTime();
};
