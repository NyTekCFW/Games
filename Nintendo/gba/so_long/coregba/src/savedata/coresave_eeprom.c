/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresave_eeprom.c                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 30/12/2024 18:06:19 by NyTekCFW                                 */
/*   Updated: 30/12/2024 18:06:41 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

static u8	*get_eeprom_status(void)
{
	static u8	_eeprom = 0;

	return (&_eeprom);
}

static void	eeprom_write(u16 address, const void *data, u16 size)
{
	const u8	*buffer = (const u8 *)data;
	u16			i = 0;

	for (i = 0; i < size; ++i)
	{
		while (REG_WAITCNT & 0x01)
			;
		*(vu8 *)(0x0E000000 + address + i) = buffer[i];
	}
}

static void	eeprom_read(u16 address, void *data, u16 size)
{
	u8	*buffer = (u8 *)data;
	u16	i = 0;

	for (i = 0; i < size; i++)
	{
		while (REG_WAITCNT & 0x01)
			;
		buffer[i] = *(vu8 *)(0x0E000000 + ((address + i)));
	}
}

u8	eeprom_status(void)
{
	return (*get_eeprom_status());
}

bool	save_to_eeprom(const void *data, u8 slot, u32 size)
{
	u8	*status = get_eeprom_status();

	if (*status == EEPROM_WAITING)
	{
		*status = EEPROM_READING;
		eeprom_write((slot * size), data, size);
		*status = EEPROM_WAITING;
		return (true);
	}
	return (false);
}

bool	load_from_eeprom(void *data, u8 slot, u32 size)
{
	u8	*status = get_eeprom_status();

	if (*status == EEPROM_WAITING)
	{
		*status = EEPROM_WRITING;
		eeprom_read((slot * size), data, size);
		*status = EEPROM_WAITING;
		return (true);
	}
	return (false);
}
