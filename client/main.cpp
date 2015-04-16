#include <iostream>
#include <conio.h>
#include <windows.h>

#include "Client.h"
#include "Coding.h"

using namespace std;

int main()
{
    cout << "opening socket!" << endl;
        //request listening socket from server (winsock client) add library libws2_32.a <-winsoc library
        //fill this out later!
   int menuOption = 99; // option entered
    while (menuOption != 0){
         //list the menu
        cout << "Menu: " <<  endl;
        cout << "0. Exit Program" << endl;
        cout << "1. List All Songs Information" << endl; //listAllSongData
        cout << "2. List Albums" << endl; //listAlbums
        cout << "3. List Artists" << endl; //listArtists
        cout << "4. List Lenghts" << endl; //listLenghts
        cout << "5. List Processes" << endl <<endl; //listProcesses
        cout << "6. List All Song Titles" << endl; //listSongs
        cout << "COMMING SOON!" << endl;
        cout << "7. Upload new songs" << endl; //playSong
        cout << "8. Download songs" << endl; //playSong
        cout << "9. Edit exsisting song" << endl; //playSong
        cout << "10. Play song" << endl << endl; //playSong

        cout << "opening socket!" << endl;
        //request listening socket from server (winsock client)
        //fill this out later!


        //enter in input
        cout << "Enter a number: ";
        cin >> menuOption;
        cout << endl;

        //encode option

        //send to server (convert to string for ecoding method

        //recieve from server (listening the

        //decode

        //print
    }
    cout << "closing"
    cout << "Thank you for using ARMband Technologies!" << endl;
    cout << "Exiting...";
    Sleep(3600);
}
