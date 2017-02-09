#ifndef NOTHINGTORECEIVEEXCEPTION_H
#define NOTHINGTORECEIVEEXCEPTION_H

#include <exception>

class NothingToReceiveException : public std::exception
{
    public:
        virtual const char* what() const throw();
};

#endif
