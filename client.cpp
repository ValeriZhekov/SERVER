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
#include <cmath>
#include <vector>
#include "data.hpp"
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
    if (connect(sock, (SOCKADDR *)&adr, sizeof(adr)) == SOCKET_ERROR)
    {
        std::cout << "Failed to connect" << std::endl;
        WSACleanup();
        return 3;
    }
    else
    {
        std::cout << "Connected, can start sending and reveiving data" << std::endl;
    }
    size_t size=878;
    int *arr=new int[size];
    for (size_t i=0; i < size; i++)
    {
        arr[i]=rand()%200-100;
    }
    data a(arr,size);
    for (size_t i=0; i < size; i++)
        {
            std::cout << a.array[i] << " ";
        }
    int bytes = send(sock,(char*)&size,sizeof(size_t), 0);
    if (bytes == SOCKET_ERROR)
    {
        std::cout << "Couldn't send size of array" << std::endl;
        WSACleanup();
        return 4;
    }
    else
    {
        std::cout << "Size of array has been sent" << std::endl;
    }
    bytes = send(sock, (char*)&a, sizeof(data), 0);
    if (bytes == SOCKET_ERROR)
    {
        std::cout << "Couldn't send array" << std::endl;
        WSACleanup();
        return 4;
    }
    else
    {
        std::cout << "Array has been sent" << std::endl;
    }
    bytes = recv(sock, (char*)&a, sizeof(data), 0);
    if (bytes == SOCKET_ERROR)
    {
        std::cout << "Couldn't get sorted array" << std::endl;
        WSACleanup();
        return 5;
    }
    else
    {
        std::cout << "Sorted array: " << std::endl;
        for (size_t i=0; i < size; i++)
        {
            std::cout << a.array[i] << " ";
        }
    } 
   
    closesocket(sock);
    WSACleanup();
    return 0;
}