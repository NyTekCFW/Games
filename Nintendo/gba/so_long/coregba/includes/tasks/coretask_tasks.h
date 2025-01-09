/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coretask_tasks.h                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 21/12/2024 19:35:05 by NyTekCFW                                 */
/*   Updated: 21/12/2024 19:35:06 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORETASK_TASKS_H
# define CORETASK_TASKS_H

typedef struct engine_s
{
	u8		initialised;
	u8		running;
	u8		max_fps;
	u32		fps_out;
	float	timescale;
}	t_engine;

typedef struct callbacks_s
{
	void	(*scripts)(void);//function executed before rendering to update each data/value
	void	(*rendering)(void);//function that will draw the game
	void	(*keys)(void);//function called at start to init each key function
	void	(*irq)(void);//function called at each irq vblank
	void	(*reg_sprites)(void);//function to initialise all sprites
	void	(*initial_call)(void);//function called before game start rendering
}	t_callback;

void	run_task_irq(void);
void	run_task_rendering(t_engine *engine, t_callback *callback);
void	run_tasks(u8 scaled, u16 clear_color, u8 max_fps, float timescale, u32 rand_seed);

#endif