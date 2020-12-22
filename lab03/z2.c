#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int signal_pause = 0;
int counter = 0;

//SIGUSR1 - wyswietlenie komunikatu i zakonczenie programu
void sigusr1_handle(int sig)
{
	puts("Wykryto SIGUSR1");
	exit(0);
}

//SIGUSR2 - wyswietlenie komunikatu i kontynuacja programu
void sigusr2_handle(int sig)
{
	puts("Wykryto SIGUSR2");
}

//SIGALRM - wstrzymanie odbierania sygnalu
void sigalrm_handle(int sig)
{
	puts("Wykryto SIGALRM");
	signal_pause = 1;
}

int main(int argc, char** argv)
{
	int i=0;
	int sleepMilisec = 100;
	struct timespec req = {sleepMilisec/1000, sleepMilisec%1000*1000000L};
	signal(SIGUSR1, sigusr1_handle);
	signal(SIGUSR2, sigusr2_handle);
	signal(SIGALRM, sigalrm_handle);
	signal(SIGTERM, SIG_IGN);

	while(1)
	{
		i++;
		nanosleep(&req, NULL);
		if(counter < 100 && signal_pause == 1)
		{
			signal(SIGALRM, SIG_IGN);
			counter++;
		}
		else if(counter >= 100 && signal_pause == 1)
		{
			signal(SIGALRM, sigalrm_handle);
			counter = 0;
			signal_pause = 0;
		}
	}
	
	return 0;
}
