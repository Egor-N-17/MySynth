#include "stdafx.h"
#include "OscillatorDialog.h"

using namespace std;

IMPLEMENT_DYNAMIC(COscillatorDialog, CDialogEx)

COscillatorDialog::COscillatorDialog(CWnd* pParent, shared_ptr<COscillator> pInstrument) : CDialogEx(IDD_OSCILLATOR_DIALOG, pParent)
{
	if (pInstrument)
	{
		m_pOscillator = pInstrument;
	}
	else
	{
		m_pOscillator = make_shared<COscillator>();
	}
}

//----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(COscillatorDialog, CDialogEx)
	ON_CBN_SELENDOK(IDC_COMBO_SIGNAL_TYPE, &COscillatorDialog::OnSelectSignalType)
	ON_BN_CLICKED(IDOK, &COscillatorDialog::OnBnClickedOk)
	ON_CBN_SELENDOK(IDC_COMBO_UNISON, &COscillatorDialog::OnCbnSelectUnison)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------

void COscillatorDialog::DoDataExchange(CDataExchange * pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SIGNAL_TYPE, m_comboType);
	DDX_Control(pDX, IDC_EDIT_PHASE_BIAS, m_editPhaseBias);
	DDX_Control(pDX, IDC_EDIT_DUTY_CYCLE, m_editDutyCycle);
	DDX_Control(pDX, IDC_COMBO_UNISON, m_comboUnison);
	DDX_Control(pDX, IDC_EDIT_INCREMENT, m_editIncrement);
}


//----------------------------------------------------------------------------

COscillatorDialog::~COscillatorDialog()
{

}

//----------------------------------------------------------------------------

BOOL COscillatorDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_comboType.AddString(SIN_SIGNAL);
	m_comboType.AddString(SQUARE_SIGNAL);
	m_comboType.AddString(TRIANGLE_SIGNAL);
	m_comboType.AddString(SAW_SIGNAL);
	m_comboType.AddString(NOISE_SIGNAL);

	m_comboUnison.AddString(L"1");
	m_comboUnison.AddString(L"3");
	m_comboUnison.AddString(L"5");
	m_comboUnison.AddString(L"15");

	m_comboType.SetCurSel(
		m_comboType.FindStringExact(0, GetSignalTypeByNumber((int)m_pOscillator->GetParam(SIGNAL_TYPE)).c_str())
		);

	if (GetSignalTypeByNumber((int)m_pOscillator->GetParam(SIGNAL_TYPE)) == SQUARE_SIGNAL)
	{
		m_comboType.SetCurSel(1);
		m_editDutyCycle.SetWindowText(to_wstring(m_pOscillator->GetParam(DUTY_CYCLE)).c_str());
	}
	else
	{
		m_editDutyCycle.EnableWindow(FALSE);
	}

	m_comboUnison.SetCurSel(
	m_comboUnison.FindStringExact(0, to_wstring((int)m_pOscillator->GetParam(UNISONE)).c_str())
		);
	
	m_editPhaseBias.SetWindowText(to_wstring(m_pOscillator->GetParam(PHASE_BIAS)).c_str());
	m_editIncrement.SetWindowText(to_wstring(m_pOscillator->GetParam(INCREMENT)).c_str());

	UpdateData(TRUE);

	return 0;
}

//----------------------------------------------------------------------------

void COscillatorDialog::OnSelectSignalType()
{
	BOOL bRes = FALSE;
	wchar_t Text[MAX_PATH + 1] = L"";
	m_comboType.GetLBText(m_comboType.GetCurSel(), Text);
	wstring wstrText(Text);
	if (wstrText == SQUARE_SIGNAL)
	{
		bRes = TRUE;
	}
	else
	{
		bRes = FALSE;
	}
	m_editDutyCycle.EnableWindow(bRes);
	UpdateData(TRUE);
}

//----------------------------------------------------------------------------

void COscillatorDialog::OnBnClickedOk()
{
	CDialogEx::OnOK();
	UpdateData(FALSE);
	m_pOscillator->SetParam(DUTY_CYCLE, _wtof(GetTextFormControl(m_editDutyCycle).c_str()));
	m_pOscillator->SetParam(SIGNAL_TYPE, GetSignalTypeByString(GetTextFormControl(m_comboType).c_str()));
	m_pOscillator->SetParam(PHASE_BIAS, _wtof(GetTextFormControl(m_editPhaseBias).c_str()));
	m_pOscillator->SetParam(UNISONE, _wtoi(GetTextFormControl(m_comboUnison).c_str()));
	m_pOscillator->SetParam(INCREMENT, _wtoi(GetTextFormControl(m_editIncrement).c_str()));
}

//----------------------------------------------------------------------------

void COscillatorDialog::OnCbnSelectUnison()
{
	BOOL bRes = FALSE;
	wchar_t Text[MAX_PATH + 1] = L"";
	m_comboUnison.GetLBText(m_comboUnison.GetCurSel(), Text);
	wstring wstrText(Text);
	if (wstrText != L"1")
	{
		bRes = TRUE;
	}
	else
	{
		bRes = FALSE;
	}
	m_editIncrement.EnableWindow(bRes);
	UpdateData(TRUE);
}

//----------------------------------------------------------------------------

shared_ptr<COscillator> COscillatorDialog::GetOscillator()
{
	return m_pOscillator;
}
