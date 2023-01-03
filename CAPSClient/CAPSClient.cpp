// CAPSClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include "TCPClient.h"

#define DEFAULT_PORT 12345
using namespace std;
// one char long for max performance
const string usefulStrings[7] = { "a", "b", "c", "d", "e", "f", "g"};
map<string, vector<string>> postmap;
map<string, vector<string>> readmap;
int postNumber;
int readNumber;
int postCount;
int readCount;
int time;
bool timerRunning;

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

void clientThreadFunction(string requestType)
{
		TCPClient client("127.0.0.1", DEFAULT_PORT);
		std::string request;
		client.OpenConnection();
		request = generateRequest(requestType);

		do {
				// barrier
				// timer
				std::cout << "String sent: " << request << std::endl;
				std::cout << "Bytes sent: " << request.size() << std::endl;

				std::string reply = client.send(request);
				// timer should start here, I think?
				if (requestType == "POST")
				{
						postCount++;
				}
				else
				{
						readCount++;
				}
				std::cout << "String returned: " << reply << std::endl;
				std::cout << "Bytes received: " << reply.size() << std::endl;
		} while (request != "exit" && request != "EXIT");
		client.CloseConnection();

}

int main(int argc, char** argv)
{
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
		// how do timers - queryperformancecounter
		// what can we get done on the client?

		// TODO Client: Replicate the reference client's function
		// Sending requests is first step
		// So take the above parameters and use them
		// Implement the barrier and timer
		// Implement number of threads
		// How are we going to do topics and threads? Randomly generated?


		// randomly generate requests here for POST, READ
		// need methods to do this so they can be called to generate x amount
		vector<thread> clientThreads;
		postNumber = 5;
		readNumber = 5;


		for (int i = 0; i < postNumber; i++)
		{
				clientThreads.emplace_back(clientThreadFunction, "POST");
				cout << "Post Thread " << to_string(i) << " sent" << endl;
				// can do type check here with second parameter
		}
		for (int i = 0; i < readNumber; i++)
		{
				clientThreads.emplace_back(clientThreadFunction, "READ");
				cout << "Read Thread " << to_string(i) << " sent" << endl;
		}
		for (auto& th : clientThreads)
				th.join();
		cout << "Number of post requests: " + to_string(postCount) << endl << "Number of read requests: " + to_string(readCount) << endl;
		TCPClient finalClient("127.0.0.1", DEFAULT_PORT);
		finalClient.OpenConnection();
		finalClient.send("exit");
		finalClient.CloseConnection();


		return 0;
}

//std::cout << "Enter string to send to server or \"exit\" (without quotes to terminate): ";
// std::getline(std::cin, request);

// if like ref client, we need to spit out every second the number of requests, for each thread

// Example RefOutput:
//TYPE thread X sent:
//Second 0: 10671 requests.
//		Second 1 : 10697 requests.
//		Second 2 : 10596 requests.
//		Second 3 : 10180 requests.
//		Second 4 : 10153 requests.
//		Second 5 : 10676 requests.
//		Second 6 : 10216 requests.
//		Second 7 : 10379 requests.
//		Second 8 : 10325 requests.
//		Second 9 : 10331 requests.
//		Average : 10422.3 requests.
//		Runtime : 10.0001 seconds.

//		Total poster requests : 213034.
//		Average requests per poster thread : 106517.
//		Total reader requests : 210404.
//		Average requests per reader thread : 105202.
//		Total requests : 423438.
//		Average requests per thread : 105859.
//		Average requests per thread per second : 10585.9.


		// exit? 



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


		// Barrier stuff is in undirected, already got
		// Figure out how to generate m and n number of threads
		// Where do locks go? when accessing DS I guess
		// to presumably grab a request to use from
		// Throtttling?

		// and timer - take number of seconds, use it to inform how long to generate requests for
		// so iterate through map of post / read requests for x seconds
		// for x seconds
		// generatePostRequest (from map)
		// generateReadRequest (from map)
		// etc.
		// map<string, vector<string >>::iterator it(postmap.find(request.getTopicId()));

		// could also have a counter to manage this functionality. might not need DS
		// COUNT OF replies we get back / requests you get back.