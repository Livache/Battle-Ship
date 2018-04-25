#include "Conexiune.h"
#include "ConexiuneHost.h"


void initSocketHost(std::string myIpAddress, sockaddr_in &hint, SOCKET &listening, SOCKET &clientSocket, sockaddr_in &client, SOCKET &sock)
{
	std::cout << "ConexiuneHost.h" << std::endl;
	int clientSize = sizeof(client);
	WSADATA wsaData;
	WORD ver = MAKEWORD(2, 2);

	int wsOK = WSAStartup(ver, &wsaData);

	if (wsOK != 0)
	{
		std::cout << "Eroare la WSASTARTUP.";
	}
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	//hint.sin_addr.s_addr = inet_addr("86.127.42.36");
	//hint.sin_addr.S_un.S_addr = INADDR_ANY;
	hint.sin_addr.S_un.S_addr = inet_addr(myIpAddress.c_str());
	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cout << "Eroare la Socket.";
	}

	bind(listening, (sockaddr*)&hint, sizeof(hint));
	
	listen(listening, SOMAXCONN);
	clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected to port" << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port." << ntohs(client.sin_port) << std::endl;
	}
	//close socket
	closesocket(listening);
}

void finalizeSocketHost(SOCKET &clientSocket)
{
	closesocket(clientSocket);
	WSACleanup();
}