#pragma once
#include "afxdialogex.h"


// CTestDialog ダイアログ

class CTestDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTestDialog)

public:
	CTestDialog(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CTestDialog();

	// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
