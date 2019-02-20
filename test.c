#include "fdf.h"

int	main(int argc, char **argv)
{
	int fd;
	int	ret;
	char *line;

	argc = 2;
	fd = open(argv[1], O_RDONLY);
	while(1)
	{
		ret =get_next_line(fd, &line);
		printf("ret:%d/nline:%s/n",ret,line);
		if (ret != 1)
		{
			break;
		}
	}
	return (0);
}
