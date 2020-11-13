#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	int i = 0;
	int sleepMilisec = 100;
	struct timespec req = {sleepMilisec/1000, sleepMilisec%1000 * 1000000L};

	while(1)
	{
		i++;
		nanosleep(&req, NULL);
	}

	return 0;
}
