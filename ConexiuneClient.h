#ifndef CONEXIUNECLIENT_H
#define CONEXIUNECLIENT_H

void initSocketClient(std::string ipAddress, sockaddr_in &hint, SOCKET &listening, SOCKET &clientSocket, sockaddr_in &client, SOCKET &sock);
void finalizeSocketClient(SOCKET &sock);

#endif