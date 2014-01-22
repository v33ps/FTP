//Socket.h
#pragma once
#include <iostream>
#include "WinSock2.h"

using namespace std;

const int STRLEN = 256;

class Socket
{
    protected:
        WSADATA wsaData;
        SOCKET mySocket;
        SOCKET myBackup;
        SOCKET acceptSocket;
        sockaddr_in myAddress;
    public:
        Socket();
        ~Socket();
        bool SendData( char* );
        bool RecvData( char*, int );
        void CloseConnection();
        void GetAndSendMessage();
};

class ServerSocket : public Socket
{
    public:
        void Listen();
        void Bind( int port );
        void StartHosting( int port );
};

class ClientSocket : public Socket
{
    public:
        void ConnectToServer( const char *ipAddress, int port );
};











