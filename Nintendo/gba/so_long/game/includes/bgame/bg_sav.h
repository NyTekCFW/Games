/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   bg_sav.h                                                                 */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:15:08 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef BG_SAV_H
# define BG_SAV_H

enum e_skins
{
	SKIN_JACKET	= 0,
	SKIN_BODY,
	SKIN_EQUIPMENTS,
	SKIN_MAX
};

typedef struct sav_user_s
{
	u32		ld[STATS_LD_MAX];
	u16		skins[SKIN_MAX];
	bool	trophies[TROPHY_MAX];
}ALIGNED(4)	t_sav_user;

typedef struct sav_s
{
	t_gameinfo	header;//header for game version detection
	t_sav_user	user_data;
}ALIGNED(4)	t_sav;

void	build_savedata(void);
void	load_savedata(void);
#endif