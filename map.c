/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:17:02 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/25 15:17:16 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					check_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if ((line[i] != ' ') && (line[i] != '-')
			&& ((line[i] < '0') || (line[i] > '9')))
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

int					check_map(char *argv, t_map_params *mpp)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (-1);
	mpp->y = 0;
	while (1)
	{
		mpp->ret = get_next_line(fd, &line);
		if (mpp->ret == -1)
			return (-1);
		if ((mpp->y == 0) && (mpp->ret == 0))
			return (-2);
		if (mpp->ret == 0)
			break ;
		mpp->ret = check_map_line(line);
		if (mpp->ret == -1)
			return (-3);
		mpp->y++;
		free(line);
		line = 0;
	}
	close(fd);
	return (0);
}

int					*aatoii(char **pptr, int *mppx)
{
	int		*tab;
	int		j;

	*mppx = 0;
	while (pptr[*mppx] != 0)
	{
		(*mppx)++;
	}
	if (!(tab = (int*)malloc((*mppx) * sizeof(int))))
		return (0);
	*mppx = 0;
	while (pptr[*mppx] != 0)
	{
		tab[*mppx] = ft_atoi(pptr[*mppx]);
		(*mppx)++;
	}
	j = 0;
	while (pptr[j] != NULL)
	{
		free(pptr[j]);
		j++;
	}
	free(pptr);
	return (tab);
}

t_map_params		stock_map(int fd, t_map_params mpp)
{
	char			*line;
	int				temp;

	temp = 0;
	while (1)
	{
		mpp.ret = get_next_line(fd, &line);
		if (mpp.ret == -1)
			return (mpp);
		if (mpp.ret == 0)
			break ;
		mpp.map[mpp.y] = aatoii(ft_strsplit(line, ' '), &mpp.x);
		if (mpp.y == 0)
			temp = mpp.x;
		else if (mpp.x != temp)
		{
			mpp.ret = -4;
			return (mpp);
		}
		mpp.y++;
		free(line);
		line = NULL;
	}
	return (mpp);
}

t_map_params		load_map(char *argv)
{
	t_map_params	mpp;
	int				fd;

	mpp.ret = check_map(argv, &mpp);
	if ((mpp.ret == -1) || (mpp.ret == -2) || (mpp.ret == -3))
		return (mpp);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		mpp.ret = -1;
		return (mpp);
	}
	mpp.map = (int**)malloc(sizeof(int*) * mpp.y);
	if (mpp.map == NULL)
	{
		mpp.ret = -1;
		return (mpp);
	}
	mpp.y = 0;
	mpp = stock_map(fd, mpp);
	close(fd);
	return (mpp);
}
