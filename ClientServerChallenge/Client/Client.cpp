// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
using namespace std;

ENetHost* client = nullptr;

bool CreateClient()
{
    client = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);

    return client != nullptr;
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

    cout << "2) Create Client " << endl;
    int UserInput;
    cin >> UserInput;

    if (UserInput == 2)
    {
        if (!CreateClient())
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet client host.\n");
            exit(EXIT_FAILURE);
        }

        ENetAddress address;
        ENetEvent event;
        ENetPeer* peer;
        /* Connect to some.server.net:1234. */
        enet_address_set_host(&address, "127.0.0.1");
        address.port = 1234;
        /* Initiate the connection, allocating the two channels 0 and 1. */
        peer = enet_host_connect(client, &address, 2, 0);
        if (peer == NULL)
        {
            fprintf(stderr,
                "No available peers for initiating an ENet connection.\n");
            exit(EXIT_FAILURE);
        }
        /* Wait up to 5 seconds for the connection attempt to succeed. */
        if (enet_host_service(client, &event, 5000) > 0 &&
            event.type == ENET_EVENT_TYPE_CONNECT)
        {
            cout << "Connection to 127.0.0.1:1234 succeeded." << endl;
        }
        else
        {
            /* Either the 5 seconds are up or a disconnect event was */
            /* received. Reset the peer in the event the 5 seconds   */
            /* had run out without any significant event.            */
            enet_peer_reset(peer);
            cout << "Connection to 127.0.0.1:1234 failed." << endl;
        }

        while (1)
        {
            ENetEvent event;

            
            /* Wait up to 1000 milliseconds for an event. */
            while (enet_host_service(client, &event, 1000) > 0)
            {
                switch (event.type)
                {
                case ENET_EVENT_TYPE_RECEIVE:
                    /*
                    printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
                    event.packet -> dataLength,
                    event.packet -> data,
                    event.peer -> data,
                    event.channelID);
                    */
                    string myMessage;
                    cin >> myMessage;
                    
                    /* Create a reliable packet of size 7 containing "packet\0" */
                    ENetPacket* packet = enet_packet_create(event.packet->data,
                        event.packet->dataLength + 1,
                        ENET_PACKET_FLAG_RELIABLE);
                    /* Clean up the packet now that we're done using it. */
                    enet_packet_destroy(event.packet);

                    {
                        
                        //cin >> myMessage;
                        /* Create a reliable packet of size 7 containing "packet\0" */
                        ENetPacket* packet = enet_packet_create(myMessage.c_str(),
                            strlen(myMessage.c_str()) + 1,
                            ENET_PACKET_FLAG_RELIABLE);

                        enet_host_broadcast(client, 0, packet);
                        //enet_peer_send(event.peer, 0, packet);

                        /* One could just use enet_host_service() instead. */
                        //enet_host_service();
                        enet_host_flush(client);
                    }
                }
            }
        }
    }
    else
    {
        cout << "Invalid Input" << endl;
    }

    if (client != nullptr)
    {
        enet_host_destroy(client);
    }

    return EXIT_SUCCESS;
}