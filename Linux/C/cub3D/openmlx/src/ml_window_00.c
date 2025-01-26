/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_window_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:40:39 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/03 22:47:59 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/openmlx.h"

/// @brief create basics shaders of openmlx
/// @param lx gmlx pointer
static void	_ml_set_win_data(t_ml *lx)
{
	create_img((t_ui){lx->width, lx->height, lx->purge_color},
		fill_img_color, "clear_window");
	create_img((t_ui){560, 20, 0},
		fill_img_color, "imgui_dbg_menu");
	create_img((t_ui){646, 645, 0},
		fill_img_color, "minimap");
	create_img((t_ui){1280, 720, 0},
		fill_img_color, "framework");
	register_img("./textures/fonts/monospace_ttf.xpm");
	split_image("/monospace_ttf.xpm", "monospace_", 32, 0);
	_ml_set_win_data_pixel();
	lx->purge_window();
}

/// @brief create a window and open it
/// @param title title of the window
/// @return 
int	_ml_create_window(char *title, t_vec2 w, int autosize)
{
	t_ml	*lx;
	t_vec2	u;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		lx->ptr = mlx_init();
		if (lx->ptr)
		{
			mlx_get_screen_size(lx->ptr, &u.x, &u.y);
			if ((u.x * u.y) < (w.x * w.y) && (u.x * u.y) > 1)
				return (printf("Error: %ix%i format is not supported!\n",
						u.x, u.y), xfree((void **)&lx->ptr), gmlx(ACT_FREE), 0);
			_ml_set_window_size(w.x, w.y);
			if (autosize)
				_ml_set_window_size(u.x, u.y);
			lx->win = mlx_new_window(lx->ptr, lx->width, lx->height, title);
			if (lx->win)
				return (_ml_set_win_data(lx), 1);
			mlx_destroy_display(lx->ptr);
			xfree((void **)&lx->ptr);
		}
	}
	return (0);
}

/// @brief set width and height of the futur window
/// @param w width
/// @param h height
/// @return 
int	_ml_set_window_size(int w, int h)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		lx->width = w;
		lx->height = h;
		return (1);
	}
	return (0);
}

/// @brief purge window and print cleared color
/// @param  
void	_ml_purge_window(void)
{
	t_ml		*lx;

	lx = gmlx(ACT_GET);
	if (lx && lx->ptr && lx->win)
	{
		mlx_clear_window(lx->ptr, lx->win);
		print_img((t_vec2){0, 0}, "clear_window");
	}
}

/// @brief purge openmlx stuff
/// @param  
void	_ml_quit(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		purge_textures();
		if (lx->ptr && lx->win)
		{
			mlx_destroy_window(lx->ptr, lx->win);
			lx->win = NULL;
		}
		if (lx->ptr)
		{
			mlx_destroy_display(lx->ptr);
			xfree((void **)&lx->ptr);
		}
		gmlx(ACT_FREE);
	}
}
