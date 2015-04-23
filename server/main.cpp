#define _WIN32_WINNT 0x501
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include "Server.h"
#include "Coding.h"

#define DEF_BUFF_SIZE (1024)
#define DEFAULT_PORT "9001"

#undef UNICODE
#define WIN32_LEAN_AND_MEAN

//Source of socket help:
//https://msdn.microsoft.com/en-us/library/windows/desktop/ms737593(v=vs.85).aspx

using namespace std;

int main()
{
    //Application specific variables
    Server serv;
    Coding code;
    string buffer, command, output;
    unsigned int comNum=7;
    //Variable declarations
    WSAData wsaData; //winsock
    struct addrinfo *result = NULL; //addresses
    struct addrinfo hints;
    int iSendResult;
    char recvbuf[DEF_BUFF_SIZE]; //Rx, Tx bufferse
    int recvbuflen = DEF_BUFF_SIZE;
    SOCKET ListenSocket = INVALID_SOCKET; //Sockets
    SOCKET ClientSocket = INVALID_SOCKET;


    //Create socket connection
    int iResult=WSAStartup(MAKEWORD(2,2),&wsaData);
    if(iResult!=0){
        cerr<<"WSAStartup Failed"<<endl;
        return 1;
    }
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) { //received a byte
            buffer = std::string(recvbuf);
            if(buffer.length()>0){
                command = code.decode(buffer);
                comNum = atoi(command.c_str());
                cout << "Command: " << command << endl << "Received request number: " << comNum << endl;
                switch (comNum){
                    case 1:
                        output = code.encode(serv.listAllSongData());
                        break;
                    case 2:
                        output = code.encode(serv.listAlbums());
                        break;
                    case 3:
                        output = code.encode(serv.listArtists());
                        break;
                    case 4:
                        output = code.encode(serv.listLengths());
                        break;
                    case 5:
                        output = code.encode(serv.listProcesses());
                        break;
                    case 6:
                        output = code.encode(serv.listSongs());
                        break;
                    case 7:
                        output = code.encode(serv.addSong("A~B~C~D"));
                        break;
                    default:
                        output = code.encode(serv.playSong(""));
                        break;
                }
                iSendResult = send( ClientSocket, output.c_str(), output.length(), 0 );
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                cout << "Sent " << iSendResult << " bytes to client" << endl;
                cout << buffer << endl;
            }
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    //Get input from client
    //Parse info from client
    //Give data to client after encoding it
    //repeat
    return 0;
}
