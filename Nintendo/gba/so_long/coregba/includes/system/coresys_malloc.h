/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_malloc.h                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 14/12/2024 16:22:33 by NyTekCFW                                 */
/*   Updated: 20/12/2024 19:50:55 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESYS_MALLOC_H
# define CORESYS_MALLOC_H

//ALLOC
void	*mx_malloc(u32 size);
void	*mx_calloc(u32 size);
void	*mx_realloc(void *ptr, u32 size);
void	mx_free(void *ptr);

//MEMORY MAP
u32		mmap_get_total_mem(void);
u32		mmap_get_used_mem(void);
u32		mmap_get_free_mem(void);
u16		mmap_get_total_sector(void);
u16		mmap_get_used_sector(void);
u16		mmap_get_free_sector(void);
u32		mmap_get_reserved_size(void);
u32		mmap_get_start_mem(void);
u32		mmap_get_end_mem(void);
#endif