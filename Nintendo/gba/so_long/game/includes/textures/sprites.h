/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   sprites.h                                                                */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:16:33 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

#pragma region PALETTE
//link pal
extern const u16	pal_sprite_link_walks[4];
extern const u16	pal_sprite_link_melee[8];
//objects
extern const u16	pal_sprites_obj[3];
#pragma endregion




#pragma region SPRITES
//link
extern const u8		sprite_link_walks[2048];
extern const u8		sprite_link_melee_du[3584];
extern const u8		sprite_link_melee_rl[3584];
//walls
extern const u16	img_collisions[1024];
extern const u16	img_walls[3584];//16x192
//ground
extern const u16	img_ground[1792];
//stair
extern const u16	img_stairs[1024];
//objects
extern const u8		sprites_obj[256];
#pragma endregion

#endif