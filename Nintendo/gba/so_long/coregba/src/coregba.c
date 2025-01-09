/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   mxgba.c                                                                  */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 10/12/2024 14:54:20 by NyTekCFW                                 */
/*   Updated: 10/12/2024 14:54:23 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coregba.h"

/// @brief Global library
/// @return ptr of the static
t_core	*get_core(void)
{
	static t_core	lib_coregba = {0};

	return (&lib_coregba);
}

t_callback	*get_callback(void)
{
	return (&get_core()->callback);
}

t_engine	*get_engine(void)
{
	return (&get_core()->engine);
}

t_texture	*get_texture(void)
{
	return (&get_core()->texture);
}

t_cp	*get_color_picker(void)
{
	return (&get_core()->color_picker);
}
