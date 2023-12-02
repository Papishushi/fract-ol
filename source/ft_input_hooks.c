/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:03:53 by dmoliner          #+#    #+#             */
/*   Updated: 2023/12/02 23:59:15 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

int	my_scrollhook(int mouseKey, void *param)
{
	t_data	*fol;

	fol = (t_data *)param;
	printf("Inside Callback: Received pointer at address %p\n", (t_data *)param);
	if (fol == NULL)
		return (EXIT_FAILURE);
	if (mouseKey == 4)
		fol->zm += 0.1;
	else if (mouseKey == 5)
		fol->zm  -= 0.1;
	return (EXIT_SUCCESS);
}

int	my_cursorhook(int x, int y, void *param)
{
	t_data	*fol;

	fol = (t_data *)param;
	if (fol == NULL)
		return (EXIT_FAILURE);
	fol->cam.x = x - WDTH * 0.5;
	fol->cam.y = y - HGHT * 0.5;
	return (EXIT_SUCCESS);
}

int	ft_hook(int keycode, void *param)
{
	t_data	*fol;

	fol = (t_data *)param;
	if (fol == NULL)
		return (EXIT_FAILURE);
	if (53 == keycode)
		return (ft_close_task(0));
	if (126 == keycode)
		fol->cam.y -= 5;
	if (125 == keycode)
		fol->cam.y += 5;
	if (123 == keycode)
		fol->cam.x -= 5;
	if (124 == keycode)
		fol->cam.x += 5;
	return (EXIT_SUCCESS);
}
