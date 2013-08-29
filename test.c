#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	struct termios  options;
	int fd, ret;

	if(argc < 2)
	{
		printf("Usage: %s [file]\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDWR | O_NONBLOCK | O_NOCTTY);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}

	fcntl(fd, F_SETFL, 0);// 也就是说现在是阻塞的

	tcgetattr(fd, &options);

	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

	options.c_cflag &= ~CRTSCTS;
	options.c_cflag |= CREAD | CLOCAL;
	
	//0代表每一个都等待VTIME 不为0则为没VMIN个数超时否则一直等待
	options.c_cc[VMIN] = 0;
	options.c_cc[VTIME] = 20;

	tcsetattr(fd, TCSANOW, &options);

	char ch;

	while(1)
	{
		ret = read(fd, &ch, 1);
		if(ret < 1)
		{
			printf("over\n");
			break;
		}

		printf("0x%x\n", ch);
	}

	close(fd);

	return 0;
}

