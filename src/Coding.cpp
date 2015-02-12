//Coding.cpp
//
//Static methods for encoding and decoding messages to be used
//within the scope of this application.
//
//Peter Muller

#include "Coding.h"
#include <string>

Coding::Coding()
{
    //ctor
}

Coding::~Coding()
{
    //dtor
}

/** \brief Deciphers a message encoded with Coding::encode.
 * \param message - The string to decode
 * \return A decoded string for use in the application
 */
std::string Coding::decode(std::string message)
{
    return message; //TODO: unstub with actual algorithm
}

/** \brief Encodes a message to be sent and decoded with Coding::decode.
 * \param message - The string to encode
 * \return An encoded message to be sent to an application endpoint
 */
std::string Coding::encode(std::string message)
{
    return message; //TODO: unstub with actual algorithm
}
