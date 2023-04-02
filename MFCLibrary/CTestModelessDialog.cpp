// CTestDialog.cpp : 実装ファイル
//

#include "pch.h"
#include "MFCLibrary.h"
#include "afxdialogex.h"
#include "CTestModelessDialog.h"


// CTestDialog ダイアログ

IMPLEMENT_DYNAMIC(CTestModelessDialog, CTestDialog)

CTestModelessDialog::CTestModelessDialog(CWnd* pParent /*=nullptr*/)
	: CTestDialog(pParent)
{

}

BOOL CTestModelessDialog::Initialize(CWnd* parent) {
	this->Create(IDD_DIALOG1, parent);
	this->ShowWindow(SW_SHOW);
	this->UpdateWindow();
	return TRUE;
}



void CTestModelessDialog::PostNcDestroy()
{
	CTestDialog::PostNcDestroy();
	delete this;
}


BEGIN_MESSAGE_MAP(CTestModelessDialog, CTestDialog)
END_MESSAGE_MAP()




// CTestDialog メッセージ ハンドラー
