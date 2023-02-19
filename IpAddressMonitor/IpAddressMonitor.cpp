// WindowsTest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。

#include <winsock2.h>
#include <Iphlpapi.h>
#include <iostream>
#include "Utils.h"
#pragma comment(lib, "Iphlpapi.lib")




int main() {
	IsInterfaceUp();
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
