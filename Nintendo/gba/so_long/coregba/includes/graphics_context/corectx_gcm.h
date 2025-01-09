/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   corectx_gcm.h                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 21/12/2024 17:06:44 by NyTekCFW                                 */
/*   Updated: 21/12/2024 18:09:17 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORECTX_GCM_H
# define CORECTX_GCM_H

u8			gcm_get_active_id(void);
u16			*gcm_get_active_buffer(void);
u16			*gcm_get_draw_buffer(void);
u16			*gcm_get_front_buffer(void);
u16			*gcm_get_back_buffer(void);
u16			gcm_get_buffer_size(void);
void		gcm_init_body(void);
void		gcm_prepare_flip(void);
void		gcm_set_clear_color(u16 clr);
void		gcm_clear_active_buffer(void);
void		gcm_clear_draw_buffer(void);
t_gcm		*get_gcm(void);

#endif