// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
This is meant to run locally, launch the server, and do the following:

Ask the user to input a name
Wait for a client to connect
Launch a client
Ask the user to input a name
Connect to the server
Run a loop based on a quit condition of your liking (ie the user types in 'quit')
Any message the user enters will be sent to the host or client, depending on who is sending it
The window of the host and client will display the user name and the msg
A sample window may look like this

John: Hello
Jane: Hi
Jane: How are you?
John: Okay
Hint: use a thread process packets and input concurrently
*/



/*
1. Start Debug
2. Debug -> Detach All (this is the client window)
3. Start Debug (this is the server window)
4. On the Server Window hit 1 and then enter
5. On the Client Window hit 2 and then enter
6. There should be a successful connection that looks like this

SERVER WINDOW
1) Create Server
2) Create Client
1
A new client connected from 16777343:54121
A packet of length 3
containing hi

CLIENT WINDOW
1) Create Server
2) Create Client
2
Connection to 127.0.0.1:1234 succeeded.
A packet of length 6
containing hello
*/

#include <enet/enet.h>

#include <iostream>
#include <string>

#include <thread>
using namespace std;

ENetAddress address;
ENetHost* server = nullptr;
ENetEvent event;

bool CreateServer()
{
    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;
    /* Bind the server to port 1234. */
    address.port = 1234;
    server = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);

    return server != nullptr;
}

void MessageSend(string username)
{
    string myMessage;

    while (1)
    {
        cout << username;
        getline(cin, myMessage);
        myMessage.insert(0, username);
        myMessage += "\n";

        /* Create a reliable packet of size 7 containing "packet\0" */
        ENetPacket* packet = enet_packet_create(myMessage.c_str(),
            myMessage.length() + 1,
            ENET_PACKET_FLAG_RELIABLE);

        enet_host_broadcast(server, 0, packet);

        //enet_packet_destroy(packet);

        enet_host_flush(server);
    }
    
}

int main(int argc, char** argv)
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        cout << "An error occurred while initializing ENet." << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    string serverName;

    cout << "Enter your desired name for this session: ";
    getline(cin, serverName);
    serverName += ": ";

    cout << "1) Create Server " << endl;

    string UserInput;
    getline(cin, UserInput);

    if (UserInput == "1")
    {
        if (!CreateServer())
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet server host.\n");
            exit(EXIT_FAILURE);
        }

        thread FirstThread(MessageSend, serverName);
        FirstThread.detach();

        while (1)
        {

            /* Wait up to 1000 milliseconds for an event. */
            while (enet_host_service(server, &event, 1000) > 0)
            {
                switch (event.type)
                {
                    case ENET_EVENT_TYPE_CONNECT:
                        cout << "A new client connected from "
                            << event.peer->address.host
                            << ":" << event.peer->address.port
                            << endl;
                        /* Store any relevant client information here. */
                        event.peer->data = (void*)("Client information");

                        // added scope because you can't create things in a case statement
                        {
                            /*
                            string myMessage = "Please enter your username: ";

                            ENetPacket* packet = enet_packet_create(myMessage.c_str(),
                                myMessage.length() + 1,
                                ENET_PACKET_FLAG_RELIABLE);


                            enet_host_broadcast(server, 0, packet);

                            enet_host_flush(server);
                            */
                        }
                        break;

                    case ENET_EVENT_TYPE_RECEIVE:
                        /*cout << "A packet of length "
                            << event.packet->dataLength << endl
                            << "containing " << (char*)event.packet->data
                            << endl;
                            */
                        cout << (char*)event.packet->data << endl;
                    /* Clean up the packet now that we're done using it. */
                        enet_packet_destroy(event.packet);

                        break;

                    case ENET_EVENT_TYPE_DISCONNECT:
                        cout << (char*)event.peer->data << " disconnected." << endl;
                        /* Reset the peer's client information. */
                        event.peer->data = NULL;
                        break;

                    default:
                        break;
                }
            }
        }

    }
    else
    {
        cout << "Invalid Input" << endl;
    }

    if (server != nullptr)
    {
        enet_host_destroy(server);
    }

    return EXIT_SUCCESS;
}