#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <enet/enet.h>

using std::atomic;
using std::cout;
using std::cin;
using std::thread;
using std::string;

class SendProcessor
{
	atomic<bool> m_ThreadShouldRun;
	thread* m_sendThread;


public:
	SendProcessor();
	~SendProcessor();
	void Run();
	void Stop();

private:
	void MessageSend(string username, ENetHost* client);
	string myMessage;

};

