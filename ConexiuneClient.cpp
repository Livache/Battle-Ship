#include "Conexiune.h"
#include "ConexiuneClient.h"


void initSocketClient(std::string ipAddress, sockaddr_in &hint, SOCKET &listening, SOCKET &clientSocket, sockaddr_in &client, SOCKET &sock)
{
	std::cout << "ConexiuneClient.h" << std::endl;
	int clientSize = sizeof(client);
	WSAData wsaData;
	WORD ver = MAKEWORD(2, 2);

	int wsResult = WSAStartup(ver, &wsaData);

	if (wsResult != 0)
	{
		std::cout << "Can't start winsock, Err #" << wsResult << std::endl;
		return;
	}


	//create socket

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cout << "Eroare socket Err #" << WSAGetLastError() << std::endl;
		return;
	}



	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//connect server.

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));

	if (connResult == SOCKET_ERROR)
	{
		std::cout << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		getchar();
		return;
	}
}

void finalizeSocketClient(SOCKET &sock)
{
	closesocket(sock);
	WSACleanup();
}