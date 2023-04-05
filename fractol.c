/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:22:58 by truangsi          #+#    #+#             */
/*   Updated: 2023/04/05 17:46:07 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int	handle_no_event(void *data)
// {
// 	if (data)
// 		return (0);
// 	return (0);
// }

int	handle_input(int keysym, t_frac *fr)
{
	// printf("%d\n", keysym);
	if (keysym == K_ESC)
		mlx_destroy_image(fr->mlx, fr->win_ptr);
	return (0);
}

int	handle_keypress(int key, t_frac *fr)
{
	if (key == K_ESC)
	{
		mlx_destroy_window(fr->mlx, fr->win_ptr);
		exit (0);
	}
	return (0);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

void	my_mlx_pixel_put(t_frac *fr, int x, int y, int color)
{
	char	*dst;

	dst = fr->addr + (y * fr->line_length + x * (fr->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	render_rect(t_frac *fr, t_rect rect, int color)
{
	int	i;
	int j;

	if (!fr->win_ptr)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
			while (j < rect.x + rect.width)
				my_mlx_pixel_put(fr, j++, i, color);
			++i;
	}
	return (0);
}

void	render_background(t_frac *fr, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			my_mlx_pixel_put(fr, j++, i, color);
		i++;
	}
}

void	render(t_frac *fr)
{
	render_background(fr, GREY);
	render_rect(fr, (t_rect) {WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100}, RED);
	render_rect(fr, (t_rect) {0, 0, 100, 100}, BLUE);
	mlx_put_image_to_window(fr->mlx, fr->win_ptr, fr->img, 0, 0);
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
	// my_mlx_pixel_put(&fr, 5, 5, 0x00FF0000);
	// render_background(&fr, GREY);
	// render_rect(&fr, (t_rect) {WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100}, RED);
	// render_rect(&fr, (t_rect) {0, 0, 100, 100}, BLUE);
	// mlx_put_image_to_window(fr.mlx, fr.win_ptr, fr.img, 0, 0);

	// setup hooks
	// mlx_loop_hook(fr.mlx, &handle_no_event, &fr);
	mlx_key_hook(fr.win_ptr, &handle_input, &fr);
	render(&fr);
	// mlx_loop_hook(fr.mlx, &handle_no_event, &fr);
	mlx_hook(fr.win_ptr, 2, 0, &handle_keypress, &fr);

	mlx_loop(fr.mlx);
}