/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savedata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:50:43 by lchiva            #+#    #+#             */
/*   Updated: 2024/01/24 05:31:34 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	error_save(int ce)
{
	char	*error;

	error = "Error code not defined\n";
	if (ce == 0)
		error = "Error: invalid size!\n";
	if (ce == 1)
		error = "Error: malloc fail!\n";
	if (ce == 2)
		error = "Error: fail during save export!\n";
	if (ce == 3)
		error = "Error: fail opening save!\n";
	print(error);
}

static void	*encrypt(void *mem, size_t size)
{
	unsigned char	*buffer;
	unsigned char	*huffer;

	if (size < 1)
		return (error_save(0), (void *)0);
	buffer = (unsigned char *)malloc(size);
	if (!buffer)
		return (error_save(1), (void *)0);
	huffer = sl_memcpy(buffer, mem, size);
	while (size--)
	{
		*huffer = *huffer ^ 0x5F;
		huffer++;
	}
	return (buffer);
}

int	read_save(t_core *core)
{
	int			i;
	int			fd;
	void		*copy;

	fd = open(PATH_SAVE, O_RDONLY, 0777);
	if (fd > 0)
	{
		sl_memset(get_account(core), 0, sizeof(t_account));
		i = read(fd, get_account(core), sizeof(t_account));
		if (i != sizeof(t_account))
		{
			sl_memset(get_account(core), 0, sizeof(t_account));
			return (error_save(0), 0);
		}
		copy = encrypt(get_account(core), sizeof(t_account));
		if (copy)
		{
			sl_memcpy(get_account(core), copy, sizeof(t_account));
			print("The save as been loaded");
			return (free(copy), copy = NULL, 1);
		}
		else
			return (error_save(1), 0);
	}
	return (error_save(3), 0);
}

int	make_save(t_core *core)
{
	void		*copy;
	int			fd;

	fd = open(PATH_SAVE, 01101, 0777);
	if (fd > 0)
	{
		copy = encrypt(get_account(core), sizeof(t_account));
		if (copy)
		{
			write(fd, copy, sizeof(t_account));
			close(fd);
			print("The save has been created");
			return (free(copy), copy = NULL, 1);
		}
		else
			return (error_save(1), 0);
	}
	return (error_save(2), 0);
}
