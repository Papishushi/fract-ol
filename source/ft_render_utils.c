/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:06:41 by dmoliner          #+#    #+#             */
/*   Updated: 2023/12/02 23:59:15 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

void	my_mlx_put_pixel(t_texture *texture, int x, int y, int color)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_length + x * \
	(texture->bitspp / 8));
	*(unsigned int *)dst = color;
}

int32_t	ft_pack_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (a << 31 | r << 16 | g << 8 | b);
}

int32_t	iter_to_color(int iterations)
{
	double	hue;
	t_rgb	t;
	t_rgb	rgb;

	hue = (double)iterations / MAX_ITER * 360.0;
	t.r = (1 - fabs(2 * 0.5 - 1)) * (1 - fabs(2 * 0.5 - 1));
	t.g = t.r * (1 - fabs(fmod(hue / 60.0, 2) - 1));
	t.b = 0.5 * (1 - t.g);
	if (hue < 60)
		rgb = (t_rgb){t.r, t.g, 0};
	else if (hue < 120)
		rgb = (t_rgb){t.g, t.r, 0};
	else if (hue < 180)
		rgb = (t_rgb){0, t.r, t.g};
	else if (hue < 240)
		rgb = (t_rgb){0, t.g, t.r};
	else if (hue < 300)
		rgb = (t_rgb){t.g, 0, t.r};
	else if (hue < 360)
		rgb = (t_rgb){t.r, 0, t.g};
	else
		rgb = (t_rgb){0, 0, 0};
	rgb = (t_rgb){(rgb.r + t.r) * 255, (rgb.g + t.g) * 255, \
	(rgb.b + t.b) * 255};
	return (ft_pack_pixel(rgb.r, rgb.g, rgb.b, 0xFF));
}

void	chunk_inner_loop(int x, int y, t_complex c, t_data *fol)
{
	t_complex	z;
	uint32_t	color;

	color = 0;
	z.real = ((x + fol->cam.x) - WDTH * 0.5) / \
	(WDTH * 0.25 * fol->zm * fol->zm);
	z.imag = ((y + fol->cam.y) - HGHT * 0.5) / \
	(HGHT * 0.25 * fol->zm * fol->zm);
	if (fol->type == MANDELBROT)
		color = iter_to_color(ft_check_mandelbrot(z));
	else if (fol->type == JULIA)
		color = iter_to_color(ft_check_julia(z, c));
	else if (fol->type == APOLLONIAN_GASKET)
		color = iter_to_color(ft_check_apollonian(z));
	else
		color = 0xFF;
	my_mlx_put_pixel(&fol->txr, x, y, color);
}

void	render_loop(t_data *fol)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	end_x = 0;
	end_y = 0;
	start_x = 0;
	while (start_x < WDTH)
	{
		start_y = 0;
		while (start_y < WDTH)
		{
			end_x = start_x + fol->chunk_size.x;
			end_y = start_y + fol->chunk_size.y;
			if (end_x > WDTH)
				end_x = WDTH;
			if (end_y > HGHT)
				end_y = HGHT;
			calculate_chunk(start_x, end_x, start_y, end_y, fol);
			start_y += fol->chunk_size.y;
		}
		start_x += fol->chunk_size.x;
	}
}
