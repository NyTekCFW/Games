/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_cpu.c                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 20/12/2024 19:43:16 by NyTekCFW                                 */
/*   Updated: 20/12/2024 19:43:17 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

#pragma region CPU_FILL
void	CpuFill32(vu32 v, void *dst, u32 size)
{
	CpuSet((void *)&v, dst, 83886080U | ((size) / (4) & 0x1FFFFF));
}

void	CpuFill16(vu16 v, void *dst, u32 size)
{
	CpuSet((void *)&v, dst, 16777216U | ((size) / (2) & 0x1FFFFF));
}

void	CpuFastFill(vu32 v, void* dst, u32 size)
{
	CpuFastSet((void *)&v, dst, CPU_FAST_SET_SRC_FIXED | ((size / 4) & 0x1FFFFF));
}

void	CpuFill(void *dst, vu32 v, u32 size)
{
	uintptr_t	ptr = (uintptr_t)dst;
	u32			i = 0;

	if (!size)
		return ;
	if ((ptr % 2))
	{
		while (i < size)
		{
			*(vu8*)(ptr + i) = (u8)v;
			++i;
		}
		return ;
	}
	if (ptr % 4 && !(ptr % 2))
	{
		CpuFill16(v, dst, size);
		return ;
	}
	if ((size % 2))
	{
		if (size > 1)
			CpuFill16(v, dst, size - 1);
		return (*(volatile u8*)((uintptr_t)dst + (size - 1)) = (u8)v, (void)0);
	}
	if (!(size % 4))
	{
		if (v < 0x10000)
			v = ((v) << 16) | (v);
	}
	if (!(size % 32))
		return (CpuFastFill(v, dst, size), (void)0);
	if (!(size % 4))
		return (CpuFill32(v, dst, size), (void)0);
	if (v < 0x10000)
		return (CpuFill16(v, dst, size), (void)0);
}
#pragma endregion


#pragma region CPU_COPY
void	CpuCopy32(const void *src, void *dest, u32 size)
{
	CpuSet(src, dest, CPU_SET_32BIT | ((size) / (4) & 0x1FFFFF));
}

void	CpuCopy16(const void *src, void *dest, u32 size)
{
	CpuSet(src, dest, CPU_SET_16BIT | ((size) / (2) & 0x1FFFFF));
}

void	CpuFastCopy(const void *src, void *dest, u32 size)
{
	CpuFastSet(src, dest, (size / 4) & 0x1FFFFF);
}

void	CpuCopy(const void *src, void *dest, u32 size)
{
	uintptr_t	ptr_s = (uintptr_t)src;
	uintptr_t	ptr_d = (uintptr_t)dest;
	u32			i = 0;

	if (!size)
		return ;
	if ((ptr_d % 2) || (ptr_s % 2))
	{
		while (i < size)
		{
			*(vu8*)(ptr_d + i) = *(vu8*)(ptr_s + i);
			++i;
		}
		return ;
	}
	if ((size % 2))
	{
		if (size > 1)
			CpuCopy16(src, dest, size - 1);
		return (*(vu8*)(ptr_d + (size - 1)) = *(vu8 *)(ptr_s + (size - 1)), (void)0);
	}
	if (((ptr_d % 4) && !(ptr_d % 2)) || ((ptr_s % 4) && !(ptr_s % 2)))
		return (CpuCopy16(src, dest, size), (void)0);
	if (!(size % 32))
		return (CpuFastCopy(src, dest, size), (void)0);
	if (!(size % 4))
		return (CpuCopy32(src, dest, size), (void)0);
	CpuCopy16(src, dest, size);
}
#pragma endregion
