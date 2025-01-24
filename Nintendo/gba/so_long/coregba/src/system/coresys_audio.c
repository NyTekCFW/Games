/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_audio.c                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 11/01/2025 20:09:37 by NyTekCFW                                 */
/*   Updated: 11/01/2025 20:09:38 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

static int	purge_sfx_data(t_audio *audio, t_sfx *prev, t_sfx *list)
{
	if (audio->sfx_count > 0)
		audio->sfx_count -= 1;
	if (prev && prev->next)
		return (xfree((void **)&prev->next), 1);
	return (0);
}

static void	store_sfx(t_sfx *new)
{
	t_audio	*audio = get_audio();
	t_sfx	*sfx = &audio->sfx;

	if (!audio->sfx_count)
		xmemcpy(sfx, new, sizeof(t_sfx));
	else
	{
		while (sfx && sfx->next)
			sfx = sfx->next;
		if (xalloc((void **)&sfx->next, sizeof(t_sfx), 1))
			xmemcpy(sfx->next, new, sizeof(t_sfx));
	}
	++audio->sfx_count;
}

/// @brief purges all sfx registered
/// @param  
void	purge_sfx(void)
{
	t_audio	*audio = get_audio();
	t_sfx	*head = &audio->sfx;
	t_sfx	*list = head;
	t_sfx	*prev = head;

	while (list)
	{
		while (list->next)
		{
			prev = list;
			list = list->next;
		}
		if (!purge_sfx_data(audio, prev, list))
			break ;
		else
			list = head;
	}
}

void	register_sfx(const char *name, const s8 *sfx_raw_data, u32 len, bool loop_sfx)
{
	t_sfx	sfx;
	u16		tick = 65536 - get_audio()->sfx_hz;

	if (name && name[0] && sfx_raw_data && len > 0 && !get_sfx(name))
	{
		sfx.h_name = fnv1a_hash(name);
		sfx.raw = sfx_raw_data;
		sfx.len = len;
		sfx.pos = (len * tick * 3.5611774E-6F);
		sfx.loop_sfx = loop_sfx;
		sfx.next = NULL;
		store_sfx(&sfx);
	}
}

t_sfx	*get_sfx(const char *name)
{
	t_sfx	*sfx = &get_audio()->sfx;
	u32		h_name = 0;

	if (!name && !name[0])
		return (NULL);
	h_name = fnv1a_hash(name);
	while (sfx)
	{
		if (sfx->h_name == h_name)
			return (sfx);
		sfx = sfx->next;
	}
	return (NULL);
}

void	set_audio_hz(enum e_sfx_hz hz)
{
	t_audio	*audio = get_audio();

	switch (hz)
	{
		case SFX_4000_HZ:audio->sfx_hz = 61342; break ;
		case SFX_8000_HZ:audio->sfx_hz = 63439; break ;
		case SFX_11025_HZ:audio->sfx_hz = 64015; break ;
		case SFX_16000_HZ:audio->sfx_hz = 64488; break ;
		case SFX_22050_HZ:audio->sfx_hz = 64776; break ;
		default:audio->sfx_hz =  0; break ;
	}
}
