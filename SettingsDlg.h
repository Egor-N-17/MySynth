#pragma once
#include "afxwin.h"
#include <vector>
#include <string>
#include <mmeapi.h>
#include "PlayParams.h"
#include "FileManager.h"

using namespace std;


// CSettingsDlg dialog

class CSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingsDlg)

public:
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	void GetDevices(vector<wstring>& vecDevices);

	DECLARE_MESSAGE_MAP()
public:

	CComboBox m_ComboDevice;
	CComboBox m_ComboSampleRate;
	CComboBox m_ComboChannel;
	CComboBox m_ComboBlock;
	CComboBox m_ComboBlockSample;

	CEdit m_editBarFolder;
	CEdit m_editInstrumentFolder;

	CEdit m_editCKey;
	CEdit m_editCSharpKey;
	CEdit m_editDKey;
	CEdit m_editDSharpKey;
	CEdit m_editEKey;
	CEdit m_editFKey;
	CEdit m_editFSharpKey;
	CEdit m_editGKey;
	CEdit m_editGSharpKey;
	CEdit m_editAKey;
	CEdit m_editASharpKey;
	CEdit m_editHKey;

	afx_msg void OnBnClickedOk();
};
