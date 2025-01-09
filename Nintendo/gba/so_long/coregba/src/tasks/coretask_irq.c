/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coretask_irq.c                                                           */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 21/12/2024 18:38:17 by NyTekCFW                                 */
/*   Updated: 21/12/2024 18:38:29 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

static void	_color_loop(s8 *row, s8 *b)
{
	static s8 rrow = 0;
	static s8 column = 0;
	static s8 dir = 0;

	if (!dir)
		++column;
	else
		--column;
	if (column == 16 || column == -1)
		rrow = (rrow + 1) % 13;
	if (column == 16)
	{
		dir = !dir;
		column = 15;
	}
	else if (column == -1)
	{
		dir = !dir;
		column = 0;
	}
	*row = rrow;
	*b = column;
}

static void	irq_color_loop(void)
{
	u16	(*tab)[16] = get_stab_color();
	s8	row = 0;
	s8	vb = 0;

	_color_loop(&row, &vb);
	
	replace_color(208, tab[row][vb]);
}

static void	irq_key_getstatus(void)
{
	s8	i = -1;

	set_keycode_status(KEY_A, key_pressed(KEY_A));
	set_keycode_status(KEY_B, key_pressed(KEY_B));
	set_keycode_status(KEY_L, key_pressed(KEY_L));
	set_keycode_status(KEY_R, key_pressed(KEY_R));
	set_keycode_status(KEY_SELECT, key_pressed(KEY_SELECT));
	set_keycode_status(KEY_START, key_pressed(KEY_START));
	set_keycode_status(KEY_UP, key_pressed(KEY_UP));
	set_keycode_status(KEY_DOWN, key_pressed(KEY_DOWN));
	set_keycode_status(KEY_LEFT, key_pressed(KEY_LEFT));
	set_keycode_status(KEY_RIGHT, key_pressed(KEY_RIGHT));
	while (++i < BUTTON_MAX)
		keynum_execute(i);
}

void	irq_callback(void)
{
	t_callback					*callback = get_callback();
	static unsigned long int	frame = 0;

	if (!(frame % 5))
		irq_color_loop();
	if (!(frame % 15))
		irq_key_getstatus();
	if (callback->irq)
		callback->irq();
	frame = (frame + 1) % 0xFFFFFFFF;
}

void	run_task_irq(void)
{
	irqInit();
	irqEnable(IRQ_VBLANK);
	irqSet(IRQ_VBLANK, irq_callback);
}
