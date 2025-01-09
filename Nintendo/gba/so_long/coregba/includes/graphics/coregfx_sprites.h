/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_sprites.h                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 23/12/2024 19:57:31 by NyTekCFW                                 */
/*   Updated: 24/12/2024 20:19:31 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREGFX_SPRITES_H
# define COREGFX_SPRITES_H

typedef struct sprite_s
{
	u32					h_name;
	u16					width;
	u16					height;
	u8					img_count;
	u8					*img;
	u16					*pal;
	struct sprite_s		*next;
}ALIGNED(4)	t_sprites;

typedef struct texture_s
{
	t_sprites	sprites;
	u16			sprites_count;
}	t_texture;

void		purge_sprites(void);
void		register_sprite(const char *name, u16 *palette, u8 *sprite, u16 width, u16 height, u8 n_image);
t_sprites	*get_sprite(const char *name);
#endif