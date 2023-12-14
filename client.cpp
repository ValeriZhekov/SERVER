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
    size_t size = 19;
    int *arr = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = rand() % 2000 - 1000;
        std::cout<<arr[i]<<" ";
    }
    size_t DataBits = ceil(double(size) / 1000);
    std::cout << "N: " << DataBits << std::endl;
    data *msg = new data[DataBits];
    int j = 1000;
    for (size_t i = 0; i < DataBits; i++)
    {
        if (i ==DataBits - 1)
        {
            j = size % 1000;
        }
        msg[i] = data(arr + i * 1000, j);
    }
    int bytes = send(sock, (char *)&size, sizeof(size_t), 0);
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
    for (int i = 0; i < DataBits; i++)
    {
        bytes = send(sock, (char *)&msg[i], sizeof(data), 0);
        if (bytes == SOCKET_ERROR)
        {
            std::cout << "Couldn't send msg: " << i << std::endl;
            WSACleanup();
            return 4;
        }
        else
        {
            std::cout << "Msg:" << i << " has been sent" << std::endl;
        }
    }
    for (int i = 0; i < DataBits; i++)
    {
        bytes = recv(sock, (char *)&msg[i], sizeof(data), 0);
        if (bytes == SOCKET_ERROR)
        {
            std::cout << "Couldn't get sorted msg num: " << i << std::endl;
            WSACleanup();
            return 5;
        }
        else
        {
            std::cout << "Got sorted msg  num: " << i << std::endl;
        }
    }
    int n = 1000;
    std::cout << "Sorted array: " << std::endl;
    for (size_t i = 0; i < DataBits; i++)
    {
        if (i == DataBits - 1)
        {
            n = size % 1000;
        }
        for (int j = 0; j < n; j++)
        {
            std::cout << msg[i].array[j] << " ";
        }
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}