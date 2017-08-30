#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "sha2.h"

static inline void memory_protect(void) {}

static inline int memory_bootloader_hash(uint8_t *hash) {
    memset(hash, 0, SHA256_DIGEST_LENGTH);

    return SHA256_DIGEST_LENGTH;
}

#endif
