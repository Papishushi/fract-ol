/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:53:36 by dmoliner          #+#    #+#             */
/*   Updated: 2023/12/02 23:59:16 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <mlx.h>

# define WDTH 1024
# define HGHT 1024
# define MAX_ITER 100
# define THRESHOLD 4.0

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}	t_rgb;

typedef enum e_fractal_type{
	MANDELBROT,
	JULIA,
	APOLLONIAN_GASKET,
}	t_fractal_type;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bitspp;
	int		line_length;
	int		endian;
}				t_texture;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_texture		txr;
	double			zm;
	t_vector		cam;
	t_vector		chunk_size;
	t_fractal_type	type;
}	t_data;

int		ft_close_task(void *param);
int32_t	ft_check_apollonian(t_complex z);
int32_t	ft_check_julia(t_complex z, t_complex c);
int32_t	ft_check_mandelbrot(t_complex c);
int		my_scrollhook(int mouseKey, void *param);
int		my_cursorhook(int x, int y, void *param);
int		ft_hook(int keycode, void *param);
void	render_loop(t_data *fol);
void	chunk_inner_loop(int x, int y, t_complex c, t_data *fol);
void	calculate_chunk(int start_x, int end_x, int start_y, int end_y, \
t_data *fol);
int		ft_render(void *param);
#endif
