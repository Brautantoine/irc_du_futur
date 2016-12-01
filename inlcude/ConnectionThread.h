#ifndef CONNECTIONTHREAD_H_INCLUDED
#define CONNECTIONTHREAD_H_INCLUDED

class ConnectionThread {
public:
    ConnectionThread(SOCKET serverSocket);
private:
    SOCKET m_serverSocket;
};

#endif // CONNECTIONTHREAD_H_INCLUDED
