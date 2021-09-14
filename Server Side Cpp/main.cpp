
#include <iostream>
#include <ws2tcpip.h>
#include <windows.h>
#include "JSL/JoyShockLibrary.h"
#include <string>

using namespace std;


int  main()
{

    WSADATA data;

    WORD version = MAKEWORD(2, 2);

    int wsOkay = WSAStartup(version, &data);

    if (wsOkay != 0)
    {
        cout << "Unable to start WinSock!" << wsOkay;
    }


    sockaddr_in server;

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;

    server.sin_port = htons(54000);     // Converting from Little to Big Endian.

    inet_pton(AF_INET, "182.185.123.28", &server.sin_addr);     // 182.185.123.28 Router's Public IP (will use port-forwarding).
                                                                // 192.168.10.100 NodeMCU's Private Static IP.
    SOCKET outData = socket(AF_INET, SOCK_DGRAM, 0);


    //if (bind(outData, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    //{
    //    cout << "\n Unable to find the socket! Error: " << WSAGetLastError() << "\n";
    //}


    cout << "\n\t I am running!\n";


///////////////////////////////////////////////////////////////////

    int numPS4_Controllers = JslConnectDevices();

    int deviceID[numPS4_Controllers];

    JslGetConnectedDeviceHandles(deviceID, numPS4_Controllers);

    JOY_SHOCK_STATE myPS4_DS4;

///////////////////////////////////////////////////////////////////


    string msgToBeSent;

    while (true)
    {

        myPS4_DS4 = JslGetSimpleState(deviceID[0]);

        bool rightTrigger = myPS4_DS4.buttons & JSMASK_ZR;


        if (rightTrigger == 1)
        {
            msgToBeSent = "Pressed";
        }

        else if (rightTrigger == 0)
        {
            msgToBeSent = "Released";
        }


        Sleep(1);

        //cout << "\n\t Please enter your message for the Client: \n";
        ////cout << "\n\t Only enter * Pressed * or * Released * \n";
        //cout << "\n\t ";

        //string msgToBeSent;
        //cin >> msgToBeSent;


        int sendOkay = sendto(outData, msgToBeSent.c_str(), msgToBeSent.size(), 0, (sockaddr*)&server, sizeof(server));

    }
    

    closesocket(outData);

    
    
    WSACleanup();



    return(0);
}