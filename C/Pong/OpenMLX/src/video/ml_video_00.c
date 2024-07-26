/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_video_00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:29:35 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/21 19:46:29 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief Write the header of the exported video
/// @param rec record settings from t_ml struct
/// @param track_img the image that will be tracked
static void	write_header_bin(t_rec *rec, char *track_img)
{
	t_shaders	*sh;
	t_shaders	tmp;

	sh = get_img(track_img);
	tmp = (t_shaders){0};
	if (sh && rec)
	{
		xmemcpy(&tmp, sh, sizeof(t_shaders));
		tmp.next = NULL;
		tmp.is_stored = 0;
		tmp.img.ptr = NULL;
		tmp.img.addr = NULL;
		xwrite(rec->fd, &tmp, sizeof(tmp));
	}
}

/// @brief Print info about the current record, stop if the video reach 4Go
/// @param rec record settings from t_ml struct
static void	write_record_info(t_rec *rec)
{
	char	buffer[128];

	if (rec)
	{
		xmemset(buffer, 0, sizeof(buffer));
		xstrcpy(buffer, "Video buffer : \0");
		if (rec->size >= 1000)
			buffer[xstrlen(buffer)] = 0x30 + (rec->size / 1000);
		if (rec->size >= 100)
			buffer[xstrlen(buffer)] = 0x30 + ((rec->size / 100) % 10);
		if (rec->size >= 10)
			buffer[xstrlen(buffer)] = 0x30 + ((rec->size / 10) % 10);
		buffer[xstrlen(buffer)] = 0x30 + (rec->size % 10);
		xstrcpy(buffer + xstrlen(buffer), " / 4096 Mo\n");
		xwrite(1, buffer, xstrlen(buffer));
		if (rec->size >= 4096)
		{
			stop_record();
			xwrite(1, "Video size reached limit of 4Go\n", 32);
		}
	}
}

/// @brief Initialise all param & info for recording
/// @param name the exported video name e.g
///"gameplay_rotd"
/// @param track_img the image that will be recorded
/// @param rate number of frame that will be ignored 
/// e.g : 2 will save 1 / 2 frame (1-8)
void	init_record(char *name, char *track_img, int rate)
{
	t_ml	*lx;
	t_rec	*rec;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		rec = &lx->record;
		if (rec && rec->status == 0)
		{
			rec->size = 0;
			rec->status = 1;
			rec->rate = rate;
			rec->fd = open(get_video_path(rec->buffer, name),
					O_RDWR | O_CREAT | O_TRUNC, 0777);
			if (rec->fd <= 0)
			{
				rec->status = 0;
				xmemset(rec->buffer, 0, sizeof(rec->buffer));
				return ;
			}
			xstrcpy(rec->tracked, track_img);
			write_header_bin(rec, track_img);
		}
	}
}

/// @brief Stop recording and clear all data's
/// @param  
void	stop_record(void)
{
	t_ml	*lx;
	t_rec	*rec;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		rec = &lx->record;
		if (rec && rec->status)
		{
			rec->status = 0;
			close(rec->fd);
			xmemset(rec->buffer, 0, sizeof(rec->buffer));
		}
	}
}

/// @brief this function need to be placed before or after
///the print_img of the tracked image.
/// @param  
void	save_record(void)
{
	static int		fps = 0;
	t_ml			*lx;
	t_rec			*rec;
	t_shaders		*sh;

	lx = gmlx(ACT_GET);
	if (lx && lx->record.fd > 0 && lx->record.status)
	{
		rec = &lx->record;
		sh = get_img(rec->tracked);
		fps += 1;
		if (sh && rec && fps >= rec->rate)
		{
			xwrite(rec->fd, sh->img.addr, sh->img.size);
			rec->size += sh->img.size / 1048576U;
			write_record_info(rec);
			fps = 0;
		}
	}
}
