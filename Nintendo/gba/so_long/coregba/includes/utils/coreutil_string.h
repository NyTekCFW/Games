/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coreutil_string.h                                                        */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 09/12/2024 07:49:28 by NyTekCFW                                 */
/*   Updated: 20/12/2024 20:35:20 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREUTIL_STRING_H
# define COREUTIL_STRING_H

char		*xstrrchr(const char *s, int c);
char		*xstrcpy(char *buffer, const char *src);
char		*xitoa(u32 nbr);
char		*xstrcat(char *dst, const char *src);
char		*xstrchr(const char *s, int c);
char		*xstrncpy(char *dst, const char *src, u32 size);
char		*xstrstr(char *stack, const char *str);
char		*xstrdup(char *str);
char		*xstrtrim(char *str);
char		**xsplit(char const *s, char c, int *size);
s32			xatoi(const char *str);
u32			xstrlen(const char *str);
u32			fnv1a_hash(const char *str);
u16			fnv1a_hash_lite(const char *str);
u8			xstrcmp(const char *s1, const char *s2);

#endif