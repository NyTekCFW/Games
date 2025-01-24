/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_sprites.h                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:10:08 by NyTekCFW                                 */
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
	u16					pal_size;
	void				(*pal_callback)(u16 *);
	const u16			*pal;
	const u8			*img;
	struct sprite_s		*next;
}ALIGNED(8)	t_sprites;

typedef struct texture_s
{
	t_sprites	sprites;
	u16			sprites_count;
}ALIGNED(8)	t_texture;

void		purge_sprites(void);
void		register_sprite(const char *name, const u16 *palette, u16 pal_size, void (*pal_callback)(u16 *), const u8 *sprite, u16 width, u16 height, u8 n_image);
t_sprites	*get_sprite(const char *name);
#endif