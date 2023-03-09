# CAPSClient

C++ client for my multihreaded server application, created as part of my Concurrent and Parallel Systems assignment, for which I received a mark of 81 (First). 
My client takes four command-line arguments - an IP address, the number of poster threads desired by the user, the number of reader threads desired by the user, and the time the user would like those requests to be sent for (in seconds).

My server and test harness can thus be run by running the executables provided like so:

CAPSAssignment.exe IP_ADDRESS

And after the server has been started, in another window:

CAPSClient.exe IP_ADDRESS NUMBER_OF_POSTER_THREADS, NUMBER_OF_READER_THREADS, TIME_IN_SECONDS.

