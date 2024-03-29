//Coding.h
//
//Static methods for encoding and decoding messages to be used
//within the scope of this application.
//
//Peter Muller

#ifndef CODING_H
#define CODING_H

#include <string>

/** \class Coding
 * \brief Contains methods for encoding and decoding application messages.
 */
class Coding
{
    public:
        Coding();
        virtual ~Coding();
        std::string decode(std::string);
        std::string encode(std::string);
    protected:
    private:
        //Just another measure of encoding. Used to XOR message.
        static const unsigned char offset = 22;
};

#endif // CODING_H
