/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:45:51 by dmoliner          #+#    #+#             */
/*   Updated: 2023/12/02 23:59:15 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"
#include "../header/ft_printf.h"
#include "../libft/libft.h"

void	initialize_fractol(t_data *fol)
{
	fol->cam.x = 0;
	fol->cam.y = 0;
	fol->zm = 1;
	fol->chunk_size.x = WDTH * 0.125;
	fol->chunk_size.y = HGHT * 0.125;
}

void	hook_setting(t_data *fol)
{
	mlx_loop_hook(fol->mlx, ft_render,(void *) fol);
	//TENGO QUE ARREGLAR ESTO FOL CAUSA SEGFAULTS EN LOS ELEMENTOS
	// NO SE AHORA MISMO COMO ARREGLAR ESTO SIN UNA VARIABLE GLOBAL
	mlx_hook(fol->win, 6, 0, &my_cursorhook,(void *) fol);
	mlx_hook(fol->win, 17, 1L << 17, &ft_close_task,(void *) fol);
	mlx_mouse_hook(fol->win, &my_scrollhook,(void *) fol);
	mlx_key_hook(fol->win, &ft_hook,(void *) fol);
}

void	display_help( void )
{
	printf("Fractol Program\n\n");
	printf("This program displays various types of fractals in a window.\n\n");
	printf("Usage: fractol [type] [options]\n\n");
	printf("type - The type of fractal to display (mandelbrot, julia, ...)\n");
	printf("Examples:\n\n");
	printf("Display the Mandelbrot fractal:\n");
	printf("$ fractol mandelbrot\n\n");
	printf("If no parameters are provided or if the parameters are invalid,");
	printf(" the program will display this help message and exit.");
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_data	fol;
	int			i;

	i = -1;
	if (argc != 2)
	{
		display_help();
		exit(EXIT_SUCCESS);
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(argv[1], "julia", 5) == 0 && ft_strlen(argv[1]) == 5)
		fol.type = JULIA;
	else if (ft_strncmp(argv[1], "mandelbrot", 10) == 0 && ft_strlen(argv[1]) == 10)
		fol.type = MANDELBROT;
	else if (ft_strncmp(argv[1], "apollonian", 10) == 0 && ft_strlen(argv[1]) == 10)
		fol.type = APOLLONIAN_GASKET;
	else
	{
		display_help();
		exit(EXIT_SUCCESS);
		return (EXIT_SUCCESS);
	}
	fol.mlx = mlx_init();
	if (!fol.mlx)
		return (EXIT_FAILURE);
	fol.win = mlx_new_window(fol.mlx, WDTH, HGHT, "fract-ol");
	if (!fol.win)
		return (EXIT_FAILURE);
	fol.txr.img = mlx_new_image(fol.mlx, WDTH, HGHT);
	if (!fol.txr.img)
	{
		mlx_destroy_window(fol.mlx, fol.win);
		return (EXIT_FAILURE);
	}
	else
		fol.txr.addr = mlx_get_data_addr(fol.txr.img, &fol.txr.bitspp, \
		&fol.txr.line_length, &fol.txr.endian);
	initialize_fractol(&fol);
	printf("Before Callback: Sending pointer at address %p\n", (void *)&fol);
	hook_setting(&fol);
	mlx_loop(fol.mlx);
	return (ft_close_task(NULL));
}
