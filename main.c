#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
static void sighandler (int signo){
	if (signo == SIGINT){
		int fd = open("./history.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
		char msg[] = "The program exited due to SIGINT\n";
		write(fd, msg, strlen(msg));
		close(fd);
		exit(0);
	}
	else if (signo == SIGUSR1){
		printf("Parent process' PID: %d\n", getppid());
	}
	return;
}


int main(){
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	while (1){
		printf("This process' PID: %d\n", getpid());
		sleep(1);
	}
	return 0;
}
