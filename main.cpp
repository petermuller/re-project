#include <iostream>
#include "Server.h"
#include "Coding.h"

using namespace std;

int main()
{
    string s,es,ds;
    cout << "Server testing!" << endl << endl;
    Server sv;
    s = sv.listAllSongData();
    es = Coding::encode(s);
    ds = Coding::decode(es);
    cout << s << endl << endl << es << endl << endl << ds << endl;
    return 0;
}
