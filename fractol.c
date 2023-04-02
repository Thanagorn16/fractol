/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:22:58 by truangsi          #+#    #+#             */
/*   Updated: 2023/04/02 16:21:37 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_frac *fr, int x, int y, int color)
{
	char	*dst;

	dst = fr->addr + (y * fr->line_length + x * (fr->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_frac	fr;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx,  1000, 1080, "fractol");
	fr.img = mlx_new_image(mlx, 1000, 1080);
	fr.addr = mlx_get_data_addr(fr.img, &fr.bits_per_pixel, &fr.line_length, &fr.endian);
	my_mlx_pixel_put(&fr, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, fr.img, 0, 0);
	mlx_loop(mlx);
}