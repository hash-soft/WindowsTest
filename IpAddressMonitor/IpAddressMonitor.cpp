// WindowsTest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include <SDKDDKVer.h>
#include <Windows.h>
//#define WIN32_LEAN_AND_MEAN 
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
#include <Iphlpapi.h>
#include <iostream>
#include <IPTypes.h>
//#include <winsock2.h>
#pragma comment(lib, "Iphlpapi.lib")

/*
#define  GAA_FLAGS (GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_DNS_SERVER |\
					GAA_FLAG_SKIP_FRIENDLY_NAME | GAA_FLAG_SKIP_MULTICAST |\
					GAA_FLAG_SKIP_UNICAST)

#define WORKING_BUFFER_SIZE 15000

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

static DWORD IsInterfaceUp(void)
{
	IP_ADAPTER_ADDRESSES* pAdapters = NULL, * pipa;
	DWORD nBufferLength = WORKING_BUFFER_SIZE;
	DWORD ret;

	do
	{
		if (pAdapters != NULL)
			FREE(pAdapters);
		pAdapters = (IP_ADAPTER_ADDRESSES*)MALLOC(nBufferLength);
		if (pAdapters == NULL)
			return GetLastError();
		ret = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAGS, NULL, pAdapters, &nBufferLength);
	} while (ret == ERROR_BUFFER_OVERFLOW);

	if (ret != ERROR_SUCCESS)
	{
		FREE(pAdapters);
		return ret;
	}

	for (pipa = pAdapters; pipa != NULL; pipa = pipa->Next)
	{
		if (pipa->IfType == IF_TYPE_SOFTWARE_LOOPBACK) continue;
		if (pipa->IfType == IF_TYPE_TUNNEL) continue;
		if (pipa->OperStatus == IfOperStatusUp) break;
	}
	FREE(pAdapters);
	pAdapters = NULL;

	if (pipa != NULL)
		return ERROR_SUCCESS;

	return ERROR_NO_DATA;
}*/

int main() {
	// イベントオブジェクトの作成
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hand = NULL;
	if (hEvent == NULL) {
		std::cout << "CreateEvent failed with error: " << GetLastError() << std::endl;
		return -1;
	}
	// OVERLAPPED構造体の初期化
	OVERLAPPED ol;
	ZeroMemory(&ol, sizeof(ol));
	ol.hEvent = hEvent;
	// NotifyAddrChange関数で通知の登録
	DWORD dwRetVal = NotifyAddrChange(&hand, &ol);
	if (dwRetVal != NO_ERROR && dwRetVal != ERROR_IO_PENDING) {
		std::cout << "NotifyAddrChange failed with error: " << dwRetVal << std::endl;
		CloseHandle(hEvent);
		return -1;
	}
	// 無限ループでIPアドレスの変更を監視
	while (true) {
		// イベントオブジェクトの待機
		DWORD dwWaitResult = WaitForSingleObject(hEvent, INFINITE);
		if (dwWaitResult == WAIT_OBJECT_0) {
			// IPアドレスが変更されたことを出力
			std::cout << "IP address changed!" << std::endl;
			// NotifyAddrChange関数で通知の再登録
			dwRetVal = NotifyAddrChange(&hand, &ol);
			if (dwRetVal != NO_ERROR && dwRetVal != ERROR_IO_PENDING) {
				std::cout << "NotifyAddrChange failed with error: " << dwRetVal << std::endl;
				break;
			}
		}
		else {
			// エラー処理
			std::cout << "WaitForSingleObject failed with error: " << GetLastError() << std::endl;
			break;
		}
	}
	// イベントオブジェクトの解放CloseHandle(hEvent);
	return 0;
}


// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
