// CTestDialog.cpp : 実装ファイル
//

#include "pch.h"
#include "MFCLibrary.h"
#include "afxdialogex.h"
#include "CTestDialog.h"


// CTestDialog ダイアログ

IMPLEMENT_DYNAMIC(CTestDialog, CDialogEx)

CTestDialog::CTestDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CTestDialog::~CTestDialog()
{
}

void CTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestDialog, CDialogEx)
END_MESSAGE_MAP()


// CTestDialog メッセージ ハンドラー


BOOL CTestDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。

	return CDialogEx::PreTranslateMessage(pMsg);
}
