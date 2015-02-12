//Server.cpp
//
//Listens for the client, receives files, and executes
//commands on behalf of the client.
//
//Peter Muller

#include "Server.h"
#include <string>

Server::Server()
{
    //ctor
}

Server::~Server()
{
    //dtor
}

/** \brief Retrieves data from the rest of the "listXX" methods.
 *
 * \return All song database values in
 *          "[Song] by [Artist] Length: [Length]" format
 */
std::string Server::listAllSongData()
{
    return "Feature coming soon!";
}

/** \brief Retrieves all artists in database.
 *
 * \return String of all artists in database
 */
std::string Server::listArtists()
{
    return "Feature coming soon!";
}

/** \brief Retrieves all song lengths in database.
 *
 * \return String of song lengths in database
 */
std::string Server::listLengths()
{
    return "Feature coming soon!";
}

/** \brief Retrieves all processes running on server.
 *
 * \return String of all processes running on server
 */
std::string Server::listProcesses()
{
    return "Feature coming soon!";
}

/** \brief Retrieves all song titles in database.
 *
 * \return String of all song titles in database
 */
std::string Server::listSongs()
{
    return "Feature coming soon!";
}

/** \brief Plays a given song on the server.
 *
 * \return Message of playback success or failure
 */
std::string Server::playSong(std::string song)
{
    return "Feature coming soon!";
}
