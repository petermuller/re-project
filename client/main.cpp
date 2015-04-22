//Kirstie Failey
//Client Program
//Reverse Engineering Project

#define _WIN32_WINNT 0x501
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <conio.h>

#include "Client.h"
#include "Coding.h"

#define DEF_BUFF_SIZE (1024)
#define DEFAULT_PORT "9001"

#undef UNICODE
#define WIN32_LEAN_AND_MEAN

using namespace std;

int main()
{   //variable declarations
    WSAData wsaData; //winsock
    struct addrinfo *result = NULL; //addresses
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;
    char sendbuf = NULL;
    char recvbuf[DEF_BUFF_SIZE]; //Rx, Tx bufferse
    int iSendResult;
    int recvbuflen = DEF_BUFF_SIZE;
    int iResult;
    SOCKET ListenSocket = INVALID_SOCKET; //Sockets
    SOCKET ClientSocket = INVALID_SOCKET;

    //variables for menu
    long menuOption = 99;       // option entered
    string es, ds;              //variables for (e)ncode and (d)ecode strings
    Coding c;                   // coding variable
    cout << "opening socket!" << endl;
        //request listening socket from server (winsock client) add library libws2_32.a <-winsoc library



 // Initialize Winsock
    iSendResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    cout << iSendResult << endl;
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iSendResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

   // Setup the TCP listening socket
    iSendResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iSendResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

   /* if (ListenSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
    */

    //******************
    //MENU OPTIONS HERE
    //******************
    while (menuOption > 0){
         //list the menu
        cout << "Menu: " <<  endl;
        cout << "0. Exit Program" << endl;
        cout << "1. List All Songs Information" << endl; //listAllSongData
        cout << "2. List Albums" << endl; //listAlbums
        cout << "3. List Artists" << endl; //listArtists
        cout << "4. List Lengths" << endl; //listLengths
        cout << "5. List Processes" << endl <<endl; //listProcesses
        cout << "6. List All Song Titles" << endl; //listSongs
        cout << "COMING SOON!" << endl;
        cout << "7. Upload new songs" << endl; //playSong
        cout << "8. Download songs" << endl; //playSong
        cout << "9. Edit existing song" << endl; //playSong
        cout << "10. Play song" << endl << endl; //playSong

        //enter in input
        cout << "Enter a number: ";
        cin >> menuOption;
        cout << endl;

        cout << "option= " << menuOption << endl;

        //convert number to string
        std::ostringstream ss;  //string variable
        ss << menuOption;       //convert long to string
        string strMenuOption = ss.str(); //load it into variable to use throughout the project
        //test the string variable
        cout << "this is the menu option you chose: " << endl;
        cout << strMenuOption << '\n';

        //encode option
        cout << "Encoding...." << endl;
        es = c.encode(strMenuOption);
        cout << "Encoded string is: " << es << endl;
        Sleep(120);

        //send to server
        cout << "Sending to server....Waiting" << endl;

        cout << "Sending in buffer =" << es.c_str() << endl;
            // Send an initial buffer -----> look at additional code?
        iSendResult = send( ListenSocket, es.c_str(), es.length(), 0 );
        if (iSendResult == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);
        Sleep(180);

        //recieve from server (listening the
        cout << "Receiving!" << endl;
        Sleep (120);

        //decode
        cout << "Decoding..." << endl;
        ds = c.decode(es);
        Sleep (60);

        cout << "decoded string is " << ds << endl;
        Sleep (3600);
    }




    // shutdown the connection since no more data will be sent
    iSendResult = shutdown(ListenSocket, SD_SEND);
    if (iSendResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    do {

        iSendResult = recv(ListenSocket, recvbuf, recvbuflen, 0);
        if ( iSendResult > 0 )
            printf("Bytes received: %d\n", iResult);
        else if ( iSendResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    }
    while( iSendResult > 0 );

    // cleanup
    closesocket(ListenSocket);
    WSACleanup();

    //close socket
    cout << "closing" << endl;

    cout << "Thank you for using ARMband Technologies!" << endl;
    cout << "Exiting...";
    Sleep(3600);
}
