/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:45:51 by dmoliner          #+#    #+#             */
/*   Updated: 2023/11/16 21:41:17 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MLX42/MLX42.h"

#define WIDTH 1024
#define HEIGHT 1024
#define MAX_ITER 100
#define THRESHOLD 4.0

typedef struct	s_complex
{
	double	real;
	double	imag;
}				t_complex;

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef enum {
    MANDELBROT,
    JULIA,
    APOLLONIAN_GASKET,
} t_fractal_type;

typedef struct	s_fractol
{
	mlx_image_t*	image;
	double			zoom;
	t_vector		cam;
	t_vector		chunk_size;
	uint32_t		frames;
	t_fractal_type	type;
}				t_fractol;



static t_fractol fractol;

// -----------------------------------------------------------------------------

int32_t	ft_check_julia(t_complex z, t_complex c)
{
	int		i;
	double	temp;

	i = 0;
	while (i++ < MAX_ITER)
	{
		temp = z.real;
		z.real = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * temp * z.imag + c.imag;

		if (z.real * z.real + z.imag * z.imag > THRESHOLD)
			return (i);  // Not in the Julia set
	}
	return (MAX_ITER);  // Belongs to the Julia set
}

int32_t ft_check_mandelbrot(t_complex c)
{
    t_complex	z;
    int			i;
	double		temp;

    z.real = 0.0;
    z.imag = 0.0;
    i = 0;
    while (i++ < MAX_ITER)
    {
        temp = z.real;
        z.real = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * temp * z.imag + c.imag;

        if (z.real * z.real + z.imag * z.imag > THRESHOLD)
            return (i);  // Not in the Mandelbrot set
    }

    return (MAX_ITER);  // Belongs to the Mandelbrot set
}

int32_t ft_check_apollonian(t_complex z)
{
	int i;
	double temp;

	i = 0;
	while (i++ < MAX_ITER)
	{
		temp = z.real;
		z.real = z.real * z.real - z.imag * z.imag + 0.3; // Adjust the constant for the Apollonian Gasket
		z.imag = 2 * temp * z.imag;

		if (z.real * z.real + z.imag * z.imag > THRESHOLD)
			return (i);  // Not in the Apollonian Gasket
	}
	return (MAX_ITER);  // Belongs to the Apollonian Gasket
}

int32_t	ft_pack_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int32_t iter_to_color(int iterations)
{
      // Customizing the color mapping based on HSL color space
    double hue = (double)iterations / MAX_ITER * 360.0; // Map iterations to hue (0-360 degrees)

    // Convert HSL to RGB
    double c = (1 - fabs(2 * 0.5 - 1)) * (1 - fabs(2 * 0.5 - 1));
    double x = c * (1 - fabs(fmod(hue / 60.0, 2) - 1));
    double m = 0.5 * (1 - c);

    double r, g, b;
    if (hue < 60)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if (hue < 120)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if (hue < 180)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if (hue < 240)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if (hue < 300)
    {
        r = x;
        g = 0;
        b = c;
    }
	else if (hue < 360)
	{
		r = c;
        g = 0;
        b = x;
	}
    else
    {
        r = 0;
        g = 0;
        b = 0;
    }

    // Apply lightness
    r = (r + m) * 255;
    g = (g + m) * 255;
    b = (b + m) * 255;

    return ft_pack_pixel(r, g, b, 0xFF);
}

void calculate_chunk(int start_x, int end_x, int start_y, int end_y) {
    t_complex c;
    t_complex z;
    uint32_t color;

    c.real = -0.7;
    c.imag = 0.27015;
    color = 0;
    for (int32_t x = start_x; x < end_x; ++x) {
        for (int32_t y = start_y; y < end_y; ++y) {
            z.real = ((x + fractol.cam.x) - WIDTH * 0.5) / (WIDTH * 0.25 * fractol.zoom * fractol.zoom);
            z.imag = ((y + fractol.cam.y) - HEIGHT * 0.5) / (HEIGHT * 0.25 * fractol.zoom * fractol.zoom);
			if (fractol.type == MANDELBROT)
				color = iter_to_color(ft_check_mandelbrot(z));
			else if (fractol.type == JULIA)
				color = iter_to_color(ft_check_julia(z, c));
			else if (fractol.type == APOLLONIAN_GASKET)
				color = iter_to_color(ft_check_apollonian(z, c));
			else
				color = 0xFF;
            mlx_put_pixel(fractol.image, x, y, color);
        }
    }
}

void ft_render(void* param) {
    for (int start_x = 0; start_x < WIDTH; start_x += fractol.chunk_size.x) {
        for (int start_y = 0; start_y < HEIGHT; start_y += fractol.chunk_size.y) {
            int end_x = start_x + fractol.chunk_size.x;
            int end_y = start_y + fractol.chunk_size.y;

            // Ensure the end coordinates do not exceed the image dimensions
            end_x = (end_x > WIDTH) ? WIDTH : end_x;
            end_y = (end_y > HEIGHT) ? HEIGHT : end_y;

            // Calculate the Julia set for the current chunk
            calculate_chunk(start_x, end_x, start_y, end_y);
        }
    }
}

/*void	ft_render(void* param)
{
	t_complex	c;
	t_complex	z;
	uint32_t	color;

	c.real = -0.7;
	c.imag = 0.27015;
	color = 0;
	for (int32_t x = 0; x < fractol.image->width; ++x)
	{
		for (int32_t y = 0; y < fractol.image->height; ++y)
		{
			z.real = ((x + fractol.cam.x) - WIDTH * 0.5) / (WIDTH * 0.25 * fractol.zoom * fractol.zoom);
			z.imag = ((y + fractol.cam.y) - HEIGHT * 0.5) / (HEIGHT * 0.25 * fractol.zoom * fractol.zoom);
			color = iter_to_color(ft_check_julia(z, c));
			mlx_put_pixel(fractol.image, x, y, color);
		}
	}
}*/

void my_scrollhook(double xdelta, double ydelta, void* param)
{
	// Simple up or down detection.
	if (ydelta > 0)
		fractol.zoom += 0.1;
	else if (ydelta < 0)
		fractol.zoom -= 0.1;
}

void my_cursorhook(double x, double y, void* param)
{
	fractol.cam.x = x - WIDTH * 0.5;
	fractol.cam.y = y - HEIGHT * 0.5;
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE) )
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		fractol.cam.y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		fractol.cam.y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		fractol.cam.x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		fractol.cam.x += 5;
}

void	ft_frame_control(void* param)
{
	fractol.frames++;
	if (fractol.frames > 60)
		fractol.frames = 0;
}
// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t*	mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "fract-ol", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(fractol.image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, fractol.image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	fractol.type = JULIA;
	fractol.cam.x = 0;
	fractol.cam.y = 0;
	fractol.zoom = 1;
	fractol.chunk_size.x = WIDTH * 0.125;
	fractol.chunk_size.y = HEIGHT * 0.125;

	mlx_loop_hook(mlx, ft_frame_control, mlx);
	mlx_loop_hook(mlx, ft_render, mlx);
	mlx_cursor_hook(mlx, &my_cursorhook, NULL);
	mlx_scroll_hook(mlx, &my_scrollhook, NULL);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
