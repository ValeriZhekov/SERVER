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
#include<ws2def.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netdb.h>

#define h_addr  h_addr_list[0]

#define PORT 80
using namespace std;
const char Host[] = "www.amazon.com";


struct servent* appl_name;
char name[4] = "FTP";
char proto[4] = "TCP";
int port=80;

struct protoent* protoen;


//typedef unsigned short WORD;
//typedef unsigned char BYTE;
//#define MAKEWORD(a,b)	((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))

int main() {


	


	// Init WINSOCKx
	WSAData wsaData;
	WORD DllVersion = 2 | 2 << 8;
		 //MAKEWORD(2, 2); 
	printf("%hu\n", DllVersion);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		fprintf(stderr, "WSAStartup()\n");
		//getchar();
		ExitProcess(EXIT_FAILURE);
	}
	if (HIBYTE(wsaData.wHighVersion) != 2 && LOBYTE(wsaData.wHighVersion) !=2)
	{
		printf( "WSAStartup()\n");
	}


	
	

/*	appl_name = getservbyname(name, proto);

	if (!appl_name)
		printf("unknown application %s\n", name);
	else
	{
		port = appl_name->s_port;
		printf("getservbyname was successful\n");
		std::cout <<"Port is "<< port << std::endl;
	}

	protoen = getprotobynumber(port);
	std::cout << protoen->p_proto << endl;
	*/


	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		fprintf(stderr, "socket()\n");
		//getchar();
		ExitProcess(EXIT_FAILURE);
	}

	// Get Server info
	HOSTENT* host = gethostbyname(Host);


	//printf("%c\n", *(struct in_addr*)host->h_addr_list[0]);

	//cout << endl;
	if (host == nullptr) {
		closesocket(sock);
		fprintf(stderr, "gethostbyname()\n");
		//getchar();
		ExitProcess(EXIT_FAILURE);
	}
	//

	hostent* localHostt;
	char* localIPP;

	localHostt = gethostbyname("www.amazon.com");

	//localIPP = inet_ntoa(* (in_addr*)  * localHostt->h_addr_list); 
	localIPP = inet_ntoa(*reinterpret_cast <in_addr*>(localHostt->h_addr_list[0]));
	std::cout << '\n';
	double b = 5.4;
	std::cout << "b= " << *reinterpret_cast <float*> (&b) << '\n';

	
	printf("Amazon's IPv4 address %s \n", localIPP);

	

	// Declare variables
	/*SOCKET ListenSocket;
	struct sockaddr_in saServer;
	hostent* localHost;
	char* localIP;

	// Create a listening socket
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Get the local host information
	localHost = gethostbyname("www.zamunda.net");
	localIP = inet_ntoa(*(struct in_addr*) * localHost->h_addr_list);

	// Set up the sockaddr structure
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = inet_addr(localIP);
	saServer.sin_port = htons(5150);

	// Bind the listening socket using the
	// information in the sockaddr structure
	bind(ListenSocket, (SOCKADDR*)& saServer, sizeof(saServer));

	*/


	/*typedef struct hostent {
		char* h_name;
		char** h_aliases;
		 char*  h_alianses[]
		short h_addrtype;
		short h_length;
		char** h_addr_list;
	} HOSTENT, * PHOSTENT, * LPHOSTENT;
*/


	hostent* localHost;
	char* localIP;
	in_addr addr;
	in6_addr addrr;
	localHost = gethostbyname("www.amazon.com");
	//localIP = inet_ntoa6(*(struct in_addr6*) * localHost->h_addr_list);
	//printf("%d\n", localHost->h_addrtype);
	//printf("%s\n", localIP);

	//localIP = inet_ntoa(*(struct in_addr6*) * localHost->h_addr_list);

	int i = 0; 
	//in6_addr addrr;
	//addrr.u.Byte =
	//	addr.
	//unsigned int dwRetval;
	
	 addrinfo* result ;
	 addrinfo* ptr;
	 addrinfo hints;


/*
	 struct sockaddr_in {
		 short            sin_family;   // e.g. AF_INET
		 unsigned short   sin_port;     // e.g. htons(3490)
		 struct in_addr   sin_addr;     // see struct in_addr, below
		 char             sin_zero[8];  // zero this if you want to
	 };

	 struct in_addr {
		 unsigned long s_addr;  // load with inet_aton()
	 };
	 */


	 /*typedef struct addrinfo {
  int             ai_flags;
  int             ai_family;
  int             ai_socktype;
  int             ai_protocol;
  size_t          ai_addrlen;
  char            *ai_canonname;
  struct sockaddr *ai_addr;
  struct addrinfo *ai_next;
} ADDRINFOA, *PADDRINFOA;*/

	char port_str[16] = {};

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//dwRetval =
		//getaddrinfo("www.zamunda.net", port_str, &hints, &result);

	  
		//printf("%d\n", result->ai_socktype);

	char ipstringbuffer[460];
	 sockaddr_in6* sockaddr_ipv6;
	 sockaddr_in* sockaddr_ip;




	/*struct sockaddr_in {
		short            sin_family;   // e.g. AF_INET
		unsigned short   sin_port;     // e.g. htons(3490)
		struct in_addr   sin_addr;     // see struct in_addr, below
		char             sin_zero[8];  // zero this if you want to
	};

	struct in_addr {
		unsigned long s_addr;  // load with inet_aton()
	};
	*/
	
	 getaddrinfo("www.amazon.com", port_str, &hints, &result);

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		sockaddr_ipv6 = ( sockaddr_in6*) ptr->ai_addr;

		//sockaddr_ipv6 = reinterpret_cast < sockaddr_in6* > (ptr->ai_addr);
		printf("\tIPv6 address %s\n", inet_ntop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, sizeof(ipstringbuffer)));
		//printf("%s \n", ipstringbuffer);

		
	
	}
	

	/*for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		sockaddr_ip = ( sockaddr_in*) ptr->ai_addr;
		printf("\tIPv4 address %s\n", inet_ntop(AF_INET, &sockaddr_ip->sin_addr, ipstringbuffer, 460));

	}
	*/

	//if (localHost->h_addrtype == AF_INET6) {
	//	while (localHost->h_addr_list[i] != 0) {
			//addr6.u.Byte=*(*UCHAR)localHost->h_addr_list[i++];
			
		//	printf("\tIPv4 Address #%d: %s\n", i, inet_ntoa(addr));
		//}
	//}

	char** pAlias;
	printf("\tOfficial name: %s\n", localHost->h_name);
	for (pAlias = localHost->h_aliases; *pAlias != 0; pAlias++) {
		printf("\tAlternate name #%d: %s\n", ++i, *pAlias);
	}


	//if (localHost->h_addrtype == AF_INET) {
	//	while (localHost->h_addr_list[i] != 0) {
		//	addr.s_addr = *(unsigned long long*)localHost->h_addr_list[i++];
	//		printf("\tIPv4 Address #%d: %s\n", i, inet_ntoa(addr));
	//	}
	//}


	// Define server info
	SOCKADDR_IN sin;
	ZeroMemory(&sin, sizeof(sin));
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;
	//inet_aton("63.161.169.137", &sin.sin_addr.s_addr);
	memcpy(&sin.sin_addr.S_un.S_addr, host->h_addr_list[0], sizeof(sin.sin_addr.S_un.S_addr));
	
	// Connect to server
	if (connect(sock, (const sockaddr*)& sin, sizeof(sin)) != 0) {
		closesocket(sock);
		fprintf(stderr, "connect()\n");
		//getchar();
		ExitProcess(EXIT_FAILURE);
	}
	
	const char szMsg[] = "HEAD / HTTP/1.1\r\n\r\n";
	if (!send(sock, szMsg, strlen(szMsg), 0)) {
		closesocket(sock);
		fprintf(stderr, "send()\n");
		//getchar();
		ExitProcess(EXIT_FAILURE);
	}

	// Recieve data back from server
	char szBuffer[4096];
	char szTemp[4096];
	while (int k=recv(sock, szTemp, 4096, 0))
	{	//strcat(szBuffer, szTemp);
		printf("%d", k);


		for (int i = 0; i < k; ++i)
			printf("%c", szTemp[i]);
		//printf("%s\n", szTemp);
	}



	
	closesocket(sock);
	//getchar();
	ExitProcess(EXIT_SUCCESS);
}
