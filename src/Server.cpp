//Server.cpp
//
//Listens for the client, receives files, and executes
//commands on behalf of the client.
//
//Peter Muller

#include "Server.h"
#include <string>
#include <fstream>
#include <sstream>

Server::Server()
{
    //ctor
    //Read database file and parse
    infile.open("database.txt",std::fstream::in);
    std::string output;
    std::string line;
    std::string token;
    std::vector<std::string> tokens;
    unsigned int counter;

    while(std::getline(infile,line)){
        std::stringstream ss(line);
        counter = 0;
        while(std::getline(ss,token,'~')){
            switch(counter){
            case 0: //song title
                songs.push_back(token);
                break;
            case 1: //artist
                artists.push_back(token);
                break;
            case 2: //length
                lengths.push_back(token);
                break;
            case 3: //album
                albums.push_back(token);
                break;
            default:
                //Invalid. Should never get here.
                break;
            }
            ++counter;
        }
    }
}

Server::~Server()
{
    //dtor
    //Cleanup database reader when done
    infile.close();
}

/** \brief Retrieves data from the rest of the "listXX" methods.
 *
 * \return All song database values in
 *          "[Song] by [Artist], Length: [Length], Album: [Album]" format
 */
std::string Server::listAllSongData()
{
    std::string output;
    for (unsigned int i = 0; i<songs.size(); i++){
        output += songs.at(i) + " by " + artists.at(i) + ",\n\t Length: " \
            + lengths.at(i) + ",\n\t Album: " + albums.at(i) + "\n\n";
    }
    return output;
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
