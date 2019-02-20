/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:36:08 by jleblond          #+#    #+#             */
/*   Updated: 2019/01/15 15:36:10 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
	t_map_params mpp;

	if (argc != 2)
	{
		ft_putendl("Usage : ./fdf <map file name>");
		return (0);
	}
	mpp = load_map(argv[1]);
	if (mpp.ret == -2)
	{
		ft_putendl("map file has a problem");
		return (0);
	}
	if (mpp.ret == -1)
	{
		ft_putendl("error");
		return (0);
	}
	mpp.ret = fdf(mpp);
	if (mpp.ret == -1)
	{
		printf("error");
	}
	return (0);
}

