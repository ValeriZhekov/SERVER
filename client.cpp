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
    if (connect(sock,(SOCKADDR*)&adr,sizeof(adr))==SOCKET_ERROR)
    {
        std::cout<<"Failed to connect"<<std::endl;
        WSACleanup();
        return 3;
    }
    else
    {
        std::cout<<"Connected, can start sending and reveiving data"<<std::endl;
    }
    Points3D points;
    std::cout<<"Enter A: "<<std::endl;
    std::cin>>points.x1>>points.y1>>points.z1;
    std::cout<<"Enter B:"<<std::endl;
    std::cin>>points.x2>>points.y2>>points.z2;
    int bytes=send(sock,(char*)&points,sizeof(Points3D),0);
    if (bytes==SOCKET_ERROR)
    {
        std::cout<<"Couldn't send data"<<std::endl;
        WSACleanup();
        return 4;
    }
    else 
    {
        std::cout<<"Data has been sent"<<std::endl;
    }
    double dist;
    bytes=recv(sock,(char*)&dist,sizeof(double),0);
    if (bytes==SOCKET_ERROR)
    {
        std::cout<<"Couldn't get distance"<<std::endl;
        WSACleanup();
        return 5;
    }
    else 
    {
        std::cout<<"Distance between A and B is "<<dist<<std::endl;
    }
    closesocket(sock);
    WSACleanup();
return 0;
}