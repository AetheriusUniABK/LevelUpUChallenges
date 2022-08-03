// Multithreading1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;
using std::cin;

//bool ShouldEndThread = false;

int ThreadVar = 0;

bool DidQuit = false;

void HelloWorldThread()
{
    //cout << "Hello World Thread" << endl;
    while (!DidQuit)
    {
        ThreadVar++;
        if (ThreadVar > 1000)
        {
            ThreadVar = 0;  
        }
    }
}

int main()
{
    cout << "Hello World!" << endl;
    char UserInput;
    thread Hello(HelloWorldThread);
    
    while (!DidQuit)
    {
        cout << "Enter any key to display the counter" << endl;
        cout << "Enter 'q' to quit" << endl;
        cin >> UserInput;
        DidQuit = (UserInput == 'q');
        cout << "ThreadVar: " << ThreadVar << endl;
    }

    Hello.join();
    
    
}


