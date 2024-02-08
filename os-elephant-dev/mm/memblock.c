#include <memblock.h>
#include <mm.h>

unsigned long max_low_pfn;
unsigned long min_low_pfn;
unsigned long max_pfn;
unsigned long long max_possible_pfn;

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define INIT_MEMBLOCK_REGIONS			128

#ifndef INIT_MEMBLOCK_RESERVED_REGIONS
# define INIT_MEMBLOCK_RESERVED_REGIONS		INIT_MEMBLOCK_REGIONS
#endif

#ifndef INIT_MEMBLOCK_MEMORY_REGIONS
#define INIT_MEMBLOCK_MEMORY_REGIONS		INIT_MEMBLOCK_REGIONS
#endif

static struct memblock_region memblock_memory_init_regions[INIT_MEMBLOCK_MEMORY_REGIONS];
static struct memblock_region memblock_reserved_init_regions[INIT_MEMBLOCK_RESERVED_REGIONS];

struct memblock memblock = {
	.memory.regions		= memblock_memory_init_regions,
	.memory.cnt		= 1,	/* empty dummy entry */
	.memory.max		= INIT_MEMBLOCK_MEMORY_REGIONS,
	.memory.name		= "memory",

	.reserved.regions	= memblock_reserved_init_regions,
	.reserved.cnt		= 1,	/* empty dummy entry */
	.reserved.max		= INIT_MEMBLOCK_RESERVED_REGIONS,
	.reserved.name		= "reserved",

	.bottom_up		= false,
	.current_limit		= MEMBLOCK_ALLOC_ANYWHERE,
};

#define for_each_memblock_type(i, memblock_type, rgn)			\
	for (i = 0, rgn = &memblock_type->regions[0];			\
	     i < memblock_type->cnt;					\
	     i++, rgn = &memblock_type->regions[i])

static int memblock_add_region(struct memblock_type *type,
			phys_addr_t base, phys_addr_t size,
			int nid, enum memblock_flags flags)
{
	int idx;
	struct memblock_region *rgn;

	for_each_memblock_type(idx, type, rgn) {
		if (rgn->size == 0) {
			rgn->base = base;
			rgn->size = size;
			rgn->flags = flags;
			memblock_set_region_node(rgn, nid);
			return 0;
		}
	}

	return -12;
}

int memblock_add(phys_addr_t base, phys_addr_t size)
{
	return memblock_add_region(&memblock.memory, base, size, 0, 0);
}