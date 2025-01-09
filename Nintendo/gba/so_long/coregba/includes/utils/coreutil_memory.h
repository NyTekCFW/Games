/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coreutil_memory.h                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 09/12/2024 07:49:40 by NyTekCFW                                 */
/*   Updated: 20/12/2024 20:35:28 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREUTIL_MEMORY_H
# define COREUTIL_MEMORY_H

void	*xmemcpy(void *dest, const void *src, u32 n);
void	*xmemset(void *s, u16 c, u32 n);
void	xfree(void **data);
bool	xalloc(void **var, u32 nmemb, u32 ts);

#endif