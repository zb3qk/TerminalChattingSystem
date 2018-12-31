#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include "objects.h"

#define PORT 64628

int main(int argc, const char *argv[]){
//check input for server or client call

char buffer1[4096]; //allocate space for buffer (used for multiple scenarios below)
char user[4096];
int connection = 0;
//int s = socket(AF_INET, SOCK_STREAM, 0); //returns the file descriptor of the socket
int s = NULL;

    // start by getting a random port from the ephemeral port range
    srandom(getpid()); // random seed based on this process's OS-assigned ID
    //int port = 0xc000 | (random()&0x3fff); // random element of 49152–65535

    // create an address structure: IPv4 protocol, anny IP address, on given port
    // note: htonl and htons are endian converters, essential for Internet communication
    struct sockaddr_in ipOfServer;
    memset(&ipOfServer, 0, sizeof(struct sockaddr_in));
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
    ipOfServer.sin_port = htons(PORT);

    // we'll have one socket that waits for other sockets to connect to it
    // those other sockets will be the ones we used to communicate
    int listener = socket(AF_INET, SOCK_STREAM, 0);

    // and we need to tell the OS that this socket will use the address created for it
    bind(listener, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));

    // wait for connections; if too many at once, suggest the OS queue up 20
    listen(listener , 20);

    system("host $HOSTNAME"); // display all this computer's IP addresses
    printf("The server is now listening on port %d\n", PORT); // and listening port
    profile online[4096]; //list of online profile objects
    int onlineLength = 0;

    FILE *profiles = fopen("profiles.txt","a+"); // opens list of profiles
    FILE *chatList = fopen("chats.txt","a+"); //opens list of chats
    FILE *profilesLength = fopen("profilesLength.txt","w+"); //opens list of chats

for(;;){ //infinite loop to run server indefinately
    // get a connection socket (this call will wait for one to connect)

    read(s,buffer1, sizeof(buffer1)); //reads data from socket (ID value or creation id)

    //TODO: Protection from empty ID value

	//Polling
	struct pollfd fds[1];
       	int timeout_msecs = 1000*60;
        int ret;
        int i;
	memset(buffer1, 0, sizeof(buffer1));
	FILE *ChatHistory = fopen("textHistory.txt","a+"); //need to also add fclose (when both parties disconnect)
	int ChatHistoryFD = fileno(ChatHistory);
  char message[4096];


	//if(!connection) return 1; //if there is no connection to be had, then there is no chat

              /* Open STREAMS device. */
              fds[0].fd = s; //socket message
                  fds[0].events = POLLIN;
              fds[1].fd = listener; //socket listener (for new connections)
                  fds[1].events = POLLIN;

              ret = poll(fds, 2, timeout_msecs);
              if (ret > 0) {
                  /* An event on one of the fds has occurred. */

                        /* FOR RECIEVING MESSAGES */
                      if (fds[0].revents & POLLIN) { //for socket (recieving messages)
		      					  read(s,buffer1, sizeof(buffer1)); //reads data from socket

		      					  write(1,buffer1, sizeof(buffer1));//writes to the command line
										  fprintf(ChatHistory, "%s", buffer1);
		      					  memset(buffer1, 0, sizeof(buffer1));
                      /* Data may be written on device number i. */
                      }

                      /* Format of data sent: (ProfileName, Password) or (create, ProfileName, Password)
                      /* FOR RECIEVING INITIAL CALLS */
                      if (fds[1].revents & POLLIN) { //for socket (Recieving initial calls)
                      s = accept(listener, (struct sockaddr*)NULL, NULL); //returns the file descriptor
                      read(s,buffer1, sizeof(buffer1)); //reads data from socket
                      char *request = buffer1;
                      char *inputs[3];
                      char *first = strtok_r(request, " ", inputs); //check return value of strtok_r
                      puts(first);

                                  /*Create a new Profile*/
                      if(!strncmp(first,"create",7)) { //create a new profile
                        char *name = inputs[1];
                        char *pass = inputs[2];
                        char *checkName;
                        //Will fgets iteratate through the file?
                        while(fgets(checkName, sizeof(checkName), profiles)) { //will be built into a Hash
                          checkName = strtok(checkName, " ");
                          if(!strncmp(checkName, name, sizeof(checkName))) { name = 1; break; }
                        }
                        if(name) { //valid profile
                          /* char *profilesLengthC;
                          fgets(profilesLengthC, sizeof(profilesLengthC), profilesLength); //finds current id length value
                          int id = atoi(profilesLengthC) + 1;
                          fprintf(profilesLength, "%i", id); //adds new id length value */
                          fprintf(profiles, "%s %s\n", name, pass); //adds profile into the profile list
                          //Makes new profile join the online queue to chat
                          profile new;
                          new.name = name;
                          new.socket = s;
                          online[onlineLength] = new;
                          onlineLength += 1;
                        }
                        else { //invalid profile
                          char *disconnectMessage =  "The profile you tried to create already exists. Please try another";
                          write(s,disconnectMessage, sizeof(disconnectMessage));
                          close(s);
                        }

                      }

                              /*Log in*/
                              /* Format (ProfileName, Password) */
                      else {
                        char *name = first; //first value sent is profile Name
                        char *pass = inputs[1]; //breakable code if inputs length is 1
                        char *checkPass = NULL;
                        char *checkName = NULL;
                        char *namePass[2]; //(ProfileName, Password)
                        int boolean = 0;
                        //Parses through profiles list
                        /*
                        Hash of all profiles saved on running server (in case server turns off, profiles are also saved in files
                        to be reinserted into the hash when the server is back up and running
                        */
                        while(fgets(checkName, sizeof(checkName), profiles)) { //will be built into a Hash
                          // (parses through file of names to see which one is the correct value)
                          checkName = strtok_r(checkName, " ", namePass); //array of 2 componenets (name, password)
                          if(!strncmp(checkName, name, sizeof(checkName))) {
                            checkPass = strtok(namePass[1], " "); //check if this output is correct
                            boolean = 1; //if the profile is found, check if the password is correct
                            if(!strncmp(checkPass, pass, sizeof(checkName))){
                              boolean = 2;
                            }
                            break;
                          }
                        }
                        if(boolean == 2){
                        //Joins profile to chat
                        profile new;
                        new.name = name;
                        new.socket = s;
                        online[onlineLength] = new;
                        }
                        if(boolean == 1){
                          char *incPassMessage = "Sorry, but the password you entered was incorrect";
                          write(s,incPassMessage, sizeof(incPassMessage));
                          close(s);
                        }
                      }
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
	close(listener);


}
