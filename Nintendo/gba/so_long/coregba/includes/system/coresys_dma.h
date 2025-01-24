/* ************************************************************************** */
/*   ~Header by : NyTekCFW~                                   SVSC Dev Team   */
/*                                                                            */
/*   coresys_dma.h                                                            */
/*                                                                            */
/*   By: NyTekCFW - Youtube.com/NyTekCFW                                      */
/*                                                                            */
/*   Created: 13/12/2024 21:04:40 by NyTekCFW                                 */
/*   Updated: 20/12/2024 19:47:13 by NyTekCFW                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORESYS_DMA_H
# define CORESYS_DMA_H

# define DMA_SYNC_TO_TIMER		0x30000000

//# define DMA_32					(1 << 10) // Transfert de 32 bits (au lieu de 16 bits)
 // Synchronisation avec un timer (déclenche le DMA à chaque cycle de timer)
/*
#define REG_DMA1SAD				(*(volatile uint32_t *)0x40000BC)
#define REG_DMA1DAD				(*(volatile uint32_t *)0x40000C0)
//#define REG_DMA1CNT				(*(volatile uint32_t *)0x40000C4)
#define REG_DMA2SAD				(*(volatile uint32_t *)0x40000C8)
#define REG_DMA2DAD				(*(volatile uint32_t *)0x40000CC)
//#define REG_DMA2CNT				(*(volatile uint32_t *)0x40000D0)
#define DMA_ENABLE				(1 << 15) // Activer le DMA
//#define DMA_REPEAT				(1 << 9)  // Répéter le transfert (utilisé avec un déclencheur comme un timer)
//#define DMA_SRC_INC				(0 << 7)  // Incrémenter l'adresse source après chaque transfert (par défaut)
//#define DMA_SRC_FIXED			(1 << 7)  // Source fixe (adresse source reste constante)
// not sort and optimized
*/
/*
#define DmaSetUnchecked(dmaNum, src, dest, control) \
{                                                 \
    vu32 *dmaRegs = (vu32 *)REG_ADDR_DMA##dmaNum; \
    dmaRegs[0] = (vu32)(src);                     \
    dmaRegs[1] = (vu32)(dest);                    \
    dmaRegs[2] = (vu32)(control);                 \
    dmaRegs[2];                                   \
}

#if MODERN
// NOTE: Assumes 16-bit DMAs.
#define DmaSet(dmaNum, src, dest, control) \
    do \
    { \
        _Static_assert(_Alignof(src) >= __builtin_choose_expr(__builtin_constant_p(control), ((control) & (DMA_32BIT << 16)) ? 4 : 2, 2), "source potentially unaligned"); \
        _Static_assert(_Alignof(dest) >= __builtin_choose_expr(__builtin_constant_p(control), ((control) & (DMA_32BIT << 16)) ? 4 : 2, 2), "destination potentially unaligned"); \
        DmaSetUnchecked(dmaNum, src, dest, control); \
    } while (0)
#else
#define DmaSet(dmaNum, src, dest, control) \
    DmaSetUnchecked(dmaNum, src, dest, control)
#endif

#define DMA_FILL_UNCHECKED(dmaNum, value, dest, size, bit)                                    \
{                                                                                             \
    vu##bit tmp = (vu##bit)(value);                                                           \
    DmaSet(dmaNum,                                                                            \
           &tmp,                                                                              \
           dest,                                                                              \
           (DMA_ENABLE | DMA_START_NOW | DMA_##bit##BIT | DMA_SRC_FIXED | DMA_DEST_INC) << 16 \
         | ((size)/(bit/8)));                                                                 \
}

#if MODERN
#define DMA_FILL(dmaNum, value, dest, size, bit) \
    do \
    { \
        _Static_assert(_Alignof(dest) >= (bit / 8), "destination potentially unaligned"); \
        DMA_FILL_UNCHECKED(dmaNum, value, dest, size, bit); \
    } while (0)
#else
#define DMA_FILL(dmaNum, value, dest, size, bit) DMA_FILL_UNCHECKED(dmaNum, value, dest, size, bit)
#endif

#define DmaFill16(dmaNum, value, dest, size) DMA_FILL(dmaNum, value, dest, size, 16)
#define DmaFill32(dmaNum, value, dest, size) DMA_FILL(dmaNum, value, dest, size, 32)

// Note that the DMA clear macros cause the DMA control value to be calculated
// at runtime rather than compile time. The size is divided by the DMA transfer
// unit size (2 or 4 bytes) and then combined with the DMA control flags using a
// bitwise OR operation.

#define DMA_CLEAR_UNCHECKED(dmaNum, dest, size, bit) \
{                                           \
    vu##bit *_dest = (vu##bit *)(dest);     \
    u32 _size = size;                       \
    DmaFill##bit(dmaNum, 0, _dest, _size);  \
}

#if MODERN
#define DMA_CLEAR(dmaNum, dest, size, bit) \
    do \
    { \
        _Static_assert(_Alignof(dest) >= (bit / 8), "destination potentially unaligned"); \
        DMA_CLEAR_UNCHECKED(dmaNum, dest, size, bit); \
    } while (0)
#else
#define DMA_CLEAR(dmaNum, dest, size, bit) DMA_CLEAR_UNCHECKED(dmaNum, dest, size, bit)
#endif

#define DmaClear16(dmaNum, dest, size) DMA_CLEAR(dmaNum, dest, size, 16)
#define DmaClear32(dmaNum, dest, size) DMA_CLEAR(dmaNum, dest, size, 32)

#define DMA_COPY_UNCHECKED(dmaNum, src, dest, size, bit)                                    \
    DmaSet(dmaNum,                                                                          \
           src,                                                                             \
           dest,                                                                            \
           (DMA_ENABLE | DMA_START_NOW | DMA_##bit##BIT | DMA_SRC_INC | DMA_DEST_INC) << 16 \
         | ((size)/(bit/8)))

#if MODERN
#define DMA_COPY(dmaNum, src, dest, size, bit) \
    do \
    { \
        _Static_assert(_Alignof(src) >= (bit / 8), "source potentially unaligned"); \
        _Static_assert(_Alignof(dest) >= (bit / 8), "destination potentially unaligned"); \
        DMA_COPY_UNCHECKED(dmaNum, src, dest, size, bit); \
    } while (0)
#else
#define DMA_COPY(dmaNum, src, dest, size, bit) DMA_COPY_UNCHECKED(dmaNum, src, dest, size, bit)
#endif

#define DmaCopy16(dmaNum, src, dest, size) DMA_COPY(dmaNum, src, dest, size, 16)
#define DmaCopy32(dmaNum, src, dest, size) DMA_COPY(dmaNum, src, dest, size, 32)

#define DmaCopyLarge(dmaNum, src, dest, size, block, bit) \
{                                                         \
    const void *_src = src;                               \
    void *_dest = dest;                                   \
    u32 _size = size;                                     \
    while (1)                                             \
    {                                                     \
        DmaCopy##bit(dmaNum, _src, _dest, (block));       \
        _src += (block);                                  \
        _dest += (block);                                 \
        _size -= (block);                                 \
        if (_size <= (block))                             \
        {                                                 \
            DmaCopy##bit(dmaNum, _src, _dest, _size);     \
            break;                                        \
        }                                                 \
    }                                                     \
}

#define DmaCopyLarge16(dmaNum, src, dest, size, block) DmaCopyLarge(dmaNum, src, dest, size, block, 16)

#define DmaCopyLarge32(dmaNum, src, dest, size, block) DmaCopyLarge(dmaNum, src, dest, size, block, 32)

#define DmaFillLarge(dmaNum, value, dest, size, block, bit) \
{                                                           \
    void *_dest = dest;                                     \
    u32 _size = size;                                       \
    while (1)                                               \
    {                                                       \
        DmaFill##bit(dmaNum, value, _dest, (block));       \
        _dest += (block);                                   \
        _size -= (block);                                   \
        if (_size <= (block))                               \
        {                                                   \
            DmaFill##bit(dmaNum, value, _dest, _size);     \
            break;                                          \
        }                                                   \
    }                                                       \
}

#define DmaFillLarge16(dmaNum, value, dest, size, block) DmaFillLarge(dmaNum, value, dest, size, block, 16)

#define DmaFillLarge32(dmaNum, value, dest, size, block) DmaFillLarge(dmaNum, value, dest, size, block, 32)

#define DmaClearLarge(dmaNum, dest, size, block, bit) \
{                                                           \
    void *_dest = dest;                                     \
    u32 _size = size;                                       \
    while (1)                                               \
    {                                                       \
        DmaFill##bit(dmaNum, 0, _dest, (block));       \
        _dest += (block);                                   \
        _size -= (block);                                   \
        if (_size <= (block))                               \
        {                                                   \
            DmaFill##bit(dmaNum, 0, _dest, _size);     \
            break;                                          \
        }                                                   \
    }                                                       \
}

#define DmaClearLarge16(dmaNum, dest, size, block) DmaClearLarge(dmaNum, dest, size, block, 16)

#define DmaClearLarge32(dmaNum, dest, size, block) DmaClearLarge(dmaNum, dest, size, block, 32)

#define DmaCopyDefvars(dmaNum, src, dest, size, bit) \
{                                                    \
    const void *_src = src;                          \
    void *_dest = dest;                              \
    u32 _size = size;                                \
    DmaCopy##bit(dmaNum, _src, _dest, _size);        \
}

#define DmaCopy16Defvars(dmaNum, src, dest, size) DmaCopyDefvars(dmaNum, src, dest, size, 16)
#define DmaCopy32Defvars(dmaNum, src, dest, size) DmaCopyDefvars(dmaNum, src, dest, size, 32)

#define DmaFillDefvars(dmaNum, value, dest, size, bit) \
{                                                      \
    void *_dest = dest;                                \
    u32 _size = size;                                  \
    DmaFill##bit(dmaNum, value, _dest, _size);         \
}

#define DmaFill16Defvars(dmaNum, value, dest, size) DmaFillDefvars(dmaNum, value, dest, size, 16)
#define DmaFill32Defvars(dmaNum, value, dest, size) DmaFillDefvars(dmaNum, value, dest, size, 32)

#define DmaClearDefvars(dmaNum, dest, size, bit) \
{                                                \
    void *_dest = dest;                          \
    u32 _size = size;                            \
    DmaClear##bit(dmaNum, _dest, _size);         \
}

#define DmaClear16Defvars(dmaNum, dest, size) DmaClearDefvars(dmaNum, dest, size, 16)
#define DmaClear32Defvars(dmaNum, dest, size) DmaClearDefvars(dmaNum, dest, size, 32)

#define DmaStop(dmaNum)                                         \
{                                                               \
    vu16 *dmaRegs = (vu16 *)REG_ADDR_DMA##dmaNum;               \
    dmaRegs[5] &= ~(DMA_START_MASK | DMA_DREQ_ON | DMA_REPEAT); \
    dmaRegs[5] &= ~DMA_ENABLE;                                  \
    dmaRegs[5];                                                 \
}

#define IntrEnable(flags)                                       \
{                                                               \
    u16 imeTemp;                                                \
                                                                \
    imeTemp = REG_IME;                                          \
    REG_IME = 0;                                                \
    REG_IE |= flags;                                            \
    REG_IME = imeTemp;                                          \
}                                                               \
*/
#endif
