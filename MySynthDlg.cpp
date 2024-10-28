
// MySynthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySynth.h"
#include "MySynthDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMySynthDlg dialog



CMySynthDlg::CMySynthDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYSYNTH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//----------------------------------------------------------------------------

void CMySynthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_STATUS, m_statStatus);

	//KEYBOARD
	DDX_Control(pDX, IDC_BUTTON_C_NOTE, m_butNoteC);
	DDX_Control(pDX, IDC_BUTTON_C_SHARP_NOTE, m_butNoteCSharp);
	DDX_Control(pDX, IDC_BUTTON_D_NOTE, m_butNoteD);
	DDX_Control(pDX, IDC_BUTTON_D_SHARP_NOTE, m_butNoteDSharp);
	DDX_Control(pDX, IDC_BUTTON_E_NOTE, m_butNoteE);
	DDX_Control(pDX, IDC_BUTTON_F_NOTE, m_butNoteF);
	DDX_Control(pDX, IDC_BUTTON_F_SHARP_NOTE, m_butNoteFSharp);
	DDX_Control(pDX, IDC_BUTTON_G_NOTE, m_butNoteG);
	DDX_Control(pDX, IDC_BUTTON_G_SHARP_NOTE, m_butNoteGSharp);
	DDX_Control(pDX, IDC_BUTTON_A_NOTE, m_butNoteA);
	DDX_Control(pDX, IDC_BUTTON_A_SHARP_NOTE, m_butNoteASharp);
	DDX_Control(pDX, IDC_BUTTON_H_NOTE, m_butNoteH);

	//OSCILLATOR
	DDX_Control(pDX, IDC_LIST_OSCILLATORS, m_listOscillators);
	DDX_Control(pDX, IDC_CHECK_SUM, m_checkSum);
	DDX_Control(pDX, IDC_CHECK_MIX, m_checkMix);
	DDX_Control(pDX, IDC_SLIDER_MIX, m_sliderMix);

	DDX_Control(pDX, IDC_BUTTON_ADD_OSCILLATOR, m_butAddOscillator);
	DDX_Control(pDX, IDC_BUTTON_EDIT_OSCILLATOR, m_butEditOscillator);
	DDX_Control(pDX, IDC_BUTTON_DELETE_OSCILLATOR, m_butDeleteOscillator);

	//ADSR Amplitude
	DDX_Control(pDX, IDC_SLIDER_ATTACK_ENV_A, m_sliderAttack);
	DDX_Control(pDX, IDC_SLIDER_DECAY_ENV_A, m_sliderDecay);
	DDX_Control(pDX, IDC_SLIDER_SUSTAIN_ENV_A, m_sliderSustain);
	DDX_Control(pDX, IDC_SLIDER_RELEASE_ENV_A, m_sliderRelease);

	DDX_Control(pDX, IDC_EDIT_ATTACK_TIME_ENV_A, m_editAttackTime);
	DDX_Control(pDX, IDC_EDIT_DECAY_TIME_ENV_A, m_editDecayTime);
	DDX_Control(pDX, IDC_EDIT_SUSTAIN_TIME_ENV_A, m_editSustainTime);
	DDX_Control(pDX, IDC_EDIT_RELEASE_TIME_ENV_A, m_editReleaseTime);

	//LFO
	DDX_Control(pDX, IDC_SLIDER_FREQ_LFO_F, m_sliderLFOFFrequency);
	DDX_Control(pDX, IDC_SLIDER_AMOUNT_LFO_F, m_sliderLFOFAmount);
	DDX_Control(pDX, IDC_COMBO_SIGNAL_TYPE_LFO_F, m_comboSignalTypeFrequency);

	DDX_Control(pDX, IDC_SLIDER_FREQ_LFO_A, m_sliderLFOAFrequency);
	DDX_Control(pDX, IDC_SLIDER_AMOUNT_LFO_A, m_sliderLFOAAmount);
	DDX_Control(pDX, IDC_COMBO_SIGNAL_TYPE_LFO_A, m_comboSignalTypeAmplitude);

	//FILTER
	DDX_Control(pDX, IDC_CHECK_FILTER_USE, m_butFilterCheck);
	DDX_Control(pDX, IDC_COMBO_FILTER_MODE, m_comboFilterType);

	DDX_Control(pDX, IDC_SLIDER_CUTOFF, m_sliderCutoff);
	DDX_Control(pDX, IDC_SLIDER_FILTER_RESONANCE, m_sliderResonance);
	DDX_Control(pDX, IDC_SLIDER_FILTER_ENVELOPE, m_sliderFilterEnvelope);

	//ADSR Filter
	DDX_Control(pDX, IDC_SLIDER_ATTACK_ENV_F, m_sliderFAttack);
	DDX_Control(pDX, IDC_SLIDER_DECAY_ENV_F, m_sliderFDecay);
	DDX_Control(pDX, IDC_SLIDER_SUSTAIN_ENV_F, m_sliderFSustain);
	DDX_Control(pDX, IDC_SLIDER_RELEASE_ENV_F, m_sliderFRelease);

	DDX_Control(pDX, IDC_EDIT_ATTACK_TIME_ENV_F, m_editFAttackTime);
	DDX_Control(pDX, IDC_EDIT_DECAY_TIME_ENV_F, m_editFDecayTime);
	DDX_Control(pDX, IDC_EDIT_SUSTAIN_TIME_ENV_F, m_editFSustainTime);
	DDX_Control(pDX, IDC_EDIT_RELEASE_TIME_ENV_F, m_editFReleaseTime);
}

//----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CMySynthDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_CTLCOLOR()

	//Menu
	ON_COMMAND(ID_SETTINGS_BUTTON, &CMySynthDlg::OnSettingsButton)
	ON_COMMAND(ID_PLAY, &CMySynthDlg::OnBnClickPlay)
	ON_COMMAND(ID_STOP, &CMySynthDlg::OnBnClickStop)

	//Oscillator
	ON_BN_CLICKED(IDC_BUTTON_ADD_OSCILLATOR, &CMySynthDlg::OnBnClickedButtonAddOscillator)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_OSCILLATOR, &CMySynthDlg::OnBnClickedButtonEditOscillator)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_OSCILLATOR, &CMySynthDlg::OnBnClickedButtonDeleteOscillator)
	ON_BN_CLICKED(IDC_CHECK_SUM, &CMySynthDlg::OnBnClickedCheckSum)
	ON_BN_CLICKED(IDC_CHECK_MIX, &CMySynthDlg::OnBnClickedCheckMix)

	//LFO Amplitude
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_TYPE_LFO_A, &CMySynthDlg::OnCbnSelchangeComboSignalTypeLfoA)

	//LFO Frequency
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_TYPE_LFO_F, &CMySynthDlg::OnCbnSelchangeComboSignalTypeLfoF)

	//Amplitude Envelope
	ON_EN_CHANGE(IDC_EDIT_ATTACK_TIME_ENV_A, &CMySynthDlg::OnEnChangeEditAttackTime)
	ON_EN_CHANGE(IDC_EDIT_DECAY_TIME_ENV_A, &CMySynthDlg::OnEnChangeEditDecayTime)
	ON_EN_CHANGE(IDC_EDIT_SUSTAIN_TIME_ENV_A, &CMySynthDlg::OnEnChangeEditSustainTime)
	ON_EN_CHANGE(IDC_EDIT_RELEASE_TIME_ENV_A, &CMySynthDlg::OnEnChangeEditReleaseTime)

	//FILTER
	ON_CBN_SELCHANGE(IDC_COMBO_FILTER_MODE, &CMySynthDlg::OnCbnSelFilterType)
	ON_BN_CLICKED(IDC_CHECK_FILTER_USE, &CMySynthDlg::OnBnClickedCheckFilterUse)

	//FILTER ENVELOPE
	ON_EN_CHANGE(IDC_EDIT_ATTACK_TIME_ENV_F, &CMySynthDlg::OnEnChangeEditFAttackTime)
	ON_EN_CHANGE(IDC_EDIT_DECAY_TIME_ENV_F, &CMySynthDlg::OnEnChangeEditFDecayTime)
	ON_EN_CHANGE(IDC_EDIT_SUSTAIN_TIME_ENV_F, &CMySynthDlg::OnEnChangeEditFSustainTime)
	ON_EN_CHANGE(IDC_EDIT_RELEASE_TIME_ENV_F, &CMySynthDlg::OnEnChangeEditFReleaseTime)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------

// CMySynthDlg message handlers

BOOL CMySynthDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_pMenu = theApp.GetMainWnd()->GetMenu();
	m_pMenu->EnableMenuItem(ID_SETTINGS_BUTTON, MF_ENABLED);
	m_pMenu->EnableMenuItem(ID_PLAY, MF_GRAYED);
	m_pMenu->EnableMenuItem(ID_STOP, MF_GRAYED);

	shared_ptr<CFileManager> pFileManager = CFileManager::Instance();
	pFileManager->LoadParams();

	m_pInstrument = make_shared<CInstrument>();

	UpdateKeyBoard();

	m_statStatus.SetWindowText(L"Stopped(add Oscillator to activate controls)");

	//OSCILLATORS
	CRect rect;
	GetClientRect(rect);
	m_listOscillators.InsertColumn(0, L"Type", LVCFMT_LEFT, (rect.Width() - 200) / 5);
	m_listOscillators.InsertColumn(1, L"Phase Bias", LVCFMT_LEFT, (rect.Width() - 200) / 5);
	m_listOscillators.InsertColumn(2, L"Duty Cycle", LVCFMT_LEFT, (rect.Width() - 200) / 5);
	m_listOscillators.InsertColumn(3, L"Unison", LVCFMT_LEFT, (rect.Width() - 200) / 5);
	m_listOscillators.InsertColumn(4, L"Increment", LVCFMT_LEFT, (rect.Width() - 200) / 5);

	m_sliderMix.SetRangeMax(MIX_RATIO);

	//LFO
	m_comboSignalTypeAmplitude.AddString(SIN_SIGNAL);
	m_comboSignalTypeAmplitude.AddString(SQUARE_SIGNAL);
	m_comboSignalTypeAmplitude.AddString(TRIANGLE_SIGNAL);
	m_comboSignalTypeAmplitude.AddString(SAW_SIGNAL);

	m_comboSignalTypeFrequency.AddString(SIN_SIGNAL);
	m_comboSignalTypeFrequency.AddString(SQUARE_SIGNAL);
	m_comboSignalTypeFrequency.AddString(TRIANGLE_SIGNAL);
	m_comboSignalTypeFrequency.AddString(SAW_SIGNAL);

	//ENVELOPE
	m_sliderAttack.SetRange(0, MIX_RATIO, TRUE);
	m_sliderAttack.SetPos(MIX_RATIO);
	m_sliderAttack.EnableWindow(FALSE);

	m_sliderDecay.SetRange(0, MIX_RATIO, TRUE);
	m_sliderDecay.SetPos(MIX_RATIO);
	m_sliderDecay.EnableWindow(FALSE);

	m_sliderSustain.SetRange(0, MIX_RATIO, TRUE);
	m_sliderSustain.SetPos(0);
	m_sliderSustain.EnableWindow(FALSE);

	m_sliderRelease.SetRange(0, MIX_RATIO, TRUE);
	m_sliderRelease.SetPos(MIX_RATIO);
	m_sliderRelease.EnableWindow(FALSE);

	m_editAttackTime.EnableWindow(FALSE);
	m_editDecayTime.EnableWindow(FALSE);
	m_editSustainTime.EnableWindow(FALSE);
	m_editReleaseTime.EnableWindow(FALSE);

	//FILTER
	m_comboFilterType.AddString(LOWPASS_MODE);
	m_comboFilterType.AddString(HIGHPASS_MODE);
	m_comboFilterType.SetCurSel(0);
	m_comboFilterType.EnableWindow(FALSE);

	m_sliderCutoff.SetRange(20, FILTER_FREQUENCIES, TRUE);
	m_sliderCutoff.EnableWindow(FALSE);

	m_sliderResonance.SetRange(QUALITY_FACTOR_MIN, QUALITY_FACTOR_MAX, TRUE);
	m_sliderResonance.EnableWindow(FALSE);

	m_sliderFilterEnvelope.SetRange(1, 10, TRUE);
	m_sliderFilterEnvelope.SetPos(1);
	m_sliderFilterEnvelope.EnableWindow(FALSE);

	m_sliderFilterEnvelope.SetRange(0, 10, TRUE);
	m_sliderFilterEnvelope.SetPos(1);
	m_sliderFilterEnvelope.EnableWindow(FALSE);

	m_sliderFAttack.SetRange(0, FILTER_RATIO, TRUE);
	m_sliderFAttack.SetPos(FILTER_RATIO);
	m_sliderFAttack.EnableWindow(FALSE);

	m_sliderFDecay.SetRange(0, FILTER_RATIO, TRUE);
	m_sliderFDecay.SetPos(FILTER_RATIO);
	m_sliderFDecay.EnableWindow(FALSE);

	m_sliderFSustain.SetRange(0, FILTER_RATIO, TRUE);
	m_sliderFSustain.SetPos(0);
	m_sliderFSustain.EnableWindow(FALSE);

	m_sliderFRelease.SetRange(0, FILTER_RATIO, TRUE);
	m_sliderFRelease.SetPos(FILTER_RATIO);

	DWORD dwStyleEx = m_listOscillators.GetExtendedStyle();
	dwStyleEx |= LVS_EX_FULLROWSELECT;
	dwStyleEx |= LVS_OWNERDATA;
	m_listOscillators.SetExtendedStyle(dwStyleEx);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

//----------------------------------------------------------------------------

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMySynthDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//----------------------------------------------------------------------------

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMySynthDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//----------------------------------------------------------------------------

void CMySynthDlg::UpdateKeyBoard()
{
	shared_ptr<CPlayParams> pPlayParams = CPlayParams::Instance();
	sPlayParams playParams = pPlayParams->GetPlayParams();

	wchar_t chSymbol = MapVirtualKeyW(playParams.iC, MAPVK_VK_TO_CHAR);
	wstring wstrText = L"C []";
	wstrText.insert(wstrText.begin() + 3, chSymbol);
	m_butNoteC.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iCSharp, MAPVK_VK_TO_CHAR);
	wstrText = L"C# []";
	wstrText.insert(wstrText.begin() + 4, chSymbol);
	m_butNoteCSharp.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iD, MAPVK_VK_TO_CHAR);
	wstrText = L"D []";
	wstrText.insert(wstrText.begin() + 3, chSymbol);
	m_butNoteD.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iDSharp, MAPVK_VK_TO_CHAR);
	wstrText = L"D# []";
	wstrText.insert(wstrText.begin() + 4, chSymbol);
	m_butNoteDSharp.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iE, MAPVK_VK_TO_CHAR);
	wstrText = L"E []";
	wstrText.insert(wstrText.begin() + 3, chSymbol);
	m_butNoteE.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iF, MAPVK_VK_TO_CHAR);
	wstrText = L"F []";
	wstrText.insert(wstrText.begin() + 3, chSymbol);
	m_butNoteF.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iFSharp, MAPVK_VK_TO_CHAR);
	wstrText = L"F# []";
	wstrText.insert(wstrText.begin() + 4, chSymbol);
	m_butNoteFSharp.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iG, MAPVK_VK_TO_CHAR);
	wstrText = L"G []";
	wstrText.insert(wstrText.begin() + 3, chSymbol);
	m_butNoteG.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iGSharp, MAPVK_VK_TO_CHAR);
	wstrText = L"G# []";
	wstrText.insert(wstrText.begin() + 4, chSymbol);
	m_butNoteGSharp.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iA, MAPVK_VK_TO_CHAR);
	wstrText = L"A []";
	wstrText.insert(wstrText.begin() + 3, chSymbol);
	m_butNoteA.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iASharp, MAPVK_VK_TO_CHAR);
	wstrText = L"A# []";
	wstrText.insert(wstrText.begin() + 4, chSymbol);
	m_butNoteASharp.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iH, MAPVK_VK_TO_CHAR);
	wstrText = L"H []";
	wstrText.insert(wstrText.begin()+3,chSymbol);
	m_butNoteH.SetWindowText(wstrText.c_str());
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnSettingsButton()
{
	CSettingsDlg dlg;
	dlg.DoModal();
	UpdateKeyBoard();
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnBnClickPlay()
{
	m_pPlay->Start();
	m_pMenu->EnableMenuItem(ID_SETTINGS_BUTTON, MF_GRAYED);
	m_pMenu->EnableMenuItem(ID_PLAY, MF_GRAYED);
	m_pMenu->EnableMenuItem(ID_STOP, MF_ENABLED);
	m_statStatus.SetWindowText(L"Played(press Esc to stop)");
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnBnClickStop()
{
	m_pPlay->Stop();
	m_pMenu->EnableMenuItem(ID_SETTINGS_BUTTON, MF_ENABLED);
	m_pMenu->EnableMenuItem(ID_PLAY, MF_ENABLED);
	m_pMenu->EnableMenuItem(ID_STOP, MF_GRAYED);
	m_statStatus.SetWindowText(L"Stopped(press Enter to play)");
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnBnClickedButtonAddOscillator()
{
	int iOscNumber = m_pInstrument->GetNumberOfOscillator();
	COscillatorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_pInstrument->SetOscillator(dlg.GetOscillator());
		UpdateOscillators();
		if (iOscNumber == 0)
		{
			m_pNotePlayer = make_shared<CNotePlayer>(m_pInstrument);
			m_pPlay = make_shared<CPlay>(m_pNotePlayer, &m_hWnd);
		}

		ActivateInstrumentControls(TRUE);
	}
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnBnClickedButtonEditOscillator()
{
	int i = m_listOscillators.GetSelectionMark();
	if (i != -1)
	{
		COscillatorDialog dlg(NULL, m_pInstrument->GetOscillator(i));
		if (dlg.DoModal() == IDOK)
		{
			UpdateOscillators();
		}
	}
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnBnClickedButtonDeleteOscillator()
{
	int i = m_listOscillators.GetSelectionMark();
	if (i != -1)
	{
		m_pInstrument->DeleteOscillator(i);
		if (m_pInstrument->GetNumberOfOscillator() == 0)
		{
			if (m_pPlay->IsPlay())
			{
				m_pPlay->Stop();
			}
			m_pPlay.reset();
			m_pNotePlayer.reset();
			m_statStatus.SetWindowText(L"Stopped(add Oscillator to activate controls)");
		}
		UpdateOscillators();
	}
}

//----------------------------------------------------------------------------

void CMySynthDlg::UpdateOscillators()
{
	if (m_pInstrument->IsMix())
	{
		m_checkMix.SetCheck(TRUE);
		m_sliderMix.EnableWindow(TRUE);
		m_sliderMix.SetPos((int)(MIX_RATIO * m_pInstrument->GetParam(MIX_OSCILLATOR)));
		m_checkSum.SetCheck(FALSE);
	}
	else
	{
		m_checkSum.EnableWindow(TRUE);
		m_checkSum.SetCheck(TRUE);
		if (m_pInstrument->GetNumberOfOscillator() == MAX_NUMBER_OF_SCILLATORS)
		{
			m_checkMix.SetCheck(FALSE);
			m_checkMix.EnableWindow(TRUE);
			m_butAddOscillator.EnableWindow(FALSE);
		}
		else
		{
			m_checkMix.SetCheck(FALSE);
			m_checkMix.EnableWindow(FALSE);
			m_butAddOscillator.EnableWindow(TRUE);
			m_sliderMix.EnableWindow(FALSE);
		}
	}
	m_listOscillators.DeleteAllItems();
	if (m_pInstrument->GetNumberOfOscillator() != 0)
	{
		for (int i = 0; i < m_pInstrument->GetNumberOfOscillator(); i++)
		{
			shared_ptr<COscillator> pOsc = m_pInstrument->GetOscillator(i);
			m_listOscillators.InsertItem(i, GetSignalTypeByNumber((int)pOsc->GetParam(SIGNAL_TYPE)).c_str());
			m_listOscillators.SetItemText(i, 1, to_wstring(pOsc->GetParam(PHASE_BIAS)).c_str());
			m_listOscillators.SetItemText(i, 2, to_wstring(pOsc->GetParam(DUTY_CYCLE)).c_str());
			m_listOscillators.SetItemText(i, 3, to_wstring(pOsc->GetParam(UNISONE)).c_str());
			m_listOscillators.SetItemText(i, 4, to_wstring(pOsc->GetParam(INCREMENT)).c_str());
		}
		ActivateInstrumentControls(TRUE);
		m_butEditOscillator.EnableWindow(TRUE);
		m_butDeleteOscillator.EnableWindow(TRUE);
	}
	else
	{
		m_checkSum.EnableWindow(FALSE);
		m_butEditOscillator.EnableWindow(FALSE);
		m_butDeleteOscillator.EnableWindow(FALSE);
		ActivateInstrumentControls(FALSE);
	}
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnBnClickedCheckSum()
{
	if ((m_checkSum.GetState() & BST_CHECKED) != 0)
	{
		m_pInstrument->SetInstrument(MIX_OSCILLATOR);
		m_checkMix.SetCheck(FALSE);
		m_sliderMix.EnableWindow(FALSE);
	}
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnBnClickedCheckMix()
{
	if ((m_checkMix.GetState() & BST_CHECKED) != 0)
	{
		m_pInstrument->SetInstrument(MIX_OSCILLATOR);
		m_sliderMix.EnableWindow(TRUE);
		m_sliderMix.SetPos((int)(m_pInstrument->GetParam(MIX_OSCILLATOR)*MIX_RATIO));
		m_checkSum.SetCheck(FALSE);
	}
}

//----------------------------------------------------------------------------

BOOL CMySynthDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_pPlay)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			OnBnClickStop();
			return 0;
		}
		else if(m_pPlay->IsPlay())
		{
			m_pNotePlayer->AddNote(pMsg);
			return 0;
		}
		if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickPlay();
			return 0;
		}
	}

	return 0;
}

//----------------------------------------------------------------------------

void CMySynthDlg::ActivateInstrumentControls(bool bActivate)
{
	m_pMenu->EnableMenuItem(ID_PLAY, bActivate ? MF_ENABLED : MF_GRAYED);

	m_sliderAttack.EnableWindow(bActivate);
	m_sliderDecay.EnableWindow(bActivate);
	m_sliderSustain.EnableWindow(bActivate);
	m_sliderRelease.EnableWindow(bActivate);

	m_editAttackTime.EnableWindow(bActivate);
	m_editDecayTime.EnableWindow(bActivate);
	m_editSustainTime.EnableWindow(bActivate);
	m_editReleaseTime.EnableWindow(bActivate);

	m_sliderLFOAFrequency.EnableWindow(bActivate);
	m_sliderLFOAAmount.EnableWindow(bActivate);
	m_comboSignalTypeAmplitude.EnableWindow(bActivate);
	if (bActivate)
	{
		m_comboSignalTypeAmplitude.SetCurSel(
			m_comboSignalTypeAmplitude.FindStringExact(0, GetSignalTypeByNumber((int)m_pInstrument->GetParamFromInstrument(LFO_A, SIGNAL_TYPE)).c_str())
			);

		m_editAttackTime.SetWindowTextW(to_wstring(m_pInstrument->GetParamFromInstrument(ENVELOPE_AMPL, T_ATTACK)).c_str());
		m_editDecayTime.SetWindowTextW(to_wstring(m_pInstrument->GetParamFromInstrument(ENVELOPE_AMPL, T_DECAY)).c_str());
		m_editSustainTime.SetWindowTextW(to_wstring(m_pInstrument->GetParamFromInstrument(ENVELOPE_AMPL, T_SUSTAIN)).c_str());
		m_editReleaseTime.SetWindowTextW(to_wstring(m_pInstrument->GetParamFromInstrument(ENVELOPE_AMPL, T_RELEASE)).c_str());
	}

	m_sliderLFOFFrequency.EnableWindow(bActivate);
	m_sliderLFOFAmount.EnableWindow(bActivate);
	m_comboSignalTypeFrequency.EnableWindow(bActivate);
	if (bActivate)
	{
		m_comboSignalTypeFrequency.SetCurSel(
			m_comboSignalTypeFrequency.FindStringExact(0, GetSignalTypeByNumber((int)m_pInstrument->GetParamFromInstrument(LFO_F, SIGNAL_TYPE)).c_str())
			);
	}

	m_butFilterCheck.EnableWindow(bActivate);
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnCbnSelchangeComboSignalTypeLfoA()
{
	wchar_t Text[MAX_PATH + 1] = L"";
	m_comboSignalTypeAmplitude.GetLBText(m_comboSignalTypeAmplitude.GetCurSel(), Text);
	m_pInstrument->SetParamToInstrument(LFO_A, SIGNAL_TYPE, _wtof(Text));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnCbnSelchangeComboSignalTypeLfoF()
{
	wchar_t Text[MAX_PATH + 1] = L"";
	m_comboSignalTypeFrequency.GetLBText(m_comboSignalTypeFrequency.GetCurSel(), Text);
	m_pInstrument->SetParamToInstrument(LFO_F, SIGNAL_TYPE, _wtof(Text));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar)
{
	double dRes = 0;
	if (pScrollBar == (CScrollBar*)&m_sliderMix)
	{
		dRes = m_sliderMix.GetPos();
		dRes = dRes / MIX_RATIO;
		m_pInstrument->SetParam(MIX_OSCILLATOR, dRes);
	}

	if (pScrollBar == (CScrollBar*)&m_sliderLFOFFrequency)
	{
		dRes = m_sliderLFOFFrequency.GetPos();
		m_pInstrument->SetParamToInstrument(LFO_F, LFO_FREQUENCY,dRes);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderLFOFAmount)
	{
		dRes = m_sliderLFOFAmount.GetPos();
		dRes = dRes / LFO_AMOUNT_MAX;
		m_pInstrument->SetParamToInstrument(LFO_F, LFO_AMOUNT, dRes);
	}

	if (pScrollBar == (CScrollBar*)&m_sliderLFOAFrequency)
	{
		dRes = m_sliderLFOAFrequency.GetPos();
		m_pInstrument->SetParamToInstrument(LFO_A, LFO_FREQUENCY, dRes);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderLFOAAmount)
	{
		dRes = m_sliderLFOAAmount.GetPos();
		dRes = dRes / LFO_AMOUNT_MAX;
		m_pInstrument->SetParamToInstrument(LFO_A, LFO_AMOUNT, dRes);
	}

	if (pScrollBar == (CScrollBar*)&m_sliderCutoff)
	{
		dRes = m_sliderCutoff.GetPos();
		m_pInstrument->SetParamToInstrument(FILTER, CUTOFF, dRes);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderResonance)
	{
		dRes = m_sliderResonance.GetPos();
		m_pInstrument->SetParamToInstrument(FILTER, RESONANCE, dRes / FILTER_RATIO);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderFilterEnvelope)
	{
		dRes = m_sliderFilterEnvelope.GetPos();
		m_pInstrument->SetParamToInstrument(ENVELOPE_FREQ, ENVELOPE, dRes);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar)
{
	double dRes = 0;

	if (pScrollBar == (CScrollBar*)&m_sliderAttack)
	{
		dRes = m_sliderAttack.GetPos();
		dRes = 1 - dRes / MIX_RATIO;
		m_pInstrument->SetParamToInstrument(ENVELOPE_AMPL, V_ATTACK, dRes);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderDecay)
	{
		dRes = m_sliderDecay.GetPos();
		dRes = 1 - dRes / MIX_RATIO;
		m_pInstrument->SetParamToInstrument(ENVELOPE_AMPL, V_DECAY, dRes);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderSustain)
	{
		dRes = m_sliderSustain.GetPos();
		dRes = 1 - dRes / MIX_RATIO;
		m_pInstrument->SetParamToInstrument(ENVELOPE_AMPL, V_SUSTAIN, dRes);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderRelease)
	{
		dRes = m_sliderRelease.GetPos();
		dRes = 1 - dRes / MIX_RATIO;
		m_pInstrument->SetParamToInstrument(ENVELOPE_AMPL, V_RELEASE, dRes);
	}

	if (pScrollBar == (CScrollBar*)&m_sliderFAttack)
	{
		dRes = FILTER_RATIO - m_sliderFAttack.GetPos();
		m_pInstrument->SetParamToInstrument(ENVELOPE_FREQ, V_ATTACK, dRes);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderFDecay)
	{
		dRes = FILTER_RATIO - m_sliderFDecay.GetPos();
		m_pInstrument->SetParamToInstrument(ENVELOPE_FREQ, V_DECAY, dRes);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderFSustain)
	{
		dRes = FILTER_RATIO - m_sliderFSustain.GetPos();
		m_pInstrument->SetParamToInstrument(ENVELOPE_FREQ, V_SUSTAIN, dRes);
	}
	if (pScrollBar == (CScrollBar*)&m_sliderFRelease)
	{
		dRes = FILTER_RATIO - m_sliderFRelease.GetPos();
		m_pInstrument->SetParamToInstrument(ENVELOPE_FREQ, V_RELEASE, dRes);
	}


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


//----------------------------------------------------------------------------

void CMySynthDlg::OnEnChangeEditAttackTime()
{
	m_pInstrument->SetParamToInstrument(ENVELOPE_AMPL, T_ATTACK,_wtof(GetTextFormControl(m_editAttackTime).c_str()));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnEnChangeEditDecayTime()
{
	m_pInstrument->SetParamToInstrument(ENVELOPE_AMPL, T_DECAY, _wtof(GetTextFormControl(m_editDecayTime).c_str()));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnEnChangeEditSustainTime()
{
	m_pInstrument->SetParamToInstrument(ENVELOPE_AMPL, T_SUSTAIN, _wtof(GetTextFormControl(m_editSustainTime).c_str()));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnEnChangeEditReleaseTime()
{
	m_pInstrument->SetParamToInstrument(ENVELOPE_AMPL, T_RELEASE, _wtof(GetTextFormControl(m_editReleaseTime).c_str()));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnBnClickedCheckFilterUse()
{
	bool bRes;
	if (m_pInstrument->IsFilterUse() == false)
	{
		m_pInstrument->UseFilter();
		bRes = true;
	}
	else
	{
		m_pInstrument->UnuseFilter();
		bRes = false;
	}
	UpdateFilter(bRes);
}

//----------------------------------------------------------------------------

void CMySynthDlg::UpdateFilter(bool bActivate)
{
	m_butFilterCheck.SetCheck(bActivate);
	m_comboFilterType.EnableWindow(bActivate);
	m_sliderCutoff.EnableWindow(bActivate);
	m_sliderResonance.EnableWindow(bActivate);
	m_sliderFilterEnvelope.EnableWindow(bActivate);

	if (bActivate)
	{
		m_comboFilterType.SetCurSel(
			m_comboFilterType.FindString(0, GetFilterModeByNumber((int)m_pInstrument->GetParamFromInstrument(FILTER, FILTER_MODE)).c_str())
			);

		m_sliderCutoff.SetPos((int)m_pInstrument->GetParamFromInstrument(FILTER, CUTOFF));
		m_sliderResonance.SetPos((int)m_pInstrument->GetParamFromInstrument(FILTER, RESONANCE));
		m_sliderFilterEnvelope.SetPos((int)m_pInstrument->GetParamFromInstrument(FILTER, ENVELOPE));
	}
	UpdateFilterEnvelope(bActivate);
}

//----------------------------------------------------------------------------

void CMySynthDlg::UpdateFilterEnvelope(bool bActivate)
{
	m_sliderFAttack.EnableWindow(bActivate);
	m_sliderFDecay.EnableWindow(bActivate);
	m_sliderFSustain.EnableWindow(bActivate);
	m_sliderFRelease.EnableWindow(bActivate);
	m_editFAttackTime.EnableWindow(bActivate);
	m_editFDecayTime.EnableWindow(bActivate);
	m_editFSustainTime.EnableWindow(bActivate);
	m_editFReleaseTime.EnableWindow(bActivate);

	if (bActivate)
	{
		m_sliderFAttack.SetPos((int)(FILTER_RATIO - m_pInstrument->GetParamFromInstrument(ENVELOPE_FREQ, V_ATTACK)));
		m_sliderFDecay.SetPos((int)(FILTER_RATIO - m_pInstrument->GetParamFromInstrument(ENVELOPE_FREQ, V_DECAY)));
		m_sliderFSustain.SetPos((int)(FILTER_RATIO - m_pInstrument->GetParamFromInstrument(ENVELOPE_FREQ, V_SUSTAIN)));
		m_sliderFRelease.SetPos((int)(FILTER_RATIO - m_pInstrument->GetParamFromInstrument(ENVELOPE_FREQ, V_RELEASE)));

		m_editFAttackTime.SetWindowTextW(to_wstring(m_pInstrument->GetParamFromInstrument(ENVELOPE_FREQ, T_ATTACK)).c_str());
		m_editFDecayTime.SetWindowTextW(to_wstring(m_pInstrument->GetParamFromInstrument(ENVELOPE_FREQ, T_DECAY)).c_str());
		m_editFSustainTime.SetWindowTextW(to_wstring(m_pInstrument->GetParamFromInstrument(ENVELOPE_FREQ, T_SUSTAIN)).c_str());
		m_editFReleaseTime.SetWindowTextW(to_wstring(m_pInstrument->GetParamFromInstrument(ENVELOPE_FREQ, T_RELEASE)).c_str());
	}
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnCbnSelFilterType()
{
	wchar_t Text[MAX_PATH + 1] = L"";
	m_comboFilterType.GetLBText(m_comboFilterType.GetCurSel(), Text);
	m_pInstrument->SetParamToInstrument(FILTER, FILTER_MODE, GetFilterModeByString(Text));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnEnChangeEditFAttackTime()
{
	m_pInstrument->SetParamToInstrument(ENVELOPE_FREQ, T_ATTACK,_wtof(GetTextFormControl(m_editFAttackTime).c_str()));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnEnChangeEditFDecayTime()
{
	m_pInstrument->SetParamToInstrument(ENVELOPE_FREQ, T_DECAY, _wtof(GetTextFormControl(m_editFDecayTime).c_str()));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnEnChangeEditFSustainTime()
{
	m_pInstrument->SetParamToInstrument(ENVELOPE_FREQ, T_SUSTAIN, _wtof(GetTextFormControl(m_editFSustainTime).c_str()));
}

//----------------------------------------------------------------------------

void CMySynthDlg::OnEnChangeEditFReleaseTime()
{
	m_pInstrument->SetParamToInstrument(ENVELOPE_FREQ, T_RELEASE, _wtof(GetTextFormControl(m_editFReleaseTime).c_str()));
}

//----------------------------------------------------------------------------

LRESULT CMySynthDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WMUSER_ERROR)
	{
		m_statStatus.SetWindowText(L"Stopped due error.Please, restart app");

		return 0;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}