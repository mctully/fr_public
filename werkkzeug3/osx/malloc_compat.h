#include <assert.h>

inline void *_aligned_malloc(size_t inBytes, size_t inAlignment)
{
	// on OS X, malloc is 16 byte aligned
	assert(inAlignment<=16);
	return malloc(inBytes);
}

void _aligned_free(void *inMem)
{
	free(inMem);
}
