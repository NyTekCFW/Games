/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_cpu.h                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 20/12/2024 17:40:01 by NyTekCFW                                 */
/*   Updated: 20/12/2024 17:40:02 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESYS_CPU_H
# define CORESYS_CPU_H

void	CpuFill32(vu32 v, void *dst, u32 size);
void	CpuFill16(vu16 v, void *dst, u32 size);
void	CpuFastFill(vu32 v, void* dst, u32 size);
void	CpuCopy32(const void *src, void *dest, u32 size);
void	CpuCopy16(const void *src, void *dest, u32 size);
void	CpuFastCopy(const void *src, void *dest, u32 size);
void	CpuCopy(const void *src, void *dest, u32 size);
void	CpuFill(void *dst, vu32 v, u32 size);

#endif