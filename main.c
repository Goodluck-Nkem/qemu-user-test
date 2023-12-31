#include <stdio.h>
#include <sys/utsname.h>

int main(int argc, char* argv[])
{
	struct utsname ust;
	uname(&ust);
	printf("Hello world (%s)\n", ust.machine);
	printf("Number of args: %i\n", argc);
	return 0;
}

