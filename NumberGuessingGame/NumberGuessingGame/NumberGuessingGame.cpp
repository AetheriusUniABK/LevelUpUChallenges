
/*
The server will be responsible for creating the number, and the players guess will be sent to the server, which will check against the random number and return the result to the player.
The player should not be able to guess until the server has responded (with confirmation of a correct or incorrect guess)
Once a player has guessed the right number the game ends.
This will use a dedicated server model, though the server will not be guessing.
Two clients will connect to the server and once two players have connected the game can start.
*/


#include <enet/enet.h>
#include <string>
#include <iostream>
#include <thread>
#include <time.h>

using namespace std;

ENetHost* NetHost = nullptr;
ENetPeer* Peer = nullptr;
bool IsServer = false;
thread* PacketThread = nullptr;

int numPlayers = 0;
bool canGuess = false;
int playerNumber = 1;
int randomNum;

enum PacketHeaderTypes
{
    PHT_Invalid = 0,
    PHT_IsCorrect,
    PHT_Guess,
    PHT_Count,
};

struct GamePacket
{
    GamePacket() {}
    PacketHeaderTypes Type = PHT_Invalid;
    //PacketHeaderTypes Type = PHT_Invalid;
};

struct IsCorrectPacket : public GamePacket
{
    IsCorrectPacket()
    {
        Type = PHT_IsCorrect;
    }

    int playerId = 0;
    bool IsCorrect = false;
};

struct GuessPacket : public GamePacket
{
    GuessPacket()
    {
        Type = PHT_Guess;
    }

    int playerId = 0;
    int guess = 0;
};

//can pass in a peer connection if wanting to limit
bool CreateServer()
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1234;
    NetHost = enet_host_create(&address /* the address to bind the server host to */,
        numPlayers,//32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);

    return NetHost != nullptr;
}

bool CreateClient()
{
    NetHost = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);

    return NetHost != nullptr;
}

bool AttemptConnectToServer()
{
    ENetAddress address;
    /* Connect to some.server.net:1234. */
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    Peer = enet_host_connect(NetHost, &address, 2, 0);
    return Peer != nullptr;
}

void HandleReceivePacket(const ENetEvent& event)
{
    GamePacket* RecGamePacket = (GamePacket*)(event.packet->data);
    if (RecGamePacket)
    {
        cout << "Received Game Packet " << endl;

        // add switch for packet types
        // or if statements for each packet type

        // let player know if they're correct or not
        if (RecGamePacket->Type == PHT_IsCorrect)
        {
            cout << "Your guess was ";
            IsCorrectPacket* CorrectPacket = (IsCorrectPacket*)(event.packet->data);
            if (CorrectPacket)
            {
                string response = (CorrectPacket->IsCorrect ? "correct :)" : "incorrect :(");
                cout << response << endl;
            }
        }
        // get player's guess
        if (RecGamePacket->Type == PHT_Guess)
        {
            GuessPacket* guessPacket = (GuessPacket*)(event.packet->data);
            if (guessPacket)
            {
                cout << "Player " << guessPacket->playerId << " guessed: " << guessPacket->guess << endl;
                if (guessPacket->guess == randomNum)
                {
                    // send a PHT_IsCorrect packet to the player that says their guess was right
                    // send a packet saying the game is over
                    // stop allowing players to send packets
                }
                else
                {
                    // send a PHT_IsCorrect packet to the player that says their guess was wrong
                }
            }
        }
    }
    else
    {
        cout << "Invalid Packet " << endl;
    }

    /* Clean up the packet now that we're done using it. */
    enet_packet_destroy(event.packet);
    {
        enet_host_flush(NetHost);
    }
}

// sends packet function
void BroadcastIsCorrectPacket()
{
    IsCorrectPacket* isCorrectPacket = new IsCorrectPacket();
    isCorrectPacket->IsCorrect = true;
    ENetPacket* packet = enet_packet_create(isCorrectPacket,
        sizeof(IsCorrectPacket),
        ENET_PACKET_FLAG_RELIABLE);

    /* One could also broadcast the packet by         */
    enet_host_broadcast(NetHost, 0, packet);
    //enet_peer_send(event.peer, 0, packet);

    /* One could just use enet_host_service() instead. */
    //enet_host_service();
    enet_host_flush(NetHost);
    delete isCorrectPacket;
}

// creates the random number
// receives player guess
// returns true or false if the guess was correct
void ServerProcessPackets()
{
    // need some kind of logic to quit
    // if user types 'q'
    // stop processing packets
    // notify other players that a player has quit
    while (1)
    {
        ENetEvent event;
        while (enet_host_service(NetHost, &event, 1000) > 0)
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
                BroadcastIsCorrectPacket();
                ++numPlayers;
                if (numPlayers > 1)
                {
                    canGuess = true;
                }
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                HandleReceivePacket(event);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                cout << (char*)event.peer->data << "disconnected." << endl;
                /* Reset the peer's client information. */
                event.peer->data = NULL;
                //notify remaining player that the game is done due to player leaving
            }
        }
    }
}

// AKA Player
// can't guess until server has responded (probably need a bool)
// 
void ClientProcessPackets()
{

    while (1)
    {
        ENetEvent event;
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(NetHost, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case  ENET_EVENT_TYPE_CONNECT:
                cout << "Connection succeeded " << endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                HandleReceivePacket(event);
                break;
            }
        }
    }
}

int main(int argc, char** argv)
{
    srand(time(NULL));

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
        // initialize random number for game
        // from 1 to 100 inclusive
        randomNum = rand() % 100 + 1;
        
        //How many players?
        // We always only want 2 players
        numPlayers = 2;
        

        if (!CreateServer())
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet server.\n");
            exit(EXIT_FAILURE);
        }

        IsServer = true;
        cout << "waiting for players to join..." << endl;
        PacketThread = new thread(ServerProcessPackets);
    }
    else if (UserInput == 2)
    {
        if (!CreateClient())
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet client host.\n");
            exit(EXIT_FAILURE);
        }

        ENetEvent event;
        if (!AttemptConnectToServer())
        {
            fprintf(stderr,
                "No available peers for initiating an ENet connection.\n");
            exit(EXIT_FAILURE);
        }

        PacketThread = new thread(ClientProcessPackets);

        //handle possible connection failure
        {
            //enet_peer_reset(Peer);
            //cout << "Connection to 127.0.0.1:1234 failed." << endl;
        }
    }
    else
    {
        cout << "Invalid Input" << endl;
    }


    if (PacketThread)
    {
        PacketThread->join();
    }

    delete PacketThread;

    if (NetHost != nullptr)
    {
        enet_host_destroy(NetHost);
    }

    return EXIT_SUCCESS;
}