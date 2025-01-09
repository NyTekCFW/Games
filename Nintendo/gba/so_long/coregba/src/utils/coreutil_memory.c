/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coreutil_memory.c                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 09/12/2024 07:42:04 by NyTekCFW                                 */
/*   Updated: 20/12/2024 21:00:24 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

/// @brief memcpy boosted with SMO methode
/// @param dest destination
/// @param src source
/// @param n size
/// @return dest ptr
void	*xmemcpy(void *dest, const void *src, u32 n)
{
	u32	i = 0;

	if (!dest && !src)
		return (NULL);
	CpuCopy(src, dest, n);
	return (dest);
}

/// @brief memset boosted with SMO methode
/// @param s source
/// @param c value that will be converted
///in u8
/// @param n size
/// @return s ptr
void	*xmemset(void *s, u16 c, u32 n)
{
    CpuFill(s, c, n);
	return (s);
}

/// @brief do a calloc, set the result into var and
///return true or false if alloc fail or no
/// @param var (void **)&var
/// @param nmemb sizeof(value type)
/// @param ts size to alloc
/// @return 0 or 1
bool	xalloc(void **var, u32 nmemb, u32 ts)
{
	if (nmemb == 0 || ts == 0)
		return (false);
	if (((ts * nmemb) / nmemb) != ts)
		return (false);
	*var = mx_malloc(nmemb * ts);
	if (!(*var))
		return (false);
	xmemset(*var, 0, nmemb * ts);
	return (true);
}

/// @brief check if the ptr give in param is not null
///if he are defined, it will be free and set at value null
/// @param data (void **)&data
void	xfree(void **data)
{
	if (data && *data)
	{
		mx_free(*data);
		*data = NULL;
	}
}
