/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coretask_tasks.h                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/01/2025 00:24:45 by NyTekCFW                                 */
/*   Updated: 16/01/2025 03:12:14 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORETASK_TASKS_H
# define CORETASK_TASKS_H

typedef struct engine_s
{
	u8		initialised;
	u8		running;
	u8		max_fps;
	u8		backup_fps;
	u8		key_input_speed;//speed of key detection
	u32		fps_out;
	float	timescale;
}ALIGNED(4)	t_engine;

typedef struct callbacks_s
{
	void	(*scripts)(void);//function executed before rendering to update each data/value
	void	(*rendering)(void);//function that will draw the game
	void	(*keys)(void);//function called at start to init each key function
	void	(*irq)(void);//function called at each irq vblank
	void	(*reg_sprites)(void);//function to initialise all sprites
	void	(*reg_sfx)(void);//function to initialise all sfx
	void	(*initial_call)(void);//function called before game start rendering
}ALIGNED(4)	t_callback;

void	run_task_irq(void);
void	run_task_rendering(t_engine *engine, t_callback *callback);
void	run_tasks(u8 scaled, u16 clear_color, u8 max_fps, float timescale, u32 rand_seed, enum e_sfx_hz hz);

#endif