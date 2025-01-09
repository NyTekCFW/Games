/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coreutil_string.c                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 09/12/2024 07:49:04 by NyTekCFW                                 */
/*   Updated: 20/12/2024 21:00:11 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

/// @brief return a unsigned int value
///that correspond at the hash of a string,
///FNV1A hash is used for this, cause its
///simple to integrate and work correctly
/// @param str string to hash
/// @return 
u32	fnv1a_hash(const char *str)
{
	u32	hash;

	hash = 2166136261u;
	while (*str)
	{
		hash ^= (u8)*str;
		hash *= 16777619u;
		++str;
	}
	return (hash);
}

u16	fnv1a_hash_lite(const char *str)
{
	u16 hash;

	hash = 0x811u;
	while (*str)
	{
		hash ^= (u8)*str;
		hash *= 0x1003u;
		++str;
	}
	return (hash);
}


/// @brief compare 2 string
/// @param s1 string 1
/// @param s2 string 2
/// @return 
u8	xstrcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1++ == *s2++)
		;
	return ((u8)*s1 - (u8)*s2);
}

/// @brief get len of a string
/// @param str string
/// @return 
u32	xstrlen(const char *str)
{
	u32	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

/// @brief strcpy boosted with SMO method
/// @param buffer dest e.g : char buffer[32];
/// @param src source e.g : "hi guys!"
/// @return 
char	*xstrcpy(char *buffer, const char *src)
{
	u32	i = 0;

	i = xstrlen(src);
	CpuCopy(src, buffer, i);
	buffer[i] = '\0';
	return (buffer);
}

char	*xstrcat(char *dst, const char *src)
{
	u32		len = xstrlen(dst);
	char	*begin = dst;

	xstrcpy(&dst[len], src);
	return (begin);
}

/// @brief get the last value (c) occurance
///and return his position with a char *
/// @param s string
/// @param c value e.g : '/'
/// @return 
char	*xstrrchr(const char *s, int c)
{
	char		uc;
	const char	*last_occurrence;

	uc = (char)c;
	last_occurrence = NULL;
	while (*s != '\0')
	{
		if (*s == uc)
			last_occurrence = s;
		++s;
	}
	if (last_occurrence != NULL)
		return ((char *)last_occurrence);
	if (*s == uc)
		return ((char *)s);
	return (NULL);
}

char	*xstrchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (s && *s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*xstrncpy(char *dst, const char *src, u32 size)
{
	u32	i;

	if (!dst || !src || size == 0)
		return (NULL);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*xstrstr(char *stack, const char *str)
{
	u32	i;
	u32	j;
	u32	len;

	if (!*str)
		return ((char *)stack);
	len = 0;
	i = 0;
	while (str[len])
		len++;
	while (stack[i])
	{
		j = 0;
		while (str[j] && stack[i + j]
			&& stack[i + j] == str[j])
			j++;
		if (j == len)
			return (&stack[i]);
		i++;
	}
	return (NULL);
}

char	*xstrdup(char *str)
{
	char	*buffer;
	u32	len;

	if (!str || !(*str))
		return (NULL);
	buffer = NULL;
	len = xstrlen(str);
	if (xalloc((void **)&buffer, sizeof(char), len + 1))
	{
		xmemcpy(buffer, str, len);
		buffer[len] = 0;
	}
	return (buffer);
}

char	*xstrtrim(char *str)
{
	char	*b;
	u32	s;
	u32	e;
	u32	i;

	if (!str || !(*str))
		return (NULL);
	s = 0;
	i = 0;
	e = xstrlen(str) - 1;
	b = NULL;
	while (str[s] && (str[s] == ' ' || str[s] == '\t'))
		s++;
	while (e > s && (str[e] == ' ' || str[e] == '\t'))
		e--;
	if (e >= s && xalloc((void **)&b, sizeof(char), (e - s) + 2))
	{
		while (s <= e)
			b[i++] = str[s++];
		b[i] = 0;
	}
	return (b);
}

static u32	_get_xitoa_len(u32 n)
{
	u32	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*_xitoa(u32 *nbr, char *res, u32 *len)
{
	res[*len] = '\0';
	if (*nbr == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (*nbr < 0)
	{
		res[0] = '-';
		*nbr *= -1;
	}
	while (*nbr)
	{
		res[--(*len)] = *nbr % 10 + '0';
		*nbr /= 10;
	}
	return (res);
}

char	*xitoa(u32 nbr)
{
	u32			len;
	char		*result;

	result = NULL;
	if ((int)nbr == -2147483648L)
	{
		if (xalloc((void **)&result, sizeof(char), 12))
		{
			xstrcpy(result, "-2147483648");
			return (result);
		}
		return (NULL);
	}
	len = _get_xitoa_len(nbr);
	if (xalloc((void **)&result, sizeof(char), len + 1))
	{
		result = _xitoa(&nbr, result, &len);
		return (result);
	}
	return (NULL);
}

static int	xcountword(char const *s, char c)
{
	int	count;

	count = 0;
	while (s && *s)
	{
		if (*s != c)
		{
			++count;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (count);
}

static int	xword_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != c)
		++i;
	return (i);
}

int	_split(const char *s, char **buffer, char c, int word)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (*s && i < word + 1)
	{
		if (*s != c)
		{
			o = xword_len(s, c);
			if (!xalloc((void **)&buffer[i], sizeof(char), o + 1))
			{
				o = 0;
				while (o < i)
					xfree((void **)&buffer[o++]);
				xfree((void **)&buffer);
				return (0);
			}
			xmemcpy(buffer[i++], s, sizeof(char) * o);
			s += o;
			continue ;
		}
		++s;
	}
	return (i);
}

char	**xsplit(char const *s, char c, int *size)
{
	char	**buffer;
	int		word;

	if (!s || !size)
		return (NULL);
	*size = 0;
	buffer = NULL;
	word = xcountword(s, c);
	if (!word)
		return (NULL);
	if (xalloc((void **)&buffer, sizeof(char *), word + 1))
		*size = _split(s, buffer, c, word);
	if (*size == 0)
		return (NULL);
	return (buffer);
}

s32	xatoi(const char *str)
{
	u32	i;
	u32	mp;
	u32	res;

	i = 0;
	mp = 1;
	res = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && i < 3)
		{
			res = res * 10 + str[i] - '0';
			++i;
		}
		else
			return (-1);
	}
	return (res * mp);
}
