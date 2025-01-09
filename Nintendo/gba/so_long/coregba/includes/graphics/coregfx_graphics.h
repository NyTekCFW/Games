/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coregfx_global.h                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 20/12/2024 15:08:18 by NyTekCFW                                 */
/*   Updated: 20/12/2024 15:08:22 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREGFX_GLOBAL_H
# define COREGFX_GLOBAL_H

enum e_row_color
{
	CLR_ROW_RED	= 0,
	CLR_ROW_ORANGE,
	CLR_ROW_YELLOW,
	CLR_ROW_LIGHTGREEN,
	CLR_ROW_GREEN,
	CLR_ROW_LIGHTCYAN,
	CLR_ROW_CYAN,
	CLR_ROW_LIGHTBLUE,
	CLR_ROW_BLUE,
	CLR_ROW_LIGHTPURPLE,
	CLR_ROW_PURPLE,
	CLR_ROW_LIGHTRED,
	CLR_ROW_GREY,
	CLR_ROW_MAX
};

# define STR_BUTTON_A			"\x0B"
# define STR_BUTTON_B			"\x0C"
# define STR_DPAD_UP			"\x0D"
# define STR_DPAD_DOWN			"\x0E"
# define STR_DPAD_LEFT			"\x0F"
# define STR_DPAD_RIGHT			"\x10"
# define STR_DPAD_LEFT_RIGHT	"\x11"
# define STR_DPAD_UP_DOWN		"\x12"
# define STR_DPAD_NONE			"\x13"
# define STR_BUTTON_L			"\x14"
# define STR_BUTTON_R			"\x15"
# define STR_BUTTON_START		"\x16"
# define STR_BUTTON_SELECT		"\x17"
# define STR_ICON_UNCHECKED		"\x18"
# define STR_ICON_CHECKED		"\x19"
# define STR_ICON_LOCKED_TROPHY	"\x1A"
# define STR_ICON_BRONZE_TROPHY	"\x1B"
# define STR_ICON_SILVER_TROPHY	"\x1C"
# define STR_ICON_GOLD_TROPHY	"\x1D"


# include "coregfx_glyphs.h"
# include "coregfx_sprites.h"
# include "coregfx_sprites_pal.h"
# include "coregfx_basics.h"
# include "coregfx_color.h"
# include "coregfx_text.h"
# include "coregfx_shapes.h"
# include "coregfx_colorpicker.h"

#endif