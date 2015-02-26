#include <iostream>
#include "Server.h"
#include "Coding.h"

using namespace std;

int main()
{
    string s,es,ds;
    cout << "Server testing!" << endl << endl;
    Server sv;
    Coding c;
    cout << "All Song Data Test" << endl;
    s = sv.listAllSongData();
    es = c.encode(s);
    ds = c.decode(es);
    cout << s << endl << endl << es << endl << endl << ds << endl;
    cout << "Artists test" << endl;
    s = sv.listArtists();
    es = c.encode(s);
    ds = c.decode(es);
    cout << s << endl << endl << es << endl << endl << ds << endl;
    return 0;
}
