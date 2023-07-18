#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>

int main()
{ 
	//we will need to use getaddrinfo() to generate an address that is suitable for bind() that takes a hints struct, this strucrt is telling our function what we need.
	std::cout << "local address configuration .." << std::endl;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family  = AF_INET; // getting IPv4 and assigning it to ai_fam..
	hints.ai_socktype = SOCK_STREAM; //this one indecates that we'll be usnig TCP, in case we wanted to use UDP, we should use SOCK_DGRAM insread
	hints.ai_flags = AI_PASSIVE; // this one is for binding to the wildcard address, so we ask getaddrinfo() so we listen on any available network interface


	struct addrinfo *bind_address; 
	getaddrinfo(0, "8080", &hints, &bind_address);

	//8080 is what port we wanna listen on, we can choose whatever port we want, but ports from 0 to 1023 
	//need a super user previlige, so we should avoid them, but anything else should be fine including 8080

	//creating the socket:
	int socket_listen;
	socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);


	if (!socket_listen) 
	{
		fprintf(stderr, "socket() failed. (%d)\n", errno);
		return 1;
	}
	else
		std::cout  << "socket ceated succesfully, binding it to local address.." << socket_listen << std::endl;
	if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen) )
	{
		std::cout << "bind() failed with error number: " << errno << "and error msg: " << std::strerror(errno) << std::endl;
		return 1;
	}
	freeaddrinfo(bind_address);

	std::cout << "listening for connections.. " << std::endl;

	if (listen(socket_listen, 10) != 0)
	{
		std::cout << "listen failed!\n error number is :" << errno << "and error msg: " << std::strerror(errno) << std::endl;
		return 1;

		// the 10 we sent as a second arg to listen is the amount of the connections we want to queue up, which means, if our server
		// is kinda slow and already dealing with a connection or some of them, we are going to line up 10 incoming requests and reject the rest, until
		// we deal with a request and kinda free a space for queueing up another.
	}
	
	std::cout << "waiting for a connection" << std::endl;
	struct sockaddr_storage client_address; // we are using this struct type bc it is large enough to store largest add supported.
	socklen_t client_len = sizeof(client_address);
	int socket_client = accept(socket_listen, (struct sockaddr*)&client_address, &client_len);
	if (socket_client < 0)
	{
		std::cout << "accept() failed with error number: " << errno << "and error msg: " << std::strerror(errno) << std::endl;
		return 1;
			//once accept() is called, the program will stop right there until a connection is made, once it is, accept will create a new socket for it in order to
			//send and receive data through the newly established connection, while the orginal socket will keep listening for new connections.
			//accept also fills in the client's address info after connection.
	}
	std::cout << "connection established.. " << std::endl;
			// in order to print the client's address we can do:
	 char address_buffer[100];
       getnameinfo((struct sockaddr*)&client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
	   std::cout << address_buffer << std::endl;
	 //  std::cout << "trying other method to print the same address : " << (struct sockaddr*)&client_address << std::endl;

	   std::cout << "reciving a request.. " << std::endl;
	   char req[1024];
	   std::cout << recv (socket_client, req, 1024, 0) << std::endl;

	   printf("Sending response...\n");
       const char *response =
           "HTTP/1.1 200 OK\r\n"
           "Connection: close\r\n"
           "Content-Type: text/plain\r\n\r\n"
           "Local time is: ";
       int bytes_sent = send(socket_client, response, strlen(response), 0);
       printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));

	   time_t timer;
       time(&timer);
       char *time_msg = ctime(&timer);
       bytes_sent = send(socket_client, time_msg, strlen(time_msg), 0);
       printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(time_msg));


	   std::cout << "Closing connection..."<< std::endl ;
       close(socket_client);
	   std::cout << "Closing listening socket..."<< std::endl ;
       close(socket_listen);

	   std::cout << "	|~~~~~~~~~~~~~WE ARE FINISHED !!!!!~~~~~~~~~~~|" << std::endl;
}
				
