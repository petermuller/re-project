//Coding.cpp
//
//Static methods for encoding and decoding messages to be used
//within the scope of this application.
//
//Peter Muller

#include "Coding.h"
#include <string>
#include <cstdlib>
#include <cstdio>
#include <time.h>

Coding::Coding()
{
    //ctor
}

Coding::~Coding()
{
    //dtor
}

/** \brief Deciphers a message encoded with Coding::encode.
 * \param message - The string to decode. First 3 characters are the shift amount,
 *          which is a number under 256.
 * \return A decoded string for use in the application
 */
std::string Coding::decode(std::string message)
{
    std::string deMess; //string to return
    char num[3];
    char shift;
    unsigned int i;
    for (i=0; i<3; i++){ //get decoder shift amount
        num[i] = message.at(i);
    }
    shift = (char)atoi(num);
    for (i=3; i<message.length(); i++){ //decode the message
        deMess.push_back((message.at(i) ^ offset) - shift);
    }
    return deMess;
}

/** \brief Encodes a message to be sent and decoded with Coding::decode.
 * \param message - The string to encode.
 * \return An encoded message to be sent to an application endpoint. The
 *          first 3 characters are the shift amount. Must be decimal number
 *          under 256.
 */
std::string Coding::encode(std::string message)
{
    std::string enMess; //string to return
    char num[3];
    srand(time(NULL)); //seed the random function
    unsigned int shift = rand()%255 + 1; //cannot be 0
    unsigned int shiftS = shift; //preserve shift amount for later
    sprintf(num,"%03d",(unsigned int)shiftS);
    enMess.append(num); //add shift number to string
    for (unsigned int i=0; i<message.length(); i++){ //encode message
        enMess.push_back((message.at(i) + shift) ^ offset);
    }
    return enMess;
}
