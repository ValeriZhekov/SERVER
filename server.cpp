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
#include <mutex>
#include <thread>
#include <vector>
#include "data.hpp"
std::mutex m;
const size_t MAXTHREADS = 4;
size_t thread = 0;
void merge(int array[], size_t left, size_t mid, size_t right) // merge algorithm
{
    size_t lSize = mid - left + 1;
    size_t rSize = right - mid;

    int *l = new int[lSize],
        *r = new int[rSize];

    for (int i = 0; i < lSize; i++)
        l[i] = array[left + i];
    for (int j = 0; j < rSize; j++)
        r[j] = array[mid + 1 + j];

    size_t i = 0, j = 0;
    size_t indexMerged = left;

    while (i < lSize && j < rSize)
    {
        if (l[i] <= r[j])
        {
            array[indexMerged] = l[i];
            i++;
        }
        else
        {
            array[indexMerged] = r[j];
            j++;
        }
        indexMerged++;
    }
    while (i < lSize)
    {
        array[indexMerged] = l[i];
        i++;
        indexMerged++;
    }
    while (j < rSize)
    {
        array[indexMerged] = r[j];
        j++;
        indexMerged++;
    }
    delete[] l;
    delete[] r;
}
void mergeSort(int array[], size_t start, size_t end) // klasicheski merge sort
{
    if (start >= end)
        return;

    size_t mid = start + (end - start) / 2;
    mergeSort(array, start, mid);
    mergeSort(array, mid + 1, end);
    merge(array, start, mid, end);
}
void toRun(int array[], size_t size) // izpulnqva se ot vsqka nishka (vsqka ima nomer ot koito znae range-a si na rabota)
{
    std::unique_lock<std::mutex> lock(m);
    size_t threadNum = thread++;
    lock.unlock();
    size_t start = threadNum * (size / MAXTHREADS);
    size_t end = (threadNum + 1) * (size / MAXTHREADS) - 1;
    size_t mid = start + (end - start) / 2;
    if (start < end)
    {
        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);
        merge(array, start, mid, end);
    }
}
void fastMergeSort(int arr[],size_t size)
{
    std::vector<std::thread> threadVector;
    for (size_t i = 0; i < MAXTHREADS; i++) //izpulnqvame nishkite
    {
        threadVector.emplace_back(std::thread(toRun, arr, size));
    }
    for (size_t i = 0; i < MAXTHREADS; i++) //izchakvame da zavurshat
    {
        threadVector[i].join();
    }
    //obedinqvame 4ti chasti ot masiva, koito veche sa sortirani
    merge(arr, 0, (size / 2 - 1) / 2, size / 2 - 1); // za 4 nishki
    merge(arr, size / 2, size / 2 + (size - 1 - size / 2) / 2, size - 1);
    merge(arr, 0, (size - 1) / 2, size - 1);

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
    size_t size;
    int bytes=recv(acceptSock,(char*)&size,sizeof(size_t),0);
    if (bytes==SOCKET_ERROR)
    {
        std::cout<<"Couldn't get size"<<std::endl;
        WSACleanup();
        return 6;
    }
    else 
    {
        std::cout<<"Size of array is: "<<size<<std::endl;
    }
    
    data a;
    bytes=recv(acceptSock,(char*)&a,sizeof(data),0);
    if (bytes==SOCKET_ERROR)
    {
        std::cout<<"Couldn't get array"<<std::endl;
        WSACleanup();
        return 6;
    }
    else 
    {
        std::cout<<"Got array"<<std::endl;
    }
    for (size_t i=0; i < size; i++)
        {
            std::cout << a.array[i] << " ";
        }
    clock_t t1,t2;
    t1=clock();
    fastMergeSort(a.array,size);
    t2=clock();
    std::cout <<std::endl<< "Sort time: " << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl; 
    for (size_t i=0; i < size; i++)
        {
            std::cout << a.array[i] << " ";
        }
        
    bytes=send(acceptSock,(char*)&a,sizeof(data),0);
    if (bytes==SOCKET_ERROR)
    {
        std::cout<<"Couldn't send sorted array"<<std::endl;
        WSACleanup();
        return 7;
    }
    else 
    {
        std::cout<<"Sorted array has been sent"<<std::endl;
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}