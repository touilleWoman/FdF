/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:00:54 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/20 12:00:55 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		check_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if ((line[i] != ' ')  && (line[i] != '-') && ((line[i] < '0') || (line[i] > '9')))
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

int		check_map(char *argv, t_map_params *mpp)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (-1);
	mpp->y = 0;
	mpp->x = 0;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (ret);
		if (ret == 0)
			break;
		ret = check_map_line(line);
		if (ret == -1)
			return (ret);
		if(mpp->y == 0)
			mpp->x = ft_strlen(line);
		if (ft_strlen(line) != (size_t)mpp->x)
			return (-1);
		mpp->y++;
	}
	close(fd);
	return (0);
}




int		load_map(char *argv)
{
	// int				fd;
	// char			*line;
	int				ret;
	t_map_params	mpp;


	// fd = open(argv, O_RDONLY);
	// if (fd == -1)
	// 	return (-1);
	ret = check_map(argv, &mpp);
	if (ret == -1)
		return (ret);
	printf("x:%dy:%d\n", mpp.x, mpp.y);

	// mpp.y = 0;
	// line = 0;
	// while (1)
	// {
	// 	ret = get_next_line(fd, &line);

	// 	if (ret == -1)
	// 		return (ret);
	// 	if (ret == 0)
	// 		break;
	// 	map.x = ft_strsplit(line,)
	// 	printf("x==%d\n", mpp.x);
	// 	mpp.map[mpp.y] = ft_aatoii(ft_strsplit(line, ' ')); //leaks possbile ici
	// 	for (int i = 0; i < 20; ++i)
	// 	{
	// 		printf("%d\n", mpp.map[mpp.y][i]);
	// 	}
	// 	mpp.y++;
	// }
	return (0);
}
