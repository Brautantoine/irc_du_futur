#ifndef CLIENTDISCONNECTEDEXCEPTION_H
#define CLIENTDISCONNECTEDEXCEPTION_H

#include <exception>

class ClientDisconnectedException : public std::exception
{
    public:
        virtual const char* what() const throw();
};

#endif
