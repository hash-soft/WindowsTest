// SDLibrarcpp : DLL 用にエクスポートされる関数を定義します。
//

#include "pch.h"
#include "framework.h"
#include "header.h"
#include "CTestDialog.h"
#include "CTestModelessDialog.h"
#include "resource.h"



MFCLIBRARY_API int DoModal(HWND hParent)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CWnd* parent = CWnd::FromHandle(hParent);
	CTestDialog a(parent);

	int result = a.DoModal();

	return result;
}


MFCLIBRARY_API HWND Create(HWND hParent) {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CWnd* parent = CWnd::FromHandle(hParent);
	CTestModelessDialog* a = new CTestModelessDialog();

	a->Initialize(parent);

	//HWND hCheck = a->GetParent()->GetSafeHwnd();
	//a->SetParent(nullptr);

	return a->GetSafeHwnd();
}