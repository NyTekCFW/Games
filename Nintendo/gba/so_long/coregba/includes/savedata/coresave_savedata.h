/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresave_savedata.h                                                      */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 31/12/2024 17:50:54 by NyTekCFW                                 */
/*   Updated: 31/12/2024 17:50:59 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESAVE_SAVEDATA_H
# define CORESAVE_SAVEDATA_H

enum	e_eeprom_status
{
	EEPROM_WAITING	= 0,
	EEPROM_WRITING,
	EEPROM_READING
};

# include "coresave_eeprom.h"

#endif