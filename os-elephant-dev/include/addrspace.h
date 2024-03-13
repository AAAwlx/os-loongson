#ifndef _ADDRSPACE_H
#define _ADDRSPACE_H

#include <loongarch.h>

#ifndef CACHE_BASE
#define CACHE_BASE		CSR_DMW1_BASE
#endif

#define TO_PHYS_MASK	((1ULL << DMW_PABITS) - 1)

#define TO_CACHE(x)		(CACHE_BASE   |	((x) & TO_PHYS_MASK))//取出后48位偏移地址并与cache的基地址相或取得虚拟地址（前文中将虚拟地址映射到了cache之中

#endif
