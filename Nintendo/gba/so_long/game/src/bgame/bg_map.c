/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_map.c                                                                 */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 04/01/2025 03:34:18 by NyTekCFW                                 */
/*   Updated: 04/01/2025 03:34:19 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

char	*get_level_name(u8 index)
{
	switch(index)
	{
		case 0: return ("Level A-1");
		case 1: return ("Level A-2");
		case 2: return ("Level A-3");
		case 3: return ("Level A-4");
		case 4: return ("Level B-1");
		case 5: return ("Level B-2");
		case 6: return ("Level B-3");
		case 7: return ("Level B-4");
		default: return ("N/A");
	}
	return (NULL);
}


/*
void	**alloc_tab(u8 width, u8 height, u32 size1, u32 size2)
{
	u8		i = 0;
	void	**buf = NULL;

	if (xalloc((void **)&buf, size1, height + 1))
	{
		while (i < height)
		{
			if (!xalloc((void **)&buf[i], size2, width + 1))
			{
				while (i)
					xfree((void **)&buf[--i]);
				xfree((void **)&buf);
				return (NULL);
			}
			++i;
		}
	}
	return (buf);
}
*/