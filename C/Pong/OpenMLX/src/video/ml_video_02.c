/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_video_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:58:27 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 14:21:39 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

char	*get_video_path(char *buffer, char *name)
{
	size_t	len;

	xmemset(buffer, 0, 128);
	xstrcpy(buffer, EXPORT_PATH);
	len = xstrlen(buffer);
	if (len + xstrlen(name) + xstrlen(".vlx") < 128)
	{
		xstrcpy(buffer + len, name);
		len = xstrlen(buffer);
		xstrcpy(buffer + len, ".vlx");
		return (buffer);
	}
	xwrite(1, "Error : name too long\n", 22);
	return (NULL);
}
