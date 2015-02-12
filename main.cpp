#include <iostream>
#include "Server.h"

using namespace std;

int main()
{
    string s;
    cout << "Server testing!" << endl;
    Server sv;
    s = sv.listAllSongData();
    cout << s;
    return 0;
}
