#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <in6addr.h>
#include <WS2tcpip.h>
#include <ws2def.h>
#include "point3D.hpp"
#include <cmath>
double distance(Points3D p)
{
     return sqrt(pow(p.x1-p.x2,2.0)+pow(p.y1-p.y2,2.0)+pow(p.z1-p.z2,2.0));
}
int main()
{
    WSAData wsaData;
    WORD version = MAKEWORD(2, 2);
    if (WSAStartup(version, &wsaData) != 0)
    {
        std::cout << "couldnt start WSA" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Winsock dll found" << std::endl;
    }
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        std::cout << "Problem with socket" << std::endl;
        WSACleanup();
        return 2;
    }
    else
    {
        std::cout << "Socket is setup" << std::endl;
    }
    sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = inet_addr("127.0.0.1"); // leko sus
    adr.sin_port = htons(29171);
    if (bind(sock, (SOCKADDR *)&adr, sizeof(adr)) == SOCKET_ERROR)
    {
        std::cout << "Bind failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 3;
    }
    else
    {
        std::cout << "Socket is bound" << std::endl;
    }
    if (listen(sock, 5) == SOCKET_ERROR)
    {
        std::cout << "Couldn't listen" << std::endl;
        WSACleanup();
        return 4;
    }
    else
    {
        std::cout << "Server is listening...." << std::endl;
    }
    SOCKET acceptSock = accept(sock, NULL, NULL);
    if (acceptSock == INVALID_SOCKET)
    {
        std::cout << "Error in accept()" << std::endl;
        WSACleanup();
        return 5;
    }
    else
    {
        std::cout << "Accepted connection" << std::endl;
    }
    Points3D points;
    int bytes=recv(acceptSock,(char*)&points,sizeof(Points3D),0);
    if (bytes==SOCKET_ERROR)
    {
        std::cout<<"Couldn't get data"<<std::endl;
        WSACleanup();
        return 6;
    }
    else 
    {
        std::cout<<"Data has been collected"<<std::endl;
    }
    double dist=distance(points);
    bytes=send(acceptSock,(char*)&dist,sizeof(double),0);
    if (bytes==SOCKET_ERROR)
    {
        std::cout<<"Couldn't send distance"<<std::endl;
        WSACleanup();
        return 7;
    }
    else 
    {
        std::cout<<"Distance has been sent"<<std::endl;
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}