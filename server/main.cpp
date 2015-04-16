#include <iostream>
#include <winsock2.h>
#include "Server.h"
#include "Coding.h"

using namespace std;

int main()
{
    //Create socket connection
    WSAData wsaData;
    int code=WSAStartup(MAKEWORD(2,2),&wsaData);
    if(code!=0){
        cerr<<"WSAStartup Failed"<<endl;
        return 1;
    }


    //Get input from client
    //Parse info from client
    //Give data to client after encoding it
    //repeat
    return 0;
}
