//Server.h
//
//Listens for the client, receives files, and executes
//commands on behalf of the client.
//
//Peter Muller

#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <fstream>

/** \class Server
 * \brief Collection of methods used to control a music database.
 */
class Server
{
    public:
        Server();
        virtual ~Server();
        std::string listAllSongData();
        std::string listArtists();
        std::string listLengths();
        std::string listProcesses();
        std::string listSongs();
        std::string playSong(std::string);
    protected:
    private:
        std::fstream infile;
        std::vector<std::string> artists;
        std::vector<std::string> songs;
        std::vector<std::string> lengths;
        std::vector<std::string> albums;
};

#endif // SERVER_H
