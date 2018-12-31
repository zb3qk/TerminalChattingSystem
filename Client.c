#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
//#include "objects.h"

#define IP "INSERT PORT HERE"
#define PORT 64628


/*Security Issue: infinitely calling message fills up call stack*/
void message(int s, char *chatID) {
	for(;;){

	}
}

void profile(char **inputs, int s) { //Check for number of parameters
	int boolean = 0;
	char *inputlist = strtok_r(*inputs, " ",inputs); //exception here
	inputlist = strtok(inputlist, "\n");
	FILE *profiles = fopen("profiles.txt", "a+"); //opens list of profiles for reading and appending
	int profilesFD = fileno(profiles); //FILE * to File Description
	char buffer[4096];
	char input[20];
	char input2[20];

		if(!strncmp(inputlist,"create",6)){ //use strncmp for safety
			inputlist = strtok_r(*inputs, " ",inputs); //exception here
			inputlist = strtok(inputlist, "\n");
			if(!strncmp(inputlist,"cancel", 7)) puts("This name is invalid, please try another one"); //invalid names
			else {
				char *pass = NULL;
				while(1){ //password
				  puts("Please enter the password you wish to use");
					fgets(input,sizeof(input),stdin);
					if(!strncmp(input,"cancel",6)) puts("The password you entered is invalid, please choose another one");
					else {
					puts("Please enter the password you wish to use again");
					fgets(input2,sizeof(input2),stdin);
					if(!strncmp(input,input2,sizeof(input))) break;
					}
				}
				/* Protocol to create new profile on the server */
				char message[4096] = "create ";
				strncat(inputlist, " ", sizeof(message) - strlen(message) - 1); //add space in front of profile
				strncat(message, inputlist, sizeof(message) - strlen(message) - 1); //concatonate create to profile name
				strcat(message,input);  //concatonate create + profile name to password


				write(s,message,strlen(message)); //writes the profile creation protocol to the server

				fprintf(profiles, "%s\n", inputlist);
				printf("You have made the profile: %s \n", inputlist);
			}
		}

		else if(!strncmp(inputlist,"delete",6)){ //use strncmp for safety
			puts("Please select a profile to delete or write cancel to go back");
			scanf("%s", inputlist);
			FILE *temp = fopen("tempProf.txt", "w");

				while(fgets(input, sizeof(input), profiles)){ //parse through profiles.txt
				//fgets(input, sizeof(input), profiles);
				char *inputP = input;
				strtok(input, "\n");
					if(!strncmp(input, inputlist, sizeof(input))) boolean=1;
					else{ //check for correctness
						fprintf(temp, "%s\n", input);
					}
				}
			if(!boolean) puts(" -- This profile does not exist");
			else printf("You have deleted the profile: %s \n", input);

			remove("profiles.txt");
			rename("tempProf.txt","profiles.txt");

			//need to delete from profile list
			//need to also include to synchronize with server
		}

		else {
			puts("This input was invalid");
		}
}

int main(int argc, const char *argv[]){

puts("////////////////////////////////////////////////////////");
puts("                Terminal Chatting System                ");
puts("////////////////////////////////////////////////////////");
puts("");
puts("Help Menu: ");
puts("press CNTRL^C to quit the program");
puts("write '/profile create (NAME)' to create a profile");
puts("write '/profile select (NAME)' to select a profile");
puts("write '/message (NAME)' to message a user");
puts("write '/help' to view the help menu");
puts("");

	//Connection to the server
	struct sockaddr_in ipOfServer;
	memset(&ipOfServer, 0, sizeof(struct sockaddr_in));
	ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = inet_addr(IP);
	ipOfServer.sin_port = htons(PORT);
	int s = socket(AF_INET, SOCK_STREAM, 0); //returns the file descriptor of the socket

	//do poll to see if server is online

	int connection = connect(s,(struct sockaddr*)&ipOfServer, sizeof(ipOfServer));
	if (connection == 0){
	puts("Connection to the server could not be made");
	} //connects socket s to the server identified in ip. Return value 0 if no connection

char input[4096];
char *inputs[3];
	if(fgetc(stdin) == '/'){
		fgets(input, sizeof(input), stdin);
		char *inputlist = strtok_r(input, " ",inputs);
		if(!strncmp(inputlist,"profile", 7)) profile(inputs, s);

	}
return 0;
}
