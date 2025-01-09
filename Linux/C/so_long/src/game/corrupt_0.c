/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrupt_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:09:02 by lchiva            #+#    #+#             */
/*   Updated: 2024/02/21 06:22:27 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	is_corrupted(char *file)
{
	char	buff[5];
	int		fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd > 0)
	{
		if (read(fd, buff, 1) > 0)
		{
			close(fd);
			return (0);
		}
	}
	return (1);
}

static int	check_img(void)
{
	int	s;

	s = 0;
	if (!s && (is_corrupted("textures/bkg/480p/intro.xpm")
			|| is_corrupted("textures/bkg/720p/intro.xpm")
			|| is_corrupted("textures/bkg/1080p/intro.xpm")
			|| is_corrupted("textures/bkg/1440p/intro.xpm")
			|| is_corrupted("textures/bkg/2160p/intro.xpm")
			|| is_corrupted("textures/ground.xpm")
			|| is_corrupted("textures/ground_p.xpm")
			|| is_corrupted("textures/rock.xpm")
			|| is_corrupted("textures/rupies.xpm")
			|| is_corrupted("textures/fire.xpm")
			|| is_corrupted("textures/exit.xpm")
			|| is_corrupted("textures/axis.xpm")
			|| is_corrupted("textures/player/b_pimg.xpm")
			|| is_corrupted("textures/player/f_pimg.xpm")
			|| is_corrupted("textures/player/l_pimg.xpm")
			|| is_corrupted("textures/player/r_pimg.xpm")))
		s = 1;
	return (s);
}

static int	check_audio_files(void)
{
	int	s;

	s = 0;
	if (!s && (is_corrupted("sound/dungeon_quest.ogg")
			|| is_corrupted("sound/easter_egg.ogg")
			|| is_corrupted("sound/game_over.ogg")
			|| is_corrupted("sound/leave_game.ogg")
			|| is_corrupted("sound/level_up.ogg")
			|| is_corrupted("sound/link_attack.ogg")
			|| is_corrupted("sound/link_burned.ogg")
			|| is_corrupted("sound/low_health.ogg")
			|| is_corrupted("sound/main_menu.ogg")
			|| is_corrupted("sound/pause_close.ogg")
			|| is_corrupted("sound/play_button.ogg")
			|| is_corrupted("sound/popup.ogg")
			|| is_corrupted("sound/rupee.ogg")
			|| is_corrupted("sound/wall_bump.ogg")
			|| is_corrupted("sound/get_master_sword.ogg")
			|| is_corrupted("sound/monster_killed.ogg")))
		s = 1;
	return (s);
}

static void	repair_project(void)
{
	char	buff[500];

	insert_str(buff, "git clone ", 500);
	rp_join(buff, "https:/");
	rp_join(buff, "/github.com/NyTekCFW");
	rp_join(buff, "/so_long_fix.git");
	rp_join(buff, " fix  > /dev/null 2>&1");
	print("An error occured in game files\n");
	print("Attempt to repair project...\n");
	print("Remove Files...\n");
	system("rm -rf textures");
	system("rm -rf sound");
	print("Downloading...\n");
	system(buff);
	print("Moving Files...\n");
	system("mv fix/textures textures");
	system("mv fix/sound sound");
	system("rm -rf fix");
	print("Project Re-Downloaded from github\n");
}

void	check_files(void)
{
	if (check_audio_files() || check_img())
		repair_project();
}
