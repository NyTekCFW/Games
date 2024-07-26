/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_video_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:30:08 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 19:45:46 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief Quit current playing video
/// @param vd video settings from t_ml struct
static void	exit_video(t_video *vd)
{
	if (vd)
	{
		vd->status = 0;
		vd->rate = 0;
		xmemset(vd->buffer, 0, sizeof(vd->buffer));
		close(vd->fd);
	}
}

/// @brief this function need to be in a loop rendering
///in occurence the loop function that show everything on your project
/// @param at where the video is displayed on window
void	display_video(t_vec2 at)
{
	static int		fps = 0;
	t_ml			*lx;
	t_video			*vd;
	t_shaders		*sh;

	lx = gmlx(ACT_GET);
	if (lx && lx->video.status && !lx->video.paused)
	{
		vd = &lx->video;
		if (vd->fd > 0 && fps >= vd->rate)
		{
			fps = 0;
			sh = get_img(vd->buffer);
			if (sh)
			{
				if (read(vd->fd, sh->img.addr, sh->img.size) <= 0)
					return (stop_video(), (void)0);
				print_img(at, vd->buffer);
			}
		}
		fps += 1;
	}
	else
		fps = 0;
}

/// @brief stop current playing
///video by calling exit_video
/// @param  
void	stop_video(void)
{
	t_ml		*lx;
	t_video		*vd;

	lx = gmlx(ACT_GET);
	if (lx && lx->video.status)
	{
		vd = &lx->video;
		if (vd->fd > 0)
			exit_video(vd);
	}
}

/// @brief Pause or resume the current video
/// @param pause VIDEO_RESUME / VIDEO_PAUSE
void	set_video_status(int pause)
{
	t_ml	*lx;
	t_video	*vd;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		vd = &lx->video;
		if (vd->fd > 0 && vd->status)
			vd->paused = pause;
	}
}

/// @brief Initialise and start the selected video
/// @param name name of the video e.g:
///"gameplay_rotd"
/// @param rate speed of video (1-5)
void	start_video(char *name, int rate)
{
	t_ml		*lx;
	t_video		*vd;
	t_shaders	tmp;

	lx = gmlx(ACT_GET);
	tmp = (t_shaders){0};
	if (lx && !lx->video.status)
	{
		vd = &lx->video;
		vd->fd = open(get_video_path(vd->path, name), O_RDONLY, 0777);
		if (vd->fd > 0)
		{
			vd->status = 1;
			if (read(vd->fd, &tmp, sizeof(tmp)) > 0)
			{
				if (!get_img(name))
					create_img((t_ui){tmp.img.width,
						tmp.img.height, 0}, fill_img_color, name);
				xstrcpy(vd->buffer, name);
				return (vd->rate = rate, (void)0);
			}
			exit_video(vd);
		}
	}
}
