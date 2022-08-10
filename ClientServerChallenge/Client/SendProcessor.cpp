#include "SendProcessor.h"
using std::atomic;
using std::cout;
using std::cin;
using std::thread;
using std::string;

SendProcessor::SendProcessor()
{

}

SendProcessor::~SendProcessor()
{

}

void SendProcessor::Run()
{
	m_ThreadShouldRun.store(true);
    //m_sendThread = new thread(&SendProcessor::MessageSend, this);
}

void SendProcessor::Stop()
{
    m_ThreadShouldRun.store(false);
    //m_sendThread->join();
}

void SendProcessor::MessageSend(string username, ENetHost* client)
{
    while (m_ThreadShouldRun.load())
    {
        cout << username;
        getline(cin, myMessage);
        myMessage.insert(0, username);

        /* Create a reliable packet of size 7 containing "packet\0" */
        ENetPacket* packet = enet_packet_create(myMessage.c_str(),
            myMessage.length() + 1,
            ENET_PACKET_FLAG_RELIABLE);

        enet_host_broadcast(client, 0, packet);

        //enet_packet_destroy(packet);

        enet_host_flush(client);
    }
}