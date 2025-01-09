/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_color.c                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 12/12/2024 15:04:10 by NyTekCFW                                 */
/*   Updated: 18/12/2024 17:59:04 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

inline u16	rgb_to_15bit(u8 r, u8 g, u8 b)
{
	return ((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10));
}

inline void	rgb15_to_rgb(u16 rgb15, u8 *r, u8 *g, u8 *b)
{
	*r = ((rgb15 & 0x1F) << 3) | ((rgb15 & 0x1F) >> 2);
	*g = (((rgb15 >> 5) & 0x1F) << 3) | (((rgb15 >> 5) & 0x1F) >> 2);
	*b = (((rgb15 >> 10) & 0x1F) << 3) | (((rgb15 >> 10) & 0x1F) >> 2);
}

/// @brief return the static tab of color (index 0 - 207)
/// @return //tab[ROW_COLOR_TYPE (0->13)][Brightness intensity (0->15)]
inline u16	(*get_stab_color(void))[16]
{
    return ((u16 (*)[16])0x05000000);
}

u16	get_color_index(u16 color)
{
	u16	j = 0;
	u16	*ptr = get_palette();

	for (j = 0; j < 256; ++j)
	{
		if (ptr[j] == color)
			return (j);
	}
	return (0xFFFF);
}

void	replace_color(u16 index, u16 color)
{
	u16	*ptr = get_palette();

	if (index < 256)
		ptr[index] = color;
}


u16	get_color_at(u16 index)
{
	u16	*ptr = get_palette();

	if (index < 256)
		return (ptr[index]);
	return (0);
}

inline u16	*get_palette(void)
{
	return ((u16 *)0x05000000);
}

void	set_palette(u16 *pal)
{
	static u16	*cur = NULL;

	if (pal && cur != pal)
	{
		CpuFastCopy(pal, (u16 *)0x05000000, 512);
		cur = pal;
	}
}
