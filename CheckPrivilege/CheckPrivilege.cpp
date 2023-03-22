// CheckPrivilege.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <windows.h>
#include <iostream>

int main()
{
	HANDLE token;
	PRIVILEGE_SET tp;
	LUID luid;
	BOOL enabled;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
	{
		std::cerr << "OpenProcessToken failed: " << GetLastError() << std::endl;
		return 1;
	}

	if (!LookupPrivilegeValue(nullptr, SE_CREATE_GLOBAL_NAME, &luid))
	{
		std::cerr << "LookupPrivilegeValue failed: " << GetLastError() << std::endl;
		CloseHandle(token);
		return 1;
	}

	tp.PrivilegeCount = 1;
	tp.Privilege[0].Luid = luid;
	tp.Privilege[0].Attributes = 0;

	if (!PrivilegeCheck(token, &tp, &enabled))
	{
		std::cerr << "PrivilegeCheck failed: " << GetLastError() << std::endl;
		CloseHandle(token);
		return 1;
	}

	if (enabled)
	{
		std::cout << "SE_CREATE_GLOBAL_NAME privilege is enabled" << std::endl;
	}
	else
	{
		std::cout << "SE_CREATE_GLOBAL_NAME privilege is not enabled" << std::endl;
	}

	CloseHandle(token);

	std::cin.get();
}
