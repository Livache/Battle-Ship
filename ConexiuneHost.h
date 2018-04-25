#ifndef CONEXIUNEHOST_H
#define CONEXIUNEHOST_H

void initSocketHost(std::string myIpAddress, sockaddr_in &hint, SOCKET &listening, SOCKET &clientSocket, sockaddr_in &client, SOCKET &sock);
void finalizeSocketHost(SOCKET &clientSocket);

#endif
