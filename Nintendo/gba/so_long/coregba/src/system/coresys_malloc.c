/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_malloc.c                                                         */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 14/12/2024 16:20:24 by NyTekCFW                                 */
/*   Updated: 20/12/2024 19:55:13 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/coregba.h"

#ifndef MAX_SECTOR
//Total sector available
# define MAX_SECTOR				512//8 ko of sector
#endif

#ifndef MEMORY_HEAP_SIZE
//Heap size
# define MEMORY_HEAP_SIZE		65536 //64 ko reserved for heap
#endif

typedef struct mmap_s
{
	u32		available_memory;
	u16		used_blocks;
	u16		max_sector;
	u32		start_address;
	u32		end_address;
}ALIGNED(4)	t_mmap;

typedef struct sector_s
{
	u16		size;
	u8		is_free;
	void	*ptr;
}ALIGNED(4)	t_sector;//size = 16

//Aligned to 4 for memory optimization
ALIGNED(4) IN_EWRAM char		_mem_heap[MEMORY_HEAP_SIZE];	//Heap region
ALIGNED(4) IN_EWRAM t_sector	_sectors[MAX_SECTOR];			//sector region
ALIGNED(4) IN_EWRAM t_mmap		_mmap = {0};					//memory structure info

//func prototype
static t_mmap					*get_mmap(void);
static void						mmap_init(void);

#pragma region ALLOC_REG
static void	malloc_init(void)
{
	int	i = 0;

	while (i < MAX_SECTOR)
	{
		_sectors[i].is_free = 1;
		_sectors[i].ptr = NULL;
		_sectors[i].size = 0;
		++i;
	}
}

static void	update_mmap(int i, u16 used_block, u32 used_mem, u16 max_sector)
{
	t_mmap	*mmap = get_mmap();

	while (i < MAX_SECTOR)
	{
		if (!_sectors[i].is_free)
		{
			max_sector = i + 1;
			used_mem += _sectors[i].size;
			++used_block;
		}
		++i;
	}
	mmap->available_memory = MEMORY_HEAP_SIZE - used_mem;
	mmap->used_blocks = used_block;
	mmap->max_sector = max_sector;
}

static t_sector	*find_sector(void *ptr)
{
	int			i = 0;

	if (!ptr)
		return (NULL);
	while (i < get_mmap()->max_sector)
	{
		if (!_sectors[i].is_free && _sectors[i].ptr == ptr)
			return (&_sectors[i]);
		++i;
	}
	return (NULL);
}

void	*mx_malloc(u32 size)
{
	static u8	initialized = 0;
	int			i = 0;
	uintptr_t	aligned_ptr = 0;
	u16			used_block = 0;
	u16			max_sector = 0;
	u32			used_mem = 0;

	if (!initialized)
	{
		initialized = 1;
		malloc_init();
		mmap_init();
	}
	if (!size)
		return (NULL);
	size = (size + 3) & ~3;
	while (i < MAX_SECTOR)
	{
		if (_sectors[i].is_free)
		{
			if (i == 0)
				_sectors[i].ptr = _mem_heap;
			else
				_sectors[i].ptr = (void *)((uintptr_t)_sectors[i - 1].ptr) + _sectors[i - 1].size;
			aligned_ptr = (uintptr_t)_sectors[i].ptr;
			if ((aligned_ptr % 4))
			{
				aligned_ptr += 4 - (aligned_ptr % 4);
				_sectors[i].ptr = (void *)aligned_ptr;
			}
			if ((uintptr_t)_sectors[i].ptr + size <= (uintptr_t)get_mmap()->end_address)
			{
				_sectors[i].is_free = 0;
				_sectors[i].size = size;
				update_mmap(i, used_block, used_mem, max_sector);
				return (_sectors[i].ptr);
			}
		}
		else
		{
			max_sector = i + 1;
			used_mem += _sectors[i].size;
			++used_block;
		}
		++i;
	}
	return (NULL);
}

void	mx_free(void* ptr)
{
	static u16	block_reached = 0;
	t_mmap		*mmap = get_mmap();
	int			i = 0;

	if (!ptr)
		return;
	while (i < mmap->max_sector)
	{
		if (_sectors[i].ptr == ptr && !_sectors[i].is_free)
		{
			if (i > block_reached)
				++block_reached;
			_sectors[i].is_free = 1;
			CpuFill(_sectors[i].ptr, 0, _sectors[i].size);
			_sectors[i].ptr = NULL;
			mmap->available_memory += _sectors[i].size;
			--mmap->used_blocks;
			if (i == (s16)mmap->max_sector - 1)
			{
				while (--i > -1)
				{
					if (!_sectors[i].is_free)
					{
						mmap->max_sector = i + 1;
						break;
					}
				}
			}
			if (!mmap->used_blocks)
			{
				mmap->max_sector = 0;
				if (block_reached > (MAX_SECTOR / 8))
				{
					//defragmentation de la memoire
					malloc_init();
					mmap_init();
					block_reached = 0;
				}
			}
			break ;
		}
		++i;
	}
}

void	*mx_realloc(void *ptr, u32 size)
{
	t_sector	*sector = NULL;
	void		*tmp = NULL;

	if (!ptr)
		return (NULL);
	sector = find_sector(ptr);
	if (sector)
	{
		size = (size + 3) & ~3;
		if (sector->size == size)
			return (sector->ptr);
		tmp = mx_malloc(size);
		if (tmp)
		{
			CpuCopy(_sectors->ptr, tmp, size);
			mx_free(sector->ptr);
			return (tmp);
		}
	}
	mx_free(sector->ptr);
	return (NULL);
}

void	*mx_calloc(u32 size)
{
	void	*tmp = NULL;

	if (!size)
		return (NULL);
	size = (size + 3) & ~3;
	tmp = mx_malloc(size);
	if (tmp)
		CpuFill(tmp, 0, size);
	return (tmp);
}
#pragma endregion


//memory map section
#pragma region MEMORY_MAP
static void	mmap_init(void)
{
	t_mmap	*mmap = get_mmap();

	mmap->available_memory = MEMORY_HEAP_SIZE;
	mmap->used_blocks = 0;
	mmap->max_sector = 0;
	mmap->start_address = (u32)(uintptr_t)&_mem_heap[0];
	mmap->end_address = (u32)((uintptr_t)&_mem_heap[0] + MEMORY_HEAP_SIZE);
}

static t_mmap	*get_mmap(void)
{
	return (&_mmap);
}

u32	mmap_get_start_mem(void)
{
	return (get_mmap()->start_address);
}

u32	mmap_get_end_mem(void)
{
	return (get_mmap()->end_address);
}

u32	mmap_get_total_mem(void)
{
	return (MEMORY_HEAP_SIZE);
}

u32	mmap_get_used_mem(void)
{
	return (MEMORY_HEAP_SIZE - get_mmap()->available_memory);
}

u32	mmap_get_free_mem(void)
{
	return (get_mmap()->available_memory);
}

u16	mmap_get_total_sector(void)
{
	return (MAX_SECTOR);
}

u16	mmap_get_used_sector(void)
{
	return (get_mmap()->used_blocks);
}

u16	mmap_get_free_sector(void)
{
	return (MAX_SECTOR - get_mmap()->used_blocks);
}

u32	mmap_get_reserved_size(void)
{//default = 68/256ko reserved in ewram for allocation
	return ((MAX_SECTOR * sizeof(t_sector)) + (MEMORY_HEAP_SIZE) + sizeof(t_mmap));
}
#pragma endregion