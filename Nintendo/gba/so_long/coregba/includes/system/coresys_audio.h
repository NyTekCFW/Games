/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_audio.h                                                          */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 11/01/2025 20:10:16 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:11:30 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESYS_AUDIO_H
# define CORESYS_AUDIO_H

#define REG_FIFO_A				(*(volatile uint32_t *)0x40000A0)
#define REG_FIFO_B				(*(volatile uint32_t *)0x40000A4)
#define REG_SOUNDCNT_H			(*(volatile uint16_t *)0x4000082)
#define REG_SOUNDCNT_X			(*(volatile uint16_t *)0x4000084)
#define REG_SOUNDCNT_L			(*(volatile uint16_t *)0x4000080)

#define SOUND_A_RIGHT_CHANNEL	0x0100
#define SOUND_A_LEFT_CHANNEL	0x0200
#define SOUND_A_FIFO_RESET		0x0800
#define SOUND_B_RIGHT_CHANNEL	0x1000
#define SOUND_B_LEFT_CHANNEL	0x2000
#define SOUND_B_FIFO_RESET		0x8000
#define SOUND_MASTER_ENABLE		0x0080

#define SOUND_A_VOL_50			0x0000  // 50% Volume pour FIFO A
#define SOUND_A_VOL_100			0x0008  // 100% Volume pour FIFO A
#define SOUND_B_VOL_50			0x0000  // 50% Volume pour FIFO B
#define SOUND_B_VOL_100			0x0004  // 100% Volume pour FIFO B

enum	e_sfx_hz
{
	SFX_4000_HZ		= 0,
	SFX_8000_HZ,
	SFX_11025_HZ,
	SFX_16000_HZ,
	SFX_22050_HZ,
	SFX_NONE_HZ
};

typedef struct sfx_s
{
	u32				h_name;
	u32				len;
	u16				pos;
	bool			loop_sfx;
	const s8		*raw;
	struct sfx_s	*next;
}ALIGNED(8)	t_sfx;

typedef struct audio_s
{
	t_sfx	sfx;
	u16		sfx_count;
	u16		sfx_hz;
}ALIGNED(8)	t_audio;

void	set_audio_hz(enum e_sfx_hz hz);
void	purge_sfx(void);
void	register_sfx(const char *name, const s8 *sfx_raw_data, u32 len, bool loop_sfx);
t_sfx	*get_sfx(const char *name);
#endif