#include "fdf.h"


int		stock_map(char *argv)
{
	int				fd;
	char			*line;
	int				ret;
	t_coordinate3d	point3d;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (-1);


	//remember to check the map here
	
	point3d.x = 0;
	point3d.y = 0;
	point3d.x = 1;


	line = 0;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (ret);
		if (ret == 0)
			break;
		printf("%s\n", line);
	}
	close(fd);
	return (0);
}