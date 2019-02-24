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
			return (- 1);
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
		return (-2);
	mpp->y = 0;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (-2);
		if ((mpp->y == 0) && (ret == 0))
		{
			ft_putendl("map file should not be empty");
			return (-2);
		}
		if (ret == 0)
			break;
		ret = check_map_line(line);
		if (ret == -1)
		{
			ft_putendl("content of map file is not right");
			return (-2);
		}
		mpp->y++;
	}
	close(fd);
	return (0);
}
//Il gere pas la cas    la carte n'est pas en rectangle

int		*aatoii(char **pptr, int *mppx)
{
	int		*tab;



	*mppx = 0;

	while (pptr[*mppx] != 0)
	{
		(*mppx)++;
	}
	tab = (int*)malloc((*mppx) * sizeof(int));
	if (tab == NULL)
		return (0);
	*mppx = 0;
	while (pptr[*mppx] != 0)
	{
		tab[*mppx] = ft_atoi(pptr[*mppx]);
		(*mppx)++;
	}

	int i;
	int j;
	i= 0;
	j = 0;
	while (pptr[j] != NULL)
	{
		i=0;
		while (pptr[j][i])
		{
			printf("%c", pptr[j][i]);
			i++;
		}
		free(pptr[j]);
		printf("\n");
		j++;
	}
	free(pptr);

	return (tab);
}



t_map_params		load_map(char *argv)
{
	int				fd;
	char			*line;
	t_map_params	mpp;


	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		mpp.ret = -1;
		return (mpp);
	}

	mpp.ret = check_map(argv, &mpp);
	if (mpp.ret == -2)
	{
		return (mpp);
	}

	line = 0;
	mpp.map = (int**)malloc(sizeof(int*) * mpp.y);

	mpp.y = 0;
	while (1)
	{
		mpp.ret = get_next_line(fd, &line);

		if (mpp.ret == -1)
			return (mpp);
		if (mpp.ret == 0)
			break;
		printf("=>%s|\n", line);
		mpp.map[mpp.y] = aatoii(ft_strsplit(line, ' '), &mpp.x); //leaks possbile ici
		mpp.y++;
	}

	//printf("x%dy%d\n", mpp.x, mpp.y );
	return (mpp);
}
