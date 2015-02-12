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
        static std::string decode(std::string);
        static std::string encode(std::string);
    protected:
    private:
};

#endif // CODING_H
