/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coreutil_va.c                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 11/01/2025 01:59:43 by NyTekCFW                                 */
/*   Updated: 11/01/2025 01:59:44 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"
# include <stdio.h>
# include <stdarg.h>
/*
int	_snprintf(char *buf, int size, const char *fmt, ...)
{

}
*/
char	*va_alloc(const char* fmt, ...)
{
	va_list	ap;
	int		size	= 0;
	char	*buffer = NULL;

	if (!fmt)
		return (NULL);
	va_start(ap, fmt);
	size = vsnprintf(NULL, 0, fmt, ap) + 1;
	size = (size + 3) & ~3;
	va_end(ap);
	if (xalloc((void **)&buffer, size, sizeof(char)))
	{
		xmemset(buffer, 0, size);
		va_start(ap, fmt);
		vsnprintf(buffer, size, fmt, ap);
		va_end(ap);
	}
	return (buffer);
}

char	*va_f_alloc(float data, u32 p)
{
	int		count = 10;
	int		cast = 0;
	int		begin = 0;
	char	*buffer	= NULL;

	if (p == 0)
		return (xitoa((int)data));
	if (xalloc((void **)&buffer, sizeof(char), 30))
	{
		if (p < 9)
		{
			p -= 1;
			while (p > 0)
			{
				count *= 10;
				p -= 1;
			}
			if (data < 0)
			{
				buffer[0] = '-';
				data *= -1;
				begin++;
			}
			cast = (int)(data * count);
			snprintf(&buffer[begin], 30 - begin, "%i.%0*u", cast / count, p, cast % count);
		}
		else
			buffer[0] = 'f';
	}
	return (buffer);
}