#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void executeClient()
{
	execl("./dataserver", "./dataserver", NULL);
}

void executeServer()
{
	execl("./client", "./client", NULL);
}


int main()
{
	printf("Starting the server-client manager\n");
	pid_t pid = fork();

	if(pid == 0)/*Child Process*/
	{
		executeClient();
	}
	else /*Parent Process*/
	{
		executeServer();
	}

	return 0;

}
