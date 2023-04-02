#pragma once
#include "CTestDialog.h"


// CTestDialog ダイアログ

class CTestModelessDialog : public CTestDialog
{
	DECLARE_DYNAMIC(CTestModelessDialog)

public:
	CTestModelessDialog(CWnd* pParent = nullptr);   // 標準コンストラクター

	BOOL Initialize(CWnd* parent);


	// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void PostNcDestroy();

	DECLARE_MESSAGE_MAP()
};
