/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/

//shm_hashtable.h

#ifndef _SHM_HASH_TABLE_H
#define _SHM_HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/shm.h>
#include "common_define.h"
#include "shmcache_types.h"
#include "shm_list.h"
#include "shm_value_allocator.h"

#define HT_ENTRY_PTR(context, entry_offset) ((struct shm_hash_entry *) \
    (context->segments.hashtable.base + entry_offset))

#define HT_CALC_EXPIRES(current_time, ttl) \
    (ttl == SHMCACHE_NEVER_EXPIRED ? 0 : current_time + ttl)

#define HT_ENTRY_IS_VALID(entry, current_time) \
    (entry->expires == 0 || entry->expires >= current_time)

#ifdef __cplusplus
extern "C" {
#endif

static inline int64_t shm_ht_get_memory_size(const int capacity)
{
    return sizeof(int64_t) * (int64_t)capacity;
}

/**
get hashtable capacity
parameters:
    max_count: max entry counti
return hashtable capacity
*/
int shm_ht_get_capacity(const int max_count);

/**
ht init
parameters:
	context: the context pointer
    capacity: the ht capacity
return none
*/
void shm_ht_init(struct shmcache_context *context, const int capacity);

/**
set value
parameters:
	context: the context pointer
    key: the key
    value: the value, include expires field
return error no, 0 for success, != 0 for fail
*/
int shm_ht_set(struct shmcache_context *context,
        const struct shmcache_key_info *key,
        const struct shmcache_value_info *value);

/**
get value
parameters:
	context: the context pointer
    key: the key
    value: store the returned value
return error no, 0 for success, != 0 for fail
*/
int shm_ht_get(struct shmcache_context *context,
        const struct shmcache_key_info *key,
        struct shmcache_value_info *value);

/**
delete the key for internal usage
parameters:
	context: the context pointer
    key: the key
    recycled: if recycled
return error no, 0 for success, != 0 for fail
*/
int shm_ht_delete_ex(struct shmcache_context *context,
        const struct shmcache_key_info *key, bool *recycled);

/**
delete the key
parameters:
	context: the context pointer
    key: the key
return error no, 0 for success, != 0 for fail
*/
static inline int shm_ht_delete(struct shmcache_context *context,
        const struct shmcache_key_info *key)
{
    bool recycled;
    return shm_ht_delete_ex(context, key, &recycled);
}

static inline int shm_ht_count(struct shmcache_context *context)
{
    return context->memory->hashtable.count;
}

#ifdef __cplusplus
}
#endif

#endif

