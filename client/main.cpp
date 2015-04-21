#include <iostream>
#include <sstream>
#include <string>
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
    long menuOption = 99;       // option entered
    string es, ds;              //variables for (e)ncode and (d)ecode strings
    Coding c;                   // coding variable
    while (menuOption > 0){
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

        //send to server (convert to string for ecoding method
        cout << "Sending to server....Waiting" << endl;
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
    cout << "closing" << endl;
    cout << "Thank you for using ARMband Technologies!" << endl;
    cout << "Exiting...";
    Sleep(3600);
}
