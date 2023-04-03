/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:22:58 by truangsi          #+#    #+#             */
/*   Updated: 2023/04/03 15:50:39 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_no_event(void *data)
{
	if (data)
		return (0);
	return (0);
}

int	handle_input(int keysym, t_frac *fr)
{
	// printf("%d\n", keysym);
	if (keysym == K_ESC)
		mlx_destroy_image(fr->mlx, fr->win_ptr);
	return (0);
}

int	handle_keypress(int key, t_frac *fr)
{
	printf("in press\n");
	if (key == K_ESC)
		mlx_destroy_window(fr->mlx, fr->win_ptr);
	printf("key: %d\n", key);
	exit (0);
}

int	handle_keyrelease(int key, void *data)
{
	printf("in release\n");
	printf("key: %d\n", key);
	if (data)
		return (0);
	return (0);
}

void	my_mlx_pixel_put(t_frac *fr, int x, int y, int color)
{
	char	*dst;

	dst = fr->addr + (y * fr->line_length + x * (fr->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	main(void)
{
	t_frac	fr;

	fr.mlx = mlx_init();
	if (!fr.mlx)
		return (0);
	fr.win_ptr = mlx_new_window(fr.mlx,  1000, 1080, "fractol");
	if (!fr.win_ptr)
		return (0);

	// create image
	fr.img = mlx_new_image(fr.mlx, 1000, 1080);
	fr.addr = mlx_get_data_addr(fr.img, &fr.bits_per_pixel, &fr.line_length, &fr.endian);
	my_mlx_pixel_put(&fr, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(fr.mlx, fr.win_ptr, fr.img, 0, 0);

	// setup hooks
	// mlx_loop_hook(fr.mlx, &handle_no_event, &fr);
	// mlx_key_hook(fr.win_ptr, &handle_input, &fr);
	mlx_loop_hook(fr.mlx, &handle_no_event, &fr);
	mlx_hook(fr.win_ptr, 2, 0, &handle_keypress, &fr);
	// mlx_hook(fr.win_ptr, 3, 0, &handle_keyrelease, &fr);

	mlx_loop(fr.mlx);
	// exit the loop if no window left, and execute this code
	mlx_destroy_window(fr.mlx, fr.win_ptr);
}