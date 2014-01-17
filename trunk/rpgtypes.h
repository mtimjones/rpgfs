// rpgtypes.h

#ifndef __RPGTYPES_H__
#define __RPGTYPES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define getSRand()      ((float)rand() / (float)RAND_MAX)
#define getRand(x)      (int)((x) * getSRand())

// Files type

#define USER_STATS_FILE		1
#define ROOT_HELP_FILE		2
#define HELP_FILE		3
#define ITEM_FILE		4
#define BUG_FILE		5

// Item File types

#define INCREASE_STRENGTH	1
#define INCREASE_PROTECTION	2
#define RESTORE_HEALTH		3

typedef struct {
  int level;
  int health;
  int strength;
  int protection;
} Stats_t;

typedef struct {
  int unlockItem;
  int value;
} Items_t;

struct Files_s;

typedef struct Files_s {
  struct Files_s* next;
  int type;
  char name[40];
  union {
    Stats_t stats;
    Items_t item;
  } u;
} Files_t;


//
// Subdirs Structure
//

// Attributes
#define ROOT_NODE	1

struct Subdirs_s;

typedef struct Subdirs_s {
  char         name[40];
  struct Subdirs_s*   parent;
  struct Subdirs_s*   root;   // Subdir list
  struct Subdirs_s*   next;   // Next ptr
  Files_t*     list;
  unsigned int attr;
} Subdirs_t;

#define hit(us,bs)	((float)us / ((float)us+(float)bs))
#define dmg(ul, ua, bd) (int)((float)ul * (float)ua / (float)bd)+1

#endif
