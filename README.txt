Steps to run:

initialize.c        //Initialize the values of all users
->gcc initialize.c -o initialize
->./initialize

server.c            //Make the server ready for accepting connections
->gcc -pthread server.c -o server
->./server

client.client       //Connect to server and request changes to user's account
->gcc client.c -o client
->./client