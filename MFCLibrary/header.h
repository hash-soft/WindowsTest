// 以下の ifdef ブロックは、DLL からのエクスポートを容易にするマクロを作成するための
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された SDKLIBRARY_EXPORTS
// シンボルを使用してコンパイルされます。このシンボルは、この DLL を使用するプロジェクトでは定義できません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、
// SDKLIBRARY_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef MFCLIBRARY_EXPORTS
#define MFCLIBRARY_API __declspec(dllexport)
#else
#define MFCLIBRARY_API __declspec(dllimport)
#endif


extern "C" {

	MFCLIBRARY_API int DoModal(HWND hParent);

	MFCLIBRARY_API HWND Create(HWND hParent);
}