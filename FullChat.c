#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>

void profile() {
	
}

int main(int argc, const char *argv[]){
//check input for server or client call

char buffer1[4096]; //allocate space for buffer (used for multiple scenarios below)
char user[4096];
int connection = 0;
int s = socket(AF_INET, SOCK_STREAM, 0); //returns the file descriptor of the socket

if(!argv[1]){ //run server

    // start by getting a random port from the ephemeral port range
    srandom(getpid()); // random seed based on this process's OS-assigned ID
    int port = 0xc000 | (random()&0x3fff); // random element of 49152–65535

    // create an address structure: IPv4 protocol, anny IP address, on given port
    // note: htonl and htons are endian converters, essential for Internet communication
    struct sockaddr_in ipOfServer;
    memset(&ipOfServer, 0, sizeof(struct sockaddr_in));
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
    ipOfServer.sin_port = htons(port);

    // we'll have one socket that waits for other sockets to connect to it
    // those other sockets will be the ones we used to communicate
    int listener = socket(AF_INET, SOCK_STREAM, 0);

    // and we need to tell the OS that this socket will use the address created for it
    bind(listener, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));

    // wait for connections; if too many at once, suggest the OS queue up 20
    listen(listener , 20);

    system("host $HOSTNAME"); // display all this computer's IP addresses
    printf("The server is now listening on port %d\n", port); // and listening port

	puts("Please input your username: ");
	scanf("%s", user); //seg fault here
	dprintf(1,"Your user name is: %s \n \n", user);

    // get a connection socket (this call will wait for one to connect)
    s = accept(listener, (struct sockaddr*)NULL, NULL); //returns the file descriptor
    //write(s, msg, strlen(msg)); // send a full message
    close(listener);
}

else if(argv[1] && argv[2]){ //run client
	//puts("Client");	
	struct sockaddr_in ipOfServer; //ipOfServer of type sockaddr_in (socket type in C) 
   	memset(&ipOfServer, 0, sizeof(struct sockaddr_in)); //
	ipOfServer.sin_family = AF_INET; //Declaring the type of socket input

	//Accepts an IP address from the Command Line
	ipOfServer.sin_addr.s_addr=inet_addr(argv[1]); //set IP address to first input argument	
	
	//Accepts a Port from the Command Line
	ipOfServer.sin_port = htons(atoi(argv[2])); //set port to the second input argument
	
	s = socket(AF_INET, SOCK_STREAM, 0); //returns the file descriptor of the socket
	//connection returns 0 upon success
	int connection = connect(s,(struct sockaddr*)&ipOfServer, sizeof(ipOfServer)); //connects socket s to the server identified in ip. Return value 0 if no connection
	if(connection==-1){ puts("Very Bad"); return 1; }
	//if(connection==0){ puts("Im here"); write(connection, msg1, strlen(msg1)); }  	

	puts("Please input your username: ");
	scanf("%s", user); //seg fault here
	dprintf(1,"Your user name is: %s \n \n", user);
}

else { puts("You have inputted the wrong number of arguments to runs either the server or the client. Please run with no arguements to run the server, and with [IP address, port #] to run the client."); return 1; }

//Chatting continues here
char buffer2[4096];
	char *namer = ": ";
	strcat(user, namer);
	

	//Polling
	struct pollfd fds[2];
       	int timeout_msecs = 1000*60;
        int ret;
        int i;
	memset(buffer1, 0, sizeof(buffer1));
	

	//if(!connection) return 1; //if there is no connection to be had, then there is no chat
	
              /* Open STREAMS device. */
              fds[0].fd = 0; //Standard Input
              fds[1].fd = s; //socket
                  fds[0].events = POLLIN;
                  fds[1].events = POLLIN;

	for(;;){ //infinite loop to check for user input or socket reciever
              ret = poll(fds, 2, timeout_msecs);
              if (ret > 0) {
                  /* An event on one of the fds has occurred. */
                      if (fds[0].revents & POLLIN) { //for standard input
		      char *message = fgets(buffer1,4096,stdin);
                      write(s, user, strlen(user)); // sends username
		      write(s, message, strlen(message)); // send a full message
                      memset(buffer1, 0, sizeof(buffer1));
		      }
                      if (fds[1].revents & POLLIN) { //for socket
		      read(s,buffer1, sizeof(buffer1)); //reads data from socket
		      write(1,buffer1, sizeof(buffer1));//writes to the command line
		      memset(buffer1, 0, sizeof(buffer1)); 
                      /* Data may be written on device number i. */
                      }
               }
	}


/*
for(;;){
	
	//reciever
	memset(buffer1, 0, sizeof(buffer1)); //sets buffer1 value to 0	
	while(read(s,buffer1, sizeof(buffer1))>0) { //output of connection is 0 if nothing is left to sent
						    //continues reading until nothing left to send
    	strcat(buffer2, buffer1); //concatonate output from server
	memset(buffer1,0,sizeof(buffer1)); //clears out the buffer
	}
	printf(buffer2); //prints chat from other computer
	memset(buffer2,0,sizeof(buffer2)); //resets immeadiate line sent

}
*/ //Extraneous Code	
return 0;
	//close(s);


}
