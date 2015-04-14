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
    cout << "Albums test" << endl;
    s = sv.listAlbums();
    es = c.encode(s);
    ds = c.decode(es);
    cout << s << endl << endl << es << endl << endl << ds << endl;
    cout << "Artists test" << endl;
    s = sv.listArtists();
    es = c.encode(s);
    ds = c.decode(es);
    cout << s << endl << endl << es << endl << endl << ds << endl;
    cout << "Lengths test" << endl;
    s = sv.listLengths();
    es = c.encode(s);
    ds = c.decode(es);
    cout << s << endl << endl << es << endl << endl << ds << endl;
    cout << "Processes test" << endl;
    s = sv.listProcesses();
    es = c.encode(s);
    ds = c.decode(es);
    cout << s << endl << endl << es << endl << endl << ds << endl;
    cout << "Songs test" << endl;
    s = sv.listSongs();
    es = c.encode(s);
    ds = c.decode(es);
    cout << s << endl << endl << es << endl << endl << ds << endl;
    return 0;
}
