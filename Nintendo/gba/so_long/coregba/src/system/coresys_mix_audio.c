/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_mix_audio.c                                                      */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 13/01/2025 10:50:55 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:14:13 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

/*
#define MAX_CHANNELS	4
#define MIX_BUFFER_SIZE	140

typedef struct mix_channel_s
{
	const s8	*raw;
	u32			len;
	u32			pos;
	u8			volume;
	bool		used;
	bool		loop_sfx;
	bool		paused;
}ALIGNED(4)	t_mix_channel;

t_mix_channel	mix_channels[MAX_CHANNELS];
s8				mix_buffer[MIX_BUFFER_SIZE];

static void	reset_channel(u8 u)
{
	mix_channels[u].used = false;
	mix_channels[u].loop_sfx = false;
	mix_channels[u].raw = NULL;
	mix_channels[u].len = 0;
	mix_channels[u].volume = 0;
	mix_channels[u].pos = 0;
	mix_channels[u].paused = false;
}

static void	add_to_channel(t_sfx *sfx)
{
	u8	u = 0;
	while (u < MAX_CHANNELS)
	{
		if (!mix_channels[u].used)
		{
			mix_channels[u].raw = sfx->raw;
			mix_channels[u].len = sfx->len;
			mix_channels[u].volume = sfx->volume;
			mix_channels[u].pos = 0;
			mix_channels[u].used = true;
			mix_channels[u].loop_sfx = sfx->loop_sfx;
			mix_channels[u].paused = false;
			break ;
		}
		++u;
	}
}

void	play_mix_audio(void)
{
	t_audio			*audio = get_audio();
	s32				data = 0;
	u32				i = 0;
	u8				u = 0;
	u8				active = 0;

	if (!audio || audio->sfx_hz == 0)
		return ;

	for (i = 0; i < MIX_BUFFER_SIZE; ++i)
	{
		data = 0;
		for (u = 0; u < MAX_CHANNELS; ++u)
		{
			if (mix_channels[u].used && mix_channels[u].raw && !mix_channels[u].paused)
			{
				if (mix_channels[u].pos >= mix_channels[u].len)
				{
					if (!mix_channels[u].loop_sfx)
						reset_channel(u);
					else
						mix_channels[u].pos = 0;
				}
				else
				{
					data += (mix_channels[u].raw[mix_channels[u].pos] * mix_channels[u].volume) >> 8;
					++mix_channels[u].pos;
					++active;
				}
			}
		}
		if (data > 127)
			data = 127;
		else if (data < -128)
			data = -128;
		mix_buffer[i] = (int8_t)data;
	}
	REG_DMA1CNT = 0;
	if (active > 0)
	{
		REG_DMA1SAD = (uint32_t)mix_buffer;
		REG_DMA1DAD = (uint32_t)&REG_FIFO_A;
		REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SYNC_TO_TIMER | DMA_ENABLE;
	}
}

void	start_audio(void)
{
	REG_DMA1CNT = 0;
	REG_DMA1SAD = (uint32_t)mix_buffer;
	REG_DMA1DAD = (uint32_t)&REG_FIFO_A;
	REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SYNC_TO_TIMER | DMA_ENABLE;
	REG_TM0D = get_audio()->sfx_hz;
	REG_TM0CNT = TIMER_ENABLE | TIMER_FREQ_1;
}


void	play_sfx(const char *name)
{
	t_sfx *sfx = get_sfx(name);

	if (sfx && sfx->raw && sfx->len > 0)
		add_to_channel(sfx);
}

void	stop_sfx(const char *name)
{
	u8		u = 0;
	t_sfx	*sfx = get_sfx(name);

	if (sfx && sfx->raw && sfx->len > 0)
	{
		while (u < MAX_CHANNELS)
		{
			if (mix_channels[u].used && mix_channels[u].raw == sfx->raw)
				reset_channel(u);
			++u;
		}
	}
}

void	stop_all_sfx(void)
{
	u8	u = 0;

	REG_DMA1CNT = 0;
	while  (u < MAX_CHANNELS)
	{
		reset_channel(u);
		++u;
	}
	REG_SOUNDCNT_H = SOUND_A_RIGHT_CHANNEL | SOUND_A_LEFT_CHANNEL | SOUND_A_FIFO_RESET;
	REG_SOUNDCNT_X = SOUND_MASTER_ENABLE;
}

void	pause_sfx(const char *name)
{
	u8		u = 0;
	t_sfx	*sfx = get_sfx(name);

	if (sfx && sfx->raw && sfx->len > 0)
	{
		while (u < MAX_CHANNELS)
		{
			if (mix_channels[u].used && mix_channels[u].raw == sfx->raw)
				mix_channels[u].paused = true;
			++u;
		}
	}
}

void	resume_sfx(const char *name)
{
	u8		u = 0;
	t_sfx	*sfx = get_sfx(name);

	if (sfx && sfx->raw && sfx->len > 0)
	{
		while (u < MAX_CHANNELS)
		{
			if (mix_channels[u].used && mix_channels[u].raw == sfx->raw)
				mix_channels[u].paused = false;
			++u;
		}
	}
}

void	pause_all_sfx(void)
{
	u8	u = 0;

	while  (u < MAX_CHANNELS)
	{
		if (mix_channels[u].used)
			mix_channels[u].paused = true;
		++u;
	}
}

void	resume_all_sfx(void)
{
	u8	u = 0;

	while  (u < MAX_CHANNELS)
	{
		if (mix_channels[u].used)
			mix_channels[u].paused = false;
		++u;
	}
}
*/

#define CYCLES_PER_BLANK 280806

typedef struct mix_channel_s
{
	const s8	*raw;
	u32			len;
	u32			pos;
	u32			def_pos;
	bool		used;
	bool		loop_sfx;
	bool		paused;
}ALIGNED(8)	t_mix_channel;

ALIGNED(8) t_mix_channel	mix_channels[2];

static void	play_sound(const s8 *raw, char channel)
{
	if (channel == 'A')
	{
		REG_TM0CNT = 0;
		REG_DMA1CNT = 0;
		REG_SOUNDCNT_H |= SOUND_A_RIGHT_CHANNEL | SOUND_A_LEFT_CHANNEL | SOUND_A_FIFO_RESET;
	}
	else if (channel == 'B')
	{
		REG_TM1CNT = 0;
		REG_DMA2CNT = 0;
		REG_SOUNDCNT_H |= SOUND_B_RIGHT_CHANNEL | SOUND_B_LEFT_CHANNEL | SOUND_B_FIFO_RESET;
	}
	if (!raw)
		return ;
	REG_SOUNDCNT_X = SOUND_MASTER_ENABLE;
	if (channel == 'A')
	{
		REG_DMA1SAD = (unsigned int)raw;
		REG_DMA1DAD = (unsigned int)&REG_FIFO_A;
		REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SYNC_TO_TIMER | DMA_ENABLE;
		REG_TM0D = get_audio()->sfx_hz;
		REG_TM0CNT = TIMER_ENABLE | TIMER_FREQ_1;
	}
	else if (channel == 'B')
	{
		REG_DMA2SAD = (unsigned int)raw;
		REG_DMA2DAD = (unsigned int)&REG_FIFO_B;
		REG_DMA2CNT = DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SYNC_TO_TIMER | DMA_ENABLE;
		REG_TM1D = get_audio()->sfx_hz;
		REG_TM1CNT = TIMER_ENABLE | TIMER_FREQ_1;
	}
}

static void	reset_channel(u8 u)
{
	mix_channels[u].used = false;
	mix_channels[u].loop_sfx = false;
	mix_channels[u].raw = NULL;
	mix_channels[u].len = 0;
	mix_channels[u].def_pos = 0;
	mix_channels[u].pos = 0;
	mix_channels[u].paused = false;
	play_sound(NULL, (u == 0) ? 'A' : 'B');
}


#include "math.h"

static void	add_to_channel(t_sfx *sfx)
{
	u8	u = 0;

	while (u < 2)
	{
		if (!mix_channels[u].used)
		{
			mix_channels[u].raw = sfx->raw;
			mix_channels[u].len = sfx->len;
			mix_channels[u].pos = sfx->pos;
			mix_channels[u].def_pos = sfx->pos;
			mix_channels[u].used = true;
			mix_channels[u].loop_sfx = sfx->loop_sfx;
			mix_channels[u].paused = false;
			if (!u)
				*(vu32 *)0x40001C0 = mix_channels[u].pos;
			else
				*(vu32 *)0x40001C4 = mix_channels[u].pos;
			play_sound(mix_channels[u].raw, (u == 0) ? 'A' : 'B');
			break ;
		}
		++u;
	}
}

void	play_sfx(const char *name)
{
	t_sfx *sfx = get_sfx(name);

	if (sfx && sfx->raw && sfx->len > 0)
		add_to_channel(sfx);
}

void	stop_sfx(const char *name)
{
	u8		u = 0;
	t_sfx	*sfx = get_sfx(name);

	if (sfx && sfx->raw && sfx->len > 0)
	{
		while (u < 2)
		{
			if (mix_channels[u].used && mix_channels[u].raw == sfx->raw)
				reset_channel(u);
			++u;
		}
	}
}

void	audio_vsync(void)
{
	u8	u = 0;

	while (u < 2)
	{
		if (mix_channels[u].used && mix_channels[u].raw)
		{
			if (!mix_channels[u].pos)
			{
				if (mix_channels[u].loop_sfx)
				{
					mix_channels[u].pos = mix_channels[u].def_pos;
					play_sound(mix_channels[u].raw, (u == 0) ? 'A' : 'B');
				}
				else
					reset_channel(u);
			}
			else
				--mix_channels[u].pos;
		}
		++u;
	}
}
