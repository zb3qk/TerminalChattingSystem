#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

void profile(char **inputs) {
	char *inputlist = strtok_r(*inputs, " ",inputs); //exception here
	inputlist = strtok(inputlist, "\n");
	FILE *profiles = fopen("profiles.txt", "a+"); //opens list of profiles for reading and appending
	int profilesFD = fileno(profiles);
	char buffer[4096];
	char input[20];
	
		if(!strncmp(inputlist,"create",6)){ //use strncmp for safety
			inputlist = strtok_r(*inputs, " ",inputs); //exception here
			inputlist = strtok(inputlist, "\n");
			if(!strncmp(inputlist,"cancel", 7)) puts("This name is invalid, please try another one"); //invalid names
			else {
			fprintf(profiles, "%s \n", inputlist);
			printf("You have made the profile: %s \n", inputlist);
			} 
		}

		else if(!strncmp(inputlist,"delete",6)){ //use strncmp for safety
			puts("Please select a profile to delete or write cancel to go back");
			scanf("%s", inputlist);
			FILE *temp = fopen("tempProf.txt", "a+");
				while(read(profilesFD, buffer, sizeof(buffer))){ //parse through profiles.txt
				fgets(input, sizeof(input), profiles);
					if(!strncmp(input, inputlist, sizeof(input)));
					else if(input[0]!='\0' || inputlist[0]!='\0'){ //check for correctness
						fprintf(temp, "%s \n", input);
					}
				}
			remove("profiles.txt");
			rename("tempProf.txt","profiles.txt");
			printf("You have deleted the profile: %s \n", inputlist);
			
			//need to delete from profile list
			//need to also include to synchronize with server
		}
}

int main(int argc, const char *argv[]){
char input[4096];
char *inputs[3];
	if(fgetc(stdin) == '/'){	
		fgets(input, sizeof(input), stdin);
		char *inputlist = strtok_r(input, " ",inputs);
		if(!strncmp(inputlist,"profile", 7)) profile(inputs); 

	}
return 0;
}
