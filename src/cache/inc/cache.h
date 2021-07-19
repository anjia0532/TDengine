/*
 * Copyright (c) 2019 TAOS Data, Inc. <cli@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TDENGINE_CACHE_H
#define TDENGINE_CACHE_H

#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*cache_load_func_t)(void*, const char* key, uint8_t nkey, char** value, size_t *len);

typedef struct cache_option_t {
  size_t limit;               /* size limit */

  double factor;              /* slab growth factor */

  int hashPowerInit;

  void* userData;             /* user data */

  cache_load_func_t loadFunc; /* user defined load data function */
} cache_option_t;

typedef enum cache_code_t {
  CACHE_OK    = 0,
  CACHE_FAIL  = -1,
  CACHE_OOM   = -2,
  CACHE_KEY_NOT_FOUND = -3,
  CACHE_REACH_LIMIT = -4,
  CACHE_ALLOC_FAIL = -5,
} cache_code_t;

struct cache_t;
typedef struct cache_t cache_t;

cache_t* cache_create(cache_option_t* options);
void  cache_destroy(cache_t*);

cache_code_t cache_put(cache_t* cache, const char* key, uint8_t nkey, const char* value, int nbytes);

cache_code_t cache_get(cache_t* cache, const char* key, uint8_t nkey, char** value, int *len);

void         cache_remove(cache_t* cache, const char* key);

#ifdef __cplusplus
}
#endif

#endif  // TDENGINE_CACHE_H