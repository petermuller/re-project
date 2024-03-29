//Server.cpp
//
//Listens for the client, receives files, and executes
//commands on behalf of the client.
//
//Peter Muller

#include "Server.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

#define BUFF_SIZE (512)

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
    infile.close();
}

Server::~Server()
{
    //dtor
    //Cleanup database reader when done
}

/** \brief Adds a song entry to the database.
 *
 * \param query - A tilde-separated string in the form of:
 *          Song~Artist~Length~Album
 *
 * \return String of true or false to denote success of the operation.
 *          A string is used for ease of encoding data for transmission.
 */
std::string Server::addSong(std::string query){
    std:: string output = "true";
    std::string token;

    infile.open("database.txt",std::fstream::out | std::fstream::app);
    infile << query << std::endl;
    infile.close();
    std::stringstream ss(query);
    unsigned int counter = 0;
    while(std::getline(ss,token,'~')){
        switch (counter){
        case 0:
            songs.push_back(token);
            break;
        case 1:
            artists.push_back(token);
            break;
        case 2:
            lengths.push_back(token);
            break;
        case 3:
            albums.push_back(token);
            break;
        case 4:
            break;
        default:
            std::cerr << "Invalid input. Failing operation." << std::endl;
            output = "false";
            break;
        }
        ++counter;
    }
    return output;
}

/** \brief Retrieves data from the rest of the "listXX" methods.
 *
 * \return All song database values in
 *          "[Song] by [Artist], Length: [Length], Album: [Album]" format.
 *          There is no trailing endline.
 */
std::string Server::listAllSongData()
{
    std::string output;
    for (unsigned int i = 0; i<songs.size(); i++){
        output += songs.at(i) + " by " + artists.at(i) + ",\n\t Length: " \
            + lengths.at(i) + ",\n\t Album: " + albums.at(i) + "\n";
    }
    return output;
}

/** \brief Retrieves all albums in database.
 *
 * \return String of all albums in database
 */
std::string Server::listAlbums(){
    std::string output;
    for (unsigned int i = 0; i<albums.size(); i++){
        if (i==0){
            output += "Albums:\n";
        }
        output += "\t" + albums.at(i) + "\n";
    }
    return output;
}

/** \brief Retrieves all artists in database.
 *
 * \return String of all artists in database
 */
std::string Server::listArtists()
{
    std::string output;
    std::vector<std::string> uarts;
    unsigned int i;
    for (i = 0; i<artists.size(); i++){
        if (std::find(uarts.begin(),uarts.end(),artists.at(i))==uarts.end()){
            //If artist not already in unique artists list
            uarts.push_back(artists.at(i));
        }
    }
    for (i = 0; i<uarts.size(); i++){
        if (i == 0){
            output += "Artists:\n";
        }
        output += "\t" + uarts.at(i) + "\n";
    }
    return output;
}

/** \brief Retrieves all song lengths in database.
 *
 * \return String of song lengths in database
 */
std::string Server::listLengths()
{
    std::string output;
    for (unsigned int i = 0; i<lengths.size(); i++){
        if (i==0){
            output += "Songs Lengths:\n";
        }
        output += "\t" + lengths.at(i) + "\n";
    }
    return output;
}

/** \brief Retrieves all processes running on server.
 *
 * \return String of all processes running on server
 */
std::string Server::listProcesses()
{
    FILE *pipe;
    char buffer[BUFF_SIZE];
    std::string output;
    pipe = popen("tasklist","r"); //Windows only
    while(fgets(buffer,BUFF_SIZE,pipe)!=NULL){
        output += buffer;
    }
    pclose(pipe);
    return output;
}

/** \brief Retrieves all song titles in database.
 *
 * \return String of all song titles in database
 */
std::string Server::listSongs()
{
    std::string output;
    for (unsigned int i = 0; i<songs.size(); i++){
        if (i==0){
            output += "Song Titles:\n";
        }
        output += "\t" + songs.at(i) + "\n";
    }
    return output;
}

/** \brief Plays a given song on the server.
 *
 * \return Message of playback success or failure
 */
std::string Server::playSong(std::string song)
{
    return "Feature coming soon!";
}
