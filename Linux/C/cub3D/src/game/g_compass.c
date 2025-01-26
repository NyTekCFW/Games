/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_compass.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:43:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/12/08 12:16:06 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine/common.h"

static void	set_compass_text(char *dir[])
{
	dir[0] = "N";
	dir[1] = "NE";
	dir[2] = "E";
	dir[3] = "SE";
	dir[4] = "S";
	dir[5] = "SW";
	dir[6] = "W";
	dir[7] = "NW";
}

static void	draw_compass_text(int index[], double angle)
{
	char	buffer[32];
	char	*tmp;
	char	*dir[8];

	set_compass_text(dir);
	xmemset(buffer, 0, sizeof(buffer));
	xstrcpy(buffer, dir[index[0]]);
	xstrcpy(&buffer[xstrlen(buffer)], "----");
	xstrcpy(&buffer[xstrlen(buffer)], dir[index[1]]);
	xstrcpy(&buffer[xstrlen(buffer)], "(");
	tmp = va_float((float)angle, 1);
	if (tmp)
	{
		xstrcpy(&buffer[xstrlen(buffer)], tmp);
		xstrcpy(&buffer[xstrlen(buffer)], ")");
		xfree((void **)&tmp);
	}
	xstrcpy(&buffer[xstrlen(buffer)], "----");
	xstrcpy(&buffer[xstrlen(buffer)], dir[index[2]]);
	ctypewritter("framework", buffer,
		(t_vec2){640 - (r_textwidth(buffer) / 2), 4}, 0xFF0000);
}

void	draw_compass(void)
{
	t_player	*user;
	double		angle;
	double		fangle;
	int			index[3];

	user = get_user();
	if (user)
	{
		angle = atan2(user->dir.y, user->dir.x) * (180.0 / PI);
		if (angle < 0)
			angle += 360.0;
		fangle = fmod(angle + 90.0, 360.0);
		if (fangle < 0)
			fangle += 360.0;
		index[1] = (int)((fangle + 22.5) / 45.0) % 8;
		index[0] = index[1] - 1;
		if (index[0] < 0)
			index[0] = 7;
		index[2] = index[1] + 1;
		if (index[2] > 7)
			index[2] = 0;
		draw_compass_text(index, angle);
	}
}
