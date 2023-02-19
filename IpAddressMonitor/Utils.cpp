#include <winsock2.h>
#include <Iphlpapi.h>
#include <iostream>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define  GAA_FLAGS (GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_DNS_SERVER |\
					GAA_FLAG_SKIP_FRIENDLY_NAME | GAA_FLAG_SKIP_MULTICAST )

#define WORKING_BUFFER_SIZE 15000

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))



DWORD IsInterfaceUp(void)
{
	IP_ADAPTER_ADDRESSES* pAdapters = NULL, * pipa;
	DWORD nBufferLength = WORKING_BUFFER_SIZE;
	DWORD ret;

	std::wcout.imbue(std::locale("Japanese"));
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
		//if (pipa->Ipv4Enabled) continue;
		if (pipa->IfType == IF_TYPE_SOFTWARE_LOOPBACK) continue;
		if (pipa->IfType == IF_TYPE_TUNNEL) continue;
		std::wcout << pipa->FriendlyName << "\n";

		PIP_ADAPTER_UNICAST_ADDRESS pUnicast = pipa->FirstUnicastAddress;
		while (pUnicast)
		{
			// ユニキャストIPアドレスを列挙
			sockaddr* pAddr = pUnicast->Address.lpSockaddr;
			if (pAddr->sa_family == AF_INET)            // IPv4
			{
				WCHAR ip_address[INET_ADDRSTRLEN];
				InetNtopW(AF_INET, &((struct sockaddr_in*)pAddr)->sin_addr, ip_address, INET_ADDRSTRLEN);
				//inet_ntop(AF_INET, &((struct sockaddr_in*)pAddr)->sin_addr, ip_address, INET_ADDRSTRLEN)
					//inet_ntop(AF_INET, &((struct sockaddr_in*)pAddr)->sin_addr, szAddr, sizeof(szAddr));
					//fprintf(stderr, ”  IPv4 : % s / % d\n”, szAddr, pUnicast->OnLinkPrefixLength);
				std::wcout << ip_address << "/" << pUnicast->OnLinkPrefixLength << "\n";
			}
			else if (pAddr->sa_family == AF_INET6)      // IPv6
			{
				//inet_ntop(AF_INET6, &((struct sockaddr_in6*)pAddr)->sin6_addr, szAddr, sizeof(szAddr));
				//fprintf(stderr, ”  IPv6 : % s / % d\n”, szAddr, pUnicast->OnLinkPrefixLength);
			}
			pUnicast = pUnicast->Next;                  // 次のユニキャストアドレスへ
		}

		//if (pipa->OperStatus == IfOperStatusUp) break;
	}
	FREE(pAdapters);
	pAdapters = NULL;

	if (pipa != NULL)
		return ERROR_SUCCESS;

	return ERROR_NO_DATA;
}