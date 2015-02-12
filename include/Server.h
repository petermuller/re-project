//Server.h
//
//Listens for the client, receives files, and executes
//commands on behalf of the client.
//
//Peter Muller

#ifndef SERVER_H
#define SERVER_H

#include <string>

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
};

#endif // SERVER_H
