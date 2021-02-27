/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:29:11 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/24 18:29:15 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	add_to_queue(int id, int queue[], int pnum)
{
	int		i;

	i = 0;
	while (i < pnum)
	{
		if (queue[i] == id)
			return ;
		if (queue[i] == -1)
		{
			queue[i] = id;
			return ;
		}
		++i;
	}
}

void	remove_from_queue(int id, int queue[], int pnum)
{
	int		i;

	i = 0;
	while (i < pnum)
	{
		if (queue[i] == id)
		{
			while (i < pnum)
			{
				if (queue[i + 1] == -1)
				{
					queue[i] = -1;
					return ;
				}
				if ((i + 1) < pnum)
					queue[i] = queue[i + 1];
				else
					queue[i] = -1;
				++i;
			}
			return ;
		}
		++i;
	}
}

void	move_queue(int queue[], int pnum)
{
	int		i;

	i = 0;
	while (i < pnum)
	{
		if (queue[i + 1] == -1)
		{
			queue[i] = -1;
			return ;
		}
		if ((i + 1) < pnum)
			queue[i] = queue[i + 1];
		else
			queue[i] = -1;
		++i;
	}
}

void	init_queue(int *queue, int pnum)
{
	int		i;

	i = 0;
	while (i < pnum)
	{
		queue[i] = -1;
		++i;
	}
}
