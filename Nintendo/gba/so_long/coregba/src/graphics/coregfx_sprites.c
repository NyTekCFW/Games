/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_sprites.c                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 23/12/2024 19:57:32 by NyTekCFW                                 */
/*   Updated: 24/12/2024 20:20:50 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

static int	purge_sprite(t_texture *texture, t_sprites *prev, t_sprites *list)
{
	if (texture->sprites_count > 0)
		texture->sprites_count -= 1;
	if (prev && prev->next)
		return (xfree((void **)&prev->next), 1);
	return (0);
}

/// @brief purges all sprites registered
/// @param  
void	purge_sprites(void)
{
	t_texture	*texture = get_texture();
	t_sprites	*head = &texture->sprites;
	t_sprites	*list = head;
	t_sprites	*prev = head;

	while (list)
	{
		while (list->next)
		{
			prev = list;
			list = list->next;
		}
		if (!purge_sprite(texture, prev, list))
			break ;
		else
			list = head;
	}
}

static void	store_sprites(t_sprites *new)
{
	t_texture	*texture = get_texture();
	t_sprites	*sh = &texture->sprites;

	if (!texture->sprites_count)
		xmemcpy(sh, new, sizeof(t_sprites));
	else
	{
		while (sh && sh->next)
			sh = sh->next;
		if (xalloc((void **)&sh->next, sizeof(t_sprites), 1))
			xmemcpy(sh->next, new, sizeof(t_sprites));
	}
	++texture->sprites_count;
}

void	register_sprite(const char *name, u16 *pal, u8 *sprite, u16 width, u16 height, u8 n_image)
{
	t_sprites	box;

	if (name && name[0] && !get_sprite(name))
	{
		box.h_name = fnv1a_hash(name);
		box.width = width;
		box.height = height;
		box.img_count = n_image;
		box.next = NULL;
		box.pal = pal;
		box.img = sprite;
		store_sprites(&box);
	}
}

t_sprites	*get_sprite(const char *name)
{
	t_sprites	*sh = &get_texture()->sprites;
	u32			h_name = 0;

	if (!name && !name[0])
		return (NULL);
	h_name = fnv1a_hash(name);
	while (sh)
	{
		if (sh->h_name == h_name)
			return (sh);
		sh = sh->next;
	}
	return (NULL);
}
