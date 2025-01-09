/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresave_eeprom.h                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 30/12/2024 21:38:59 by NyTekCFW                                 */
/*   Updated: 30/12/2024 21:39:12 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESAVE_EEPROM_H
# define CORESAVE_EEPROM_H

u8		eeprom_status(void);
void	save_to_eeprom(const void *data, u8 slot, u32 size);
void	load_from_eeprom(void *data, u8 slot, u32 size);

#endif