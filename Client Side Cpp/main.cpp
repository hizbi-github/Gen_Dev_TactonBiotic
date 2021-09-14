#include <iostream>
#include <ws2tcpip.h>
#include <windows.h>
#include "JSL/JoyShockLibrary.h"
#include <string>

//#pragma comment (lib, "ws2_32.lib")                  // only works with Visual Studio.
// Works with gc++ compilers specifically


using namespace std;


int  main()
{

    WSADATA data;

    WORD version = MAKEWORD(2, 2);

    int wsOkay = WSAStartup(version, &data);

    if (wsOkay != 0)
    {
        cout << "Unable to start WinSock!" << wsOkay;

        return(0);
    }

    
    SOCKET inData = socket(AF_INET, SOCK_DGRAM, 0); 


    sockaddr_in server;

    server.sin_addr.S_un.S_addr = ADDR_ANY;

    server.sin_family = AF_INET;

    server.sin_port = htons(55000);     // Converting from Little to Big Endian.


    if (bind(inData, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        cout << "\n Unable to find the socket! Error: " << WSAGetLastError() << "\n";
    }


    sockaddr_in client;

    int clientLength = sizeof(client);

    ZeroMemory(&client, clientLength);

    char inDataBuf[1024];


    cout << "\n     I am running!\n";


///////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////


    //string msgFromInside;

    //int switchCase = 0;


    while (true)
    {
        
        ZeroMemory(inDataBuf, 1024);
                
        int inDataBytes = recvfrom(inData, inDataBuf, 1024, 0, (sockaddr*)&client, &clientLength);


        if (inDataBytes == SOCKET_ERROR)
        {
            cout << "\n Unable to receive data from the client!" << WSAGetLastError() << "\n";  

            continue;          
        }


        char clientIP[256];
        ZeroMemory(clientIP, 256);


        inet_ntop(AF_INET, &client.sin_addr, clientIP, 256);


        cout << "\n Message received from Client: " << clientIP;
        cout << "\t" << inDataBuf << "\n";      
   

    }
    

    closesocket(inData);

    
    
    WSACleanup();



    return(0);
}