// Settings.cpp : implementation file
//

#include "stdafx.h"
#include "MySynth.h"
#include "SettingsDlg.h"
#include "afxdialogex.h"

// CSettingsDlg dialog

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialogEx)

CSettingsDlg::CSettingsDlg(CWnd* pParent /*= NULL*/)
	: CDialogEx(IDD_SETTINGS_DIALOG, pParent)
{
}

//----------------------------------------------------------------------------

CSettingsDlg::~CSettingsDlg()
{
}

//----------------------------------------------------------------------------

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICE, m_ComboDevice);
	DDX_Control(pDX, IDC_COMBO_SAMPLE_RATE, m_ComboSampleRate);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ComboChannel);
	DDX_Control(pDX, IDC_COMBO_BLOCKS, m_ComboBlock);
	DDX_Control(pDX, IDC_COMBO_BLOCK_SAMPLE, m_ComboBlockSample);

	DDX_Control(pDX, IDC_EDIT_C_NOTE, m_editCKey);
	DDX_Control(pDX, IDC_EDIT_C_SHARP_NOTE, m_editCSharpKey);
	DDX_Control(pDX, IDC_EDIT_D_NOTE, m_editDKey);
	DDX_Control(pDX, IDC_EDIT_D_SHARP_NOTE, m_editDSharpKey);
	DDX_Control(pDX, IDC_EDIT_E_NOTE, m_editEKey);
	DDX_Control(pDX, IDC_EDIT_F_NOTE, m_editFKey);
	DDX_Control(pDX, IDC_EDIT_F_SHARP_NOTE, m_editFSharpKey);
	DDX_Control(pDX, IDC_EDIT_G_NOTE, m_editGKey);
	DDX_Control(pDX, IDC_EDIT_G_SHARP_NOTE, m_editGSharpKey);
	DDX_Control(pDX, IDC_EDIT_A_NOTE, m_editAKey);
	DDX_Control(pDX, IDC_EDIT_A_SHARP_NOTE, m_editASharpKey);
	DDX_Control(pDX, IDC_EDIT_H_NOTE, m_editHKey);
}

//----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CSettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingsDlg::OnBnClickedOk)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------

// CSettings message handlers

BOOL CSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	shared_ptr<CPlayParams> pParams = CPlayParams::Instance();
	sPlayParams playParams;
	playParams = pParams->GetPlayParams();

	vector<wstring> vecDevices;
	GetDevices(vecDevices);

	for (auto device : vecDevices)
	{
		m_ComboDevice.AddString(device.c_str());
	}
	m_ComboDevice.SetCurSel(playParams.iDeviceNumber);

	m_ComboBlock.AddString(_T("8 bit"));
	m_ComboBlock.AddString(_T("16 bit"));
	m_ComboBlock.SetCurSel(playParams.iBlocks == 8 ? 0 : 1);

	m_ComboSampleRate.AddString(_T("8000"));
	m_ComboSampleRate.AddString(_T("11025"));
	m_ComboSampleRate.AddString(_T("12000"));
	m_ComboSampleRate.AddString(_T("16000"));
	m_ComboSampleRate.AddString(_T("22050"));
	m_ComboSampleRate.AddString(_T("32000"));
	m_ComboSampleRate.AddString(_T("44100"));
	m_ComboSampleRate.AddString(_T("48000"));
	m_ComboSampleRate.SetCurSel(m_ComboSampleRate.FindString(0, to_wstring(playParams.iSampleRate).c_str()));
	
	m_ComboChannel.AddString(_T("Mono"));
	m_ComboChannel.AddString(_T("Stereo"));
	m_ComboChannel.SetCurSel(playParams.iChannel == 1 ? 0 : 1);

	m_ComboBlockSample.AddString(_T("32"));
	m_ComboBlockSample.AddString(_T("64"));
	m_ComboBlockSample.AddString(_T("128"));
	m_ComboBlockSample.AddString(_T("256"));
	m_ComboBlockSample.AddString(_T("512"));
	m_ComboBlockSample.SetCurSel(m_ComboBlockSample.FindString(0, to_wstring(playParams.iBlockSample).c_str()));

	m_editCKey.SetLimitText(1);
	m_editCSharpKey.SetLimitText(1);
	m_editDKey.SetLimitText(1);
	m_editDSharpKey.SetLimitText(1);
	m_editEKey.SetLimitText(1);
	m_editFKey.SetLimitText(1);
	m_editFSharpKey.SetLimitText(1);
	m_editGKey.SetLimitText(1);
	m_editGSharpKey.SetLimitText(1);
	m_editAKey.SetLimitText(1);
	m_editASharpKey.SetLimitText(1);
	m_editHKey.SetLimitText(1);

	wchar_t chSymbol = MapVirtualKeyW(playParams.iC, MAPVK_VK_TO_CHAR);
	wstring wstrText;
	wstrText.push_back(chSymbol);
	m_editCKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iCSharp, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editCSharpKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iD, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editDKey.SetWindowText(wstrText.c_str());
	
	chSymbol = MapVirtualKeyW(playParams.iDSharp, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editDSharpKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iE, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editEKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iF, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editFKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iFSharp, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editFSharpKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iG, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editGKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iGSharp, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editGSharpKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iA, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editAKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iASharp, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editASharpKey.SetWindowText(wstrText.c_str());

	chSymbol = MapVirtualKeyW(playParams.iH, MAPVK_VK_TO_CHAR);
	wstrText[0] = chSymbol;
	m_editHKey.SetWindowText(wstrText.c_str());

	UpdateData(FALSE);


	return TRUE;
}

//----------------------------------------------------------------------------

void CSettingsDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();

	UpdateData(TRUE);
	sPlayParams playParams;

	CString cstrText;
	m_ComboSampleRate.GetWindowText(cstrText);
	playParams.iSampleRate = stoi(wstring(cstrText));

	m_ComboChannel.GetWindowText(cstrText);
	playParams.iChannel = wstring(cstrText) == L"Mono" ? 1 : 2;

	m_ComboBlock.GetWindowText(cstrText);
	playParams.iBlocks = wstring(cstrText) == L"8 bit" ? 8 : 16;

	m_ComboBlockSample.GetWindowText(cstrText);
	playParams.iBlockSample = stoi(wstring(cstrText));

	playParams.iDeviceNumber = m_ComboDevice.GetCurSel();

	m_editCKey.GetWindowText(cstrText);
	playParams.iC = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editCSharpKey.GetWindowText(cstrText);
	playParams.iCSharp = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editDKey.GetWindowText(cstrText);
	playParams.iD = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editDSharpKey.GetWindowText(cstrText);
	playParams.iDSharp = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editEKey.GetWindowText(cstrText);
	playParams.iE = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editFKey.GetWindowText(cstrText);
	playParams.iF = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editFSharpKey.GetWindowText(cstrText);
	playParams.iFSharp = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editGKey.GetWindowText(cstrText);
	playParams.iG = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editGSharpKey.GetWindowText(cstrText);
	playParams.iGSharp = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editAKey.GetWindowText(cstrText);
	playParams.iA = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editASharpKey.GetWindowText(cstrText);
	playParams.iASharp = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	m_editHKey.GetWindowText(cstrText);
	playParams.iH = MapVirtualKeyExW(towupper(cstrText[0]), MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));

	shared_ptr<CPlayParams> pParams = CPlayParams::Instance();
	pParams->SetPlayParams(playParams);

	shared_ptr<CFileManager> pFileManager = CFileManager::Instance();
	pFileManager->SaveParams(playParams);
}

//----------------------------------------------------------------------------

void CSettingsDlg::GetDevices(vector<wstring>& vecDevices)
{
	int iDeviceCount = waveOutGetNumDevs();
	WAVEOUTCAPS woc;
	for (int n = 0; n < iDeviceCount; n++)
		if (waveOutGetDevCaps(n, &woc, sizeof(WAVEOUTCAPS)) == S_OK)
			vecDevices.push_back(woc.szPname);
}