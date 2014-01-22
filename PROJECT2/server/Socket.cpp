//Socket.cpp
#include "Socket.h"


Socket::Socket()
{
    if( WSAStartup( MAKEWORD(2, 2), &wsaData ) != NO_ERROR )
    {
        cerr<<"Socket Initialization: Error with WSAStartup\n";
        system("pause");
        WSACleanup();
        exit(10);
    }

    //Create a socket
    mySocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if ( mySocket == INVALID_SOCKET )
    {
        cerr<<"Socket Initialization: Error creating socket"<<endl;
        system("pause");
        WSACleanup();
        exit(11);
    }

    myBackup = mySocket;
}

Socket::~Socket()
{
    WSACleanup();
}

bool Socket::SendData( char *buffer )
{
    cout <<" in SendData" << endl;
    send( mySocket, buffer, strlen( buffer ), 0 );
    cout << "after send" << endl;
    //memset(&buffer, '\0', sizeof(buffer));
    cout << "after memset " << endl;

    return true;
}

bool Socket::RecvData( char *buffer, int size )
{
    int i = recv( mySocket, buffer, size, 0 );
    buffer[i] = '\0';
    return true;
}

void Socket::CloseConnection()
{
    cout<<"CLOSE CONNECTION"<<endl;
    closesocket( mySocket );
    mySocket = myBackup;
}

void Socket::GetAndSendMessage()
{
    char message[STRLEN];
    cin.ignore();//without this, it gets the return char from the last cin and ignores the following one!
    cout<<"Send > ";
    cin.get( message, STRLEN );
    SendData( message );
}

void ServerSocket::StartHosting( int port )
{
     Bind( port );
     Listen();
}

void ServerSocket::Listen()
{
    //cout<<"LISTEN FOR CLIENT..."<<endl;

    if ( listen ( mySocket, 1 ) == SOCKET_ERROR )
    {
        cerr<<"ServerSocket: Error listening on socket\n";
        system("pause");
        WSACleanup();
        exit(15);
    }

    //cout<<"ACCEPT CONNECTION..."<<endl;

    acceptSocket = accept( myBackup, NULL, NULL );
    while ( acceptSocket == SOCKET_ERROR )
    {
        acceptSocket = accept( myBackup, NULL, NULL );
    }
    mySocket = acceptSocket;
}

void ServerSocket::Bind( int port )
{
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = inet_addr( "0.0.0.0" );
    myAddress.sin_port = htons( port );

    //cout<<"BIND TO PORT "<<port<<endl;

    if ( bind ( mySocket, (SOCKADDR*) &myAddress, sizeof( myAddress) ) == SOCKET_ERROR )
    {
        cerr<<"ServerSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(14);
    }
}

void ClientSocket::ConnectToServer( const char *ipAddress, int port )
{
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = inet_addr( ipAddress );
    myAddress.sin_port = htons( port );

    //cout<<"CONNECTED"<<endl;

    if ( connect( mySocket, (SOCKADDR*) &myAddress, sizeof( myAddress ) ) == SOCKET_ERROR )
    {
        cerr<<"ClientSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(13);
    }
}








