//Main.cpp
//In Dev-C++ you must add the libws2_32.a library to
//   Project-->Project Options-->Parameters--Linker-->Add Library or Object
// libws2_32 is in the Dev-C++/lib folder
#include <iostream>
#include "Socket.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char* argv[])
{
    //const char* dirName="C:/Users/Student/desktop";
    const char* dirName="./";
    int port = atoi(argv[1]);
    //char *ipAddress = "127.0.0.1";
    string ipAddress;
    bool done = false;
    char recMessage[STRLEN];
    char sendMessage[STRLEN];
    string input;
    string fileToCopy;
    //SERVER

    ServerSocket sockServer;
    cout<<"HOSTING..."<<endl;
    sockServer.StartHosting( port );

    sockServer.SendData("LOGIN");

    sockServer.RecvData(recMessage, STRLEN);
    if(strlen(recMessage) < 3)
    {
        sockServer.SendData("UNWELCOME");
        sockServer.CloseConnection();
    }
    else
    {
        sockServer.SendData("WELCOME");
    }

    //Connected
    while ( true )
    {
        cout<<"\t--WAIT--"<<endl;
        sockServer.RecvData( recMessage, STRLEN );
        cout<<"Recv > "<< recMessage << endl;

        input = string(recMessage).substr(0,4);
        cout << input << input.size() << endl;
        if(string(recMessage).size() > 4)
        {
            fileToCopy = string(recMessage).substr(5);
        }

        if(input == "LIST")
        {
            DIR *dir;
            struct dirent *ep;
            char* fileName;
            char* directory;

            dir = opendir (dirName);

            while (ep = readdir (dir))
            {
                fileName = ep->d_name;
                sockServer.SendData(fileName);
                sockServer.SendData("\n");
            }
        }

        else if(input == "SEND")
        {
            ifstream fin;
            string line;
            //fileToCopy = "C:/Users/Student/desktop/" + fileToCopy;
            //fileToCopy = fileToCopy;
            cout << fileToCopy << endl;
            fin.open(fileToCopy.c_str());
            cout << "file open" << endl;
            if(!fin.is_open())
            {
                cout << "File Does Not Exist" << endl;
            }
            char  toSend[1024];
            cout << "before reading loop" << endl;
            while(!fin.eof())
            {
                getline(fin, line);
                cout << "after getline" << endl;
                //toSend = new char[line.length()+1];
                strcpy(toSend, line.c_str());
                //append a newline
                strcat(toSend, "\n");
                sockServer.SendData(toSend);
                cout << "sent data" << endl;
                memset(&toSend, '\0', sizeof(toSend));
            }
            sockServer.SendData("EOF");
            cout << "sent eof" << endl;
        }
        else if(input == "QUIT")
        {
            sockServer.CloseConnection();
        }
    }
}

