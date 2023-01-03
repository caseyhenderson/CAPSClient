// CAPSClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include "TCPClient.h"

#define DEFAULT_PORT 12345
using namespace std;
// one char long for max performance
const string usefulStrings[7] = { "a", "b", "c", "d", "e", "f", "g"};
map<string, vector<string>> postmap;
map<string, vector<string>> readmap;


string generateRequest(string type)
{
		// generate random number 
		// let's go one long to get performance
		int random = rand() % 8;
		string request = "";
		if (type == "POST")
		{
				request.append("POST@" + usefulStrings[random] + "#" + usefulStrings[random]);
		}
		else if (type == "READ")
		{
				request.append("READ@" + usefulStrings[random] + "#" + to_string(random));
		}
		return request;
}

// these then go into a map I guess?



int main(int argc, char** argv)
{
		std::cout << argv[0] << std::endl << argv[1]; 
		// vector of the client threads
		// number of requests, seconds of requests, numbers of clients
		// threadClient function
		// //
		// // trying to add more arguments. Not fun.
		// // although haven't defined what post-count should do yet tbf
	// Validate the parameters
		// string gen: randomised, pre-gen or automated
		// REFACTOR this to take your parrameters: IP, post thread count, read thread count, time, throttling
		if (argc != 2) {
				printf("usage: %s server-name|IP-address\n", argv[0]);
				printf("post count: %s post-count\n", argv[2]);
				// then take read count as the other argument and store to variables m, and n respectively
				return 1;
		}
		// how do barriers
		// how do timers
		// what can we get done on the client?

		// TODO Client: Replicate the reference client's function
		// Sending requests is first step
		// So take the above parameters and use them
		// Implement the barrier and timer
		// Implement number of threads
		// How are we going to do topics and threads? Randomly generated?


		// randomly generate requests here for POST, READ
		// need methods to do this so they can be called to generate x amount


		TCPClient client(argv[1], DEFAULT_PORT);
		std::string request;

		// if (post_request)
		// generate random post requests
		// similar switch: case could work
		// call generate request with the type here, after its been determined how many threads we're doing (and whether they're poster/reader)
		// so call generate request(POST, m) 
		// and then insert them to map for fast access idk
		// populate the map with requests
		// not sure when we do this

		// something like this, but for client?
		// 		for (auto& th : serverThreads)
		// th.join();
		// vector of clientThreads / postThreads / readThreads

		client.OpenConnection();

		do {
				request = "";
				// then decide what it's gonna be here
				std::cout << "Enter string to send to server or \"exit\" (without quotes to terminate): ";
				std::getline(std::cin, request);

				std::cout << "String sent: " << request << std::endl;
				std::cout << "Bytes sent: " << request.size() << std::endl;

				std::string reply = client.send(request);

				std::cout << "String returned: " << reply << std::endl;
				std::cout << "Bytes received: " << reply.size() << std::endl;
		} while (request != "exit" && request != "EXIT");

		client.CloseConnection();

		return 0;
}
