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