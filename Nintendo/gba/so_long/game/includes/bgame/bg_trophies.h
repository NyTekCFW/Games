/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_trophies.h                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:15:25 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_TROPHIES_H
# define BG_TROPHIES_H

enum e_trophies
{
	TROPHY_HUNTER		= 0,
	TROPHY_COLLECTOR,
	TROPHY_BEGINNER,
	TROPHY_EXPERT,
	TROPHY_FINISHER,
	TROPHY_MAKER,
	TROPHY_NEW_START,
	TROPHY_EXPLORER,
	TROPHY_STYLIST,
	TROPHY_ENDGAME,
	TROPHY_MAX
};

typedef struct trophies_s
{
	bool	unlocked;
	u8		rarity;
}ALIGN(4)	t_trophy;

char	*get_trophy_name(u8 index);
bool	try_unlock_trophy(u8 index, bool (*check_func)(void *), void *param);
#endif