// IslandUiPch.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "pch.h"
#include "framework.h"
#include "IslandUiPch.h"



using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Xaml::Markup;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::Foundation;
using namespace Windows::Security::Cryptography;



LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
IAsyncAction OnButtonClick(IInspectable const&, RoutedEventArgs const&);

HWND _hWnd;
HWND _hWndXamlIsland = nullptr;
XamlRoot _xamlroot = { nullptr };

//名前からコントロールを特定するテンプレート
template<typename T> T Element(const WCHAR* name) {
	return _xamlroot.Content().as<Page>().FindName(name).as<T>();
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
	//ウインドウクラス登録
	const TCHAR szWindowClass[] = TEXT("Win32DesktopApp");
	WNDCLASSEX windowClass = {};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = szWindowClass;
	windowClass.hbrBackground = (HBRUSH)NULL_BRUSH;// (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.hIconSm = ::LoadIcon(nullptr, IDI_APPLICATION);
	windowClass.lpszMenuName = MAKEINTRESOURCEW(IDC_ISLANDUIPCH);
	if (::RegisterClassEx(&windowClass) == 0) {
		::MessageBox(nullptr, TEXT("Windows registration failed!"), TEXT("Error"), MB_OK);
		return 0;
	}

	//ウインドウ作成
	_hWnd = ::CreateWindow(
		szWindowClass,
		TEXT("Windows c++ Win32 Desktop App"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);
	if (_hWnd == nullptr) {
		::MessageBox(nullptr, TEXT("Call to CreateWindow failed!"), TEXT("Error"), MB_OK);
		return 0;
	}

	//C++/WinRTのおまじない
	init_apartment(apartment_type::single_threaded);
	WindowsXamlManager winxamlmanager = WindowsXamlManager::InitializeForCurrentThread();

	//XAMLホスト準備
	DesktopWindowXamlSource desktopSource;
	auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
	check_hresult(interop->AttachToWindow(_hWnd));
	interop->get_WindowHandle(&_hWndXamlIsland);

	//XAMLホストのサイズをメインウインドウに合わせる
	RECT rcClient;
	::GetClientRect(_hWnd, &rcClient);
	::SetWindowPos(_hWndXamlIsland, nullptr, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, SWP_SHOWWINDOW);


	std::vector<uint8_t> xaml_array;
	std::ifstream file("XMLFile.xml", std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		xaml_array.assign(std::istreambuf_iterator<char>{file}, {});
		file.close();
	}
	else {
		::MessageBox(nullptr, TEXT("FileOpen failed!"), TEXT("Error"), MB_OK);
		return 0;
	}

	//XAMLコードを取り出してXAMLホストにセット
	auto xaml_buf = CryptographicBuffer::CreateFromByteArray(xaml_array);
	auto xamlstr = CryptographicBuffer::ConvertBinaryToString(BinaryStringEncoding::Utf8, xaml_buf);
	auto xamlContainer = XamlReader::Load(xamlstr).as<Page>();
	desktopSource.Content(xamlContainer);
	_xamlroot = xamlContainer.XamlRoot();

	//_xamlroot.Content().as<Page>().find
	auto count = VisualTreeHelper::GetChildrenCount(_xamlroot.Content().as<Page>().FindName(L"grid1").as<Grid>());
	//auto g = _xamlroot.Content();

	//auto element = VisualTreeHelper::GetChild(_xamlroot.Content(), 0);
	//FrameworkElement frameworkElement = dynamic_cast<FrameworkElement>(element);

	std::wstring a = L"count = " + std::to_wstring(count);
	MessageBox(_hWnd, a.c_str(), 0, 0);

	//ボタンにイベントハンドラ登録
	Element<Button>(L"button1").Click({ &OnButtonClick });
	Element<Button>(L"button2").Click({ &OnButtonClick });

	//メインウインドウ表示
	::ShowWindow(_hWnd, nShowCmd);
	::UpdateWindow(_hWnd);

	//メッセージループ
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ISLANDUIPCH));

	MSG msg;

	// メイン メッセージ ループ:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

//ウインドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT messageCode, WPARAM wParam, LPARAM lParam) {
	RECT rcClient;

	switch (messageCode) {
	case WM_CREATE:
		//return 0;
		break;

	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	case WM_SIZE:   //メインウインドウのサイズが変わったらXAMLホストも追従
		::GetClientRect(hWnd, &rcClient);
		::SetWindowPos(_hWndXamlIsland, nullptr, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, SWP_SHOWWINDOW);

		return 0;
		break;

	default:
		return ::DefWindowProc(hWnd, messageCode, wParam, lParam);
		break;
	}

	return 0;
}

//ボタンクリックのイベントハンドラ
// ハンドラはひとつでNameでどのボタンか判別して処理を分ける
IAsyncAction OnButtonClick(IInspectable const& sender, RoutedEventArgs const& e) {
	auto button = sender.as<Button>();
	if (button.Name() == L"button1") {
		// winrt::to_string は UTF-8からなので直接ワイド文字に変換する
		int length = MultiByteToWideChar(CP_ACP, 0, "あああああ", -1, nullptr, 0);
		std::wstring wide(length, 0);
		MultiByteToWideChar(CP_ACP, 0, "あああああ", -1, &wide[0], length);

		auto dlg = ContentDialog();
		dlg.Title(box_value(wide));
		dlg.Content(box_value(L"ほげー？\nほげ\nほげ\nほげ"));
		dlg.PrimaryButtonText(L"OK");
		dlg.CloseButtonText(L"CANCEL");
		dlg.XamlRoot(_xamlroot);
		auto result = co_await dlg.ShowAsync();
		if (result == ContentDialogResult::Primary) {
			Element<Grid>(L"grid1").Background(SolidColorBrush{ Colors::Pink() });
			Element<TextBlock>(L"textblock1").Text(L"ほげー！");
		}
	}
	else if (button.Name() == L"button2") {
		auto dlg = ContentDialog();
		dlg.Title(box_value(L"button2"));
		dlg.Content(box_value(L"ほげー？\nほげ\nほげ\nほげ"));
		dlg.PrimaryButtonText(L"OK");
		dlg.CloseButtonText(L"CANCEL");
		dlg.XamlRoot(_xamlroot);
		auto result = co_await dlg.ShowAsync();
		if (result == ContentDialogResult::Primary) {
			Element<Grid>(L"grid1").Background(SolidColorBrush{ Colors::Pink() });
			Element<TextBlock>(L"textblock1").Text(L"ほげー！");
		}
	}
}