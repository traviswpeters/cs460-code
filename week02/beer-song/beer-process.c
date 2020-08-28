#include <stdio.h>
#include <unistd.h>

static void PrintMessage(int i);
static void GoToSleep(void);

#define NBOTTLES 100000

int main(void)
{
	int i = NBOTTLES;

	while (1)
	{
		PrintMessage(i);
		GoToSleep();
		i -= 1;
	}

	return 0;
}

static void PrintMessage(int i)
{
	printf("%d bottles of beer on the wall, %d bottles of beer. Take one down, pass it around...\n", i, i);
}

static void GoToSleep(void)
{
	sleep(1);
}
