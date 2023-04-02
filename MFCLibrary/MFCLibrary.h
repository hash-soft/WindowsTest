// MFCLibrary.h : MFCLibrary DLL のメイン ヘッダー ファイル
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCLibraryApp
// このクラスの実装に関しては MFCLibrary.cpp をご覧ください
//

class CMFCLibraryApp : public CWinApp
{
public:
	CMFCLibraryApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
