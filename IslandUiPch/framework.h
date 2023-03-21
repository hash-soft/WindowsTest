#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
// Windows ヘッダー ファイル
#include <windows.h>
// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>    //DesktopWindowXamlSource

//名称かぶり対策（前半）ここから
#pragma push_macro("GetCurrentTime")
#pragma push_macro("TRY")
#undef GetCurrentTime
#undef TRY
//名称かぶり対策（前半）ここまで

#include <winrt/windows.ui.xaml.hosting.h>  //WindowsXamlManager
#include <winrt/windows.ui.xaml.markup.h>   //XamlReader
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/windows.ui.xaml.controls.primitives.h>  //Click
#include <winrt/windows.ui.xaml.media.h>    //SolidColorBrush
#include <winrt/windows.foundation.h>   //IAsyncAction
#include <winrt/windows.security.cryptography.h>    //CryptographicBuffer

//名称かぶり対策（後半）ここから
#pragma pop_macro("TRY")
#pragma pop_macro("GetCurrentTime")
//名称かぶり対策（後半）ここまで

#include <fstream>
