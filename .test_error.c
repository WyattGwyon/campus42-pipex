#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
	int fd;
	fd = open("doesnotexist.txt", O_CREAT);

	if (fd == -1)
	{
		perror("perror output");

		printf("strerror says: %s\n", strerror(errno));
	}
	return (0);
}