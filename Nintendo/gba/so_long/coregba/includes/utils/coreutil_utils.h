/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coreutil_utils.h                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 20/12/2024 20:08:11 by NyTekCFW                                 */
/*   Updated: 20/12/2024 20:35:35 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREUTIL_UTILS_H
# define COREUTIL_UTILS_H

//processor ram 32 ko
//external ram 256ko
# define IN_IWRAM 		__attribute__ ((section (".iwram")))
# define IN_EWRAM		__attribute__ ((section (".ewram")))
# define IN_COMMON_DATA	__attribute__ ((section ("common_data")))

# include "coreutil_math.h"
# include "coreutil_rand.h"
# include "coreutil_memory.h"
# include "coreutil_string.h"
#endif