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
    Coding code;
    WSAData wsaData; //winsock
    string buffer, command, output;
    struct addrinfo *result, *ptr = NULL; //addresses
    struct addrinfo hints;
    char sendbuf = NULL;
    char recvbuf[DEF_BUFF_SIZE]; //Rx, Tx bufferse
    int iSendResult;
    int recvbuflen = DEF_BUFF_SIZE;
    string strMenuOption;
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
    cout << "initializing WinSock... " << iSendResult << endl;
    if (iSendResult != 0) {
        cerr << "WSAStartup failed" << endl;
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iSendResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    cout << "    iSendResult " << iSendResult << endl;
    if ( iSendResult != 0 ) {
        cerr << "getaddrinfo failed " << endl;
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        cout << "Listen Socket being established.... " << ListenSocket << endl;
        if (ListenSocket == INVALID_SOCKET) {
            printf("socket failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return 1;
        }

       // connect to server
        iSendResult = connect(ListenSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        cout << "                  connected? =" << iSendResult << endl;
         if (iSendResult == SOCKET_ERROR) {
             cout << "Socket_error.." << endl << endl;
            closesocket(ListenSocket);
            ListenSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);

   if (ListenSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

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
        cout << "5. List Processes" << endl; //listProcesses
        cout << "6. List All Song Titles" << endl; //listSongs
        cout << "7. Upload new songs" << endl << endl; //addSong
        cout << "COMING SOON!" << endl;
        cout << "8. Download songs" << endl; //playSong
        cout << "9. Edit existing song" << endl; //playSong
        cout << "10. Play song" << endl << endl; //playSong

        //enter in input
        cout << "Enter a number: ";
        cin >> menuOption;
        cout << endl;

        cout << "You entered option= " << menuOption << endl;
        cin.ignore();

        if ((menuOption==1)|| (menuOption==2) || (menuOption==3) || (menuOption==4) ||
                  (menuOption==5) || (menuOption==6)){
            //convert number to string
            std::ostringstream ss;  //string variable
            ss << menuOption;       //convert long to string
            strMenuOption = ss.str(); //load it into variable to use throughout the project
            //test the string variable
            cout << "This is the menu option you chose: ";
            cout << strMenuOption << endl;

        }else if (menuOption==7){
            string song, artist, length, album;
            cout << "Thank you for adding to our database!" << endl;
            cout << "Please enter the following information" << endl;

            cout << "Song: ";
            getline (cin, song);
            //cout << "You inputed: " << song << endl;

            cout << endl << "Artist: ";
            getline (cin,artist);
            //cout << "You inputed: " << artist << endl;

            cout << endl << "Length: ";
            getline (cin,length);
            //cout << "You inputed: " << length << endl;

            cout << endl << "Album: ";
            getline (cin,album);
            //cout << "You inputed: " << album << endl;

           /* string SongStr(song);
            string ArtistStr(artist);
            string LengthStr(length);
            string AlbumStr(album);
*/
            strMenuOption = "7~" + song + "~" + artist + "~" + length + "~" + album;
            cout << "user input" << strMenuOption << endl << endl << endl;

        }else {//close socket
            cout << "closing" << endl;
            closesocket(ListenSocket);
            WSACleanup();

            cout << "Thank you for using ARMband Technologies!" << endl;
            cout << "Exiting...";
            Sleep(3600);

            return 1;
        }

        //encode option
        cout << "Encoding...." << endl;
        es = c.encode(strMenuOption);
        cout << "      Encoded string is: " << es << endl;
        Sleep(120);

        //send to server
        cout << "----Sending to server....Waiting----" << endl;


        cout << " Sending in buffer =" << es.c_str() << endl;

        // Send an initial buffer -----> look at additional code?
        iSendResult = send( ListenSocket, es.c_str(), es.length(), 0 );
        if (iSendResult == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        printf("Bytes Sent: %d\n", iSendResult);
        Sleep(180);

        cout << "Receiving!" << endl;
        Sleep (120);
        //recieve from server

        do{
            cout << "Buffer is: " << iSendResult << endl;
            iSendResult = recv(ListenSocket, recvbuf, recvbuflen, 0);
            cout << "After, Buffer is..." << iSendResult << endl;
            if (iSendResult > 0){
                if(buffer.length()>0){
                    int comNum;
                    std::string token;
                    command = code.decode(buffer);
                    std::stringstream ss(command);
                    std::getline(ss,token,'~');
                    comNum = atoi(token.c_str());
                    cout << "Received request number: " << comNum << endl;
                }
                cout << "Decoding..." << endl;
                ds = c.decode(recvbuf);
                cout << "Past the decode" << endl;
                cout << "DS = " << ds;
                continue;
            }
            //if ( iSendResult > 0 )
               // printf("Bytes received: %d\n", iSendResult);
            else if ( iSendResult == 0 )
                printf("Connection closed\n");
            else
                printf("recv failed with error: %d\n", WSAGetLastError());
        }
        while( iSendResult == DEF_BUFF_SIZE );

        cout << "got to the decode";
        //decode
        cout << "Decoding..." << endl;
        ds = c.decode(es);
        Sleep (60);

        cout << "decoded string is " << ds << endl;
        Sleep (3600);
}//end While Loop

    // shutdown the connection since no more data will be sent
    iSendResult = shutdown(ListenSocket,SD_SEND);
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
            printf("Bytes received: %d\n", iSendResult);
        else if ( iSendResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());
}
    while( iSendResult > 0 );

    // cleanup
    cout << "closing" << endl;
    closesocket(ListenSocket);
    WSACleanup();

    //close socket


    cout << "Thank you for using ARMband Technologies!" << endl;
    cout << "Exiting...";
    Sleep(3600);
}
