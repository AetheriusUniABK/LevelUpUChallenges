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

ENetAddress address;
ENetHost* server = nullptr;
ENetHost* client = nullptr;
ENetHost* peer = nullptr;

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
/*
struct Position
{

    Position(float const& x, float const& y)
        : m_x(x)
        , m_y(y)
    {

    }

    float m_x;
    float m_y;
};*/

bool CreateClient()
{
    client = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);

    return client != nullptr;
}

// void pointers ex
/*int AddNumber(void* x, void* y)
{
    int* intx = (int*)x;
    int* inty = (int*)y;
}*/

class NetworkMessage
{
public:

    NetworkMessage(int const& type)
        : m_type(type)
    {

    }

    virtual ~NetworkMessage()
    {

    }

    int GetType() { return m_type; }

private:
    int m_type;
};

class PositionMessage : public NetworkMessage
{
public:
    PositionMessage(float const& x, float const& y)
        : NetworkMessage(0)
        , m_x(x)
        , m_y(y)
    {

    }

    float GetX() { return m_x; }
    float GetY() { return m_y; }

private:
    float m_x;
    float m_y;
};

class StringMessage : public NetworkMessage
{
public:
    StringMessage(const char* myMessage)
        : NetworkMessage(1)
    {

    }
};

int main(int argc, char** argv)
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        cout << "An error occurred while initializing ENet." << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    cout << "1) Create Server " << endl;
    cout << "2) Create Client " << endl;
    int UserInput;
    cin >> UserInput;
    if (UserInput == 1)
    {
        if (!CreateServer())
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet server host.\n");
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            if (peer == nullptr)
            {
                PositionMessage message(45.234f, 74.674f);

                float myArray[2] = { 25.345f, 35.234f };

                ENetPacket* packet = enet_packet_create(myArray,
                    sizeof(myArray),//sizeof(float)*2
                    ENET_PACKET_FLAG_RELIABLE);
                /* Extend the packet so and append the string "foo", so it now */
                /* contains "packetfoo\0"                                      */
                //enet_packet_resize(packet, strlen("packetfoo") + 1);
                //strcpy(&packet->data[strlen("packet")], "foo");
                /* Send the packet to the peer over channel id 0. */
                /* One could also broadcast the packet by         */
                enet_host_broadcast(server, 0, packet);
                //enet_peer_send(event.peer, 0, packet);

                /* One could just use enet_host_service() instead. */
                //enet_host_service();
                enet_host_flush(server);
            }

            ENetEvent event;
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
                        /* Create a reliable packet of size 7 containing "packet\0" */
                        ENetPacket* packet = enet_packet_create("hello",
                            strlen("hello") + 1,
                            ENET_PACKET_FLAG_RELIABLE);
                        /* Extend the packet so and append the string "foo", so it now */
                        /* contains "packetfoo\0"                                      */
                        //enet_packet_resize(packet, strlen("packetfoo") + 1);
                        //strcpy(&packet->data[strlen("packet")], "foo");
                        /* Send the packet to the peer over channel id 0. */
                        /* One could also broadcast the packet by         */
                        enet_host_broadcast(server, 0, packet);
                        //enet_peer_send(event.peer, 0, packet);

                        /* One could just use enet_host_service() instead. */
                        //enet_host_service();
                        enet_host_flush(server);
                    }
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    
                    //float* myData = (float*)event.packet->data;

                    NetworkMessage* message = (NetworkMessage*)event.packet->data;

                    switch (message->GetType())
                    {
                    case 0:
                        PositionMessage * posMessage = (PositionMessage*)event.packet->data;
                        cout << "A packet of length " << event.packet->dataLength 
                            << " containing " << posMessage->GetX() << ", " << posMessage->GetY() 
                            << endl;
                        break;
                    default:
                        break;
                    }
                    
                    // 0 is at the end to terminate, so this prints ars, not ars0
                    //char myString[4] = {'a','r','s', 0};
                    const char* myString = "Hello";
                    
                    cout << "A packet of length "
                        << event.packet->dataLength << endl
                        //<< "containing " << myData[0] << ", " << myData[1]//(char*)event.packet->data
                        //<< "containing " << myString
                        << "containing " 
                        << endl;
                    //<< "was received from " << (char*)event.peer->data
                    //<< " on channel " << event.channelID << endl;
                /* Clean up the packet now that we're done using it. */
                    enet_packet_destroy(event.packet);

                    break;

                case ENET_EVENT_TYPE_DISCONNECT:
                    cout << (char*)event.peer->data << "disconnected." << endl;
                    /* Reset the peer's client information. */
                    event.peer->data = NULL;
                }
            }
        }

    }
    else if (UserInput == 2)
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
                    
                    cout << "A packet of length "
                        << event.packet->dataLength << endl
                        << "containing " << (char*)event.packet->data
                        << endl;
                    /* Clean up the packet now that we're done using it. */
                    enet_packet_destroy(event.packet);

                    {
                        /* Create a reliable packet of size 7 containing "packet\0" */
                        ENetPacket* packet = enet_packet_create("hi",
                            strlen("hi") + 1,
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

    if (server != nullptr)
    {
        enet_host_destroy(server);
    }

    if (client != nullptr)
    {
        enet_host_destroy(client);
    }


    return EXIT_SUCCESS;
}


/* Extend the packet so and append the string "foo", so it now */
/* contains "packetfoo\0"                                      */
// enet_packet_resize(packet, strlen("packetfoo") + 1);
// strcpy(&packet->data[strlen("packet")], "foo");





