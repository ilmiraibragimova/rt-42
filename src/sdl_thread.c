/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 21:28:17 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 22:17:51 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_thread(t_rt *r, t_rt *params[N_THRED])
{
	int count;

	count = 0;
	while (count < N_THRED)
	{
		if (!(params[count] = thread_copy(r, count)))
			ft_put_error("failed to copy param in thread\n");
		++count;
	}
}

static int	calc(void *ptr)
{
	t_rt		*thread;

	thread = (t_rt*)ptr;
	if (thread->stereoscopy)
		ft_stereoscopy(thread);
	else if (thread->blur)
		ft_blur(thread);
	else
		ft_render(thread);
	return (0);
}

void		threads_loop(t_rt *params[N_THRED])
{
	int			count;
	int			thread_return_value;
	SDL_Thread	*thread[N_THRED];

	count = 0;
	while (count < N_THRED)
	{
		thread[count] = SDL_CreateThread(calc, "TestThread",\
		(void *)params[count]);
		count++;
	}
	while (count--)
		SDL_WaitThread(thread[count], &thread_return_value);
}

void		free_thread(t_rt *thread[N_THRED])
{
	int count;

	count = 0;
	while (count < N_THRED)
	{
		free(thread[count]->obj);
		free(thread[count]->ray);
		free(thread[count]);
		++count;
	}
}

void		threads(t_rt *r)
{
	t_rt		*thread[N_THRED];

	init_thread(r, thread);
	threads_loop(thread);
	free_thread(thread);
}
