//Main.cpp
//In Dev-C++ you must add the libws2_32.a library to
//   Project-->Project Options-->Parameters--Linker-->Add Library or Object
// libws2_32 is in the Dev-C++/lib folder

#include <iostream>
#include <fstream>
#include "Socket.h"
using namespace std;

int main(int argc, char* argv[])
{
    int port = atoi(argv[1]);
    //char *ipAddress = "127.0.0.1";
    string ipAddress;
    bool done = false;
    char recMessage[STRLEN];
    char sendMessage[STRLEN];
    string input;
    string line;
    string fileToCopy;

    cout<<"Enter an IP address, 127.0.0.1 is the loopback address"<<endl;
    cin>>ipAddress;
    ClientSocket sockClient;
    cout<<"ATTEMPTING TO CONNECT..."<<endl;
    sockClient.ConnectToServer( ipAddress.c_str(), port );
    //Connected

    //Recieving login
    sockClient.RecvData( recMessage, STRLEN ); //rec

    cout<< "Recv > " << recMessage <<endl;

    //sockClient.GetAndSendMessage();
    char message[STRLEN];
    cin.ignore();//without this, it gets the return char from the last cin and ignores the following one!
    cout<<"Send > ";
    cin.get( message, STRLEN );
    sockClient.SendData( message );

    sockClient.RecvData( recMessage, STRLEN ); //rec
    cout<< "Recv > " << recMessage <<endl;

    while ( true )
    {
        //sockClient.GetAndSendMessage();
        char message[STRLEN];
        cin.ignore();//without this, it gets the return char from the last cin and ignores the following one!
        cout<<"Send > ";
        cin.get( message, STRLEN );
        sockClient.SendData( message );
        cout << "input is " << message << endl;

        input = string(message).substr(0,4);
        if(string(message).size() > 4)
            fileToCopy = string(message).substr(5);
        cout << "input is " << input << endl;
        cout << "File to copy is " << fileToCopy << endl;
        cout<<"\t--WAIT--"<<endl;


       if(input == "SEND")
        {

            //recMessage[STRLEN] = ' ';
            ofstream fout;
            fout.open(fileToCopy.c_str(), fstream::app);

            do
            {
                cout << "FIRST" << recMessage << endl;
                memset(&recMessage, '\0', sizeof(recMessage));
                cout << "SECOND" << recMessage << endl;
                sockClient.RecvData( recMessage, STRLEN );
                cout << "THIRD" << recMessage << endl;
                if(recMessage != "EOF")
                {
                    fout << recMessage << endl;
                    //memset(recMessage, 0, sizeof(char)*STRLEN);
                }
            }while(strcmp(recMessage, "EOF") == 0);//end eof

        }

        else if(input == "LIST")
        {
            sockClient.RecvData(recMessage, STRLEN);
            cout << recMessage;
            cout << endl;
        }
        else
        {
            cout << "Error" << endl;
        }
    }
}

