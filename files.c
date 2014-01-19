#include "rpgtypes.h"
#include <strings.h>

Files_t *allocateFile( int type, int level )
{
  Files_t* handle;
  int value;
  static int bugnum = 0;

  handle = (Files_t*)malloc(sizeof(Files_t));

  bzero( (void*)handle, sizeof(Files_t) );

  handle->type = type;

  handle->next = (Files_t*)0;

  switch( type )
  {
    case USER_STATS_FILE:
      handle->u.stats.level = 1;
      handle->u.stats.health = 10;
      handle->u.stats.maxhealth = 10;
      handle->u.stats.strength = 2;
      handle->u.stats.protection = 2;
      handle->u.stats.xp = 0;
      handle->u.stats.xptonextlevel = 10;
      strcpy(handle->name, "user.txt");
      break;

    case ROOT_HELP_FILE:
      strcpy( handle->name, "help.txt");
      break;

    case HELP_FILE:
      break;

    case ITEM_FILE:
      strcpy( handle->name, "item.txt");
      value = getRand(10);
      if (value < 2) handle->u.item.unlockItem = INCREASE_STRENGTH;
      else if (value < 4) handle->u.item.unlockItem = INCREASE_PROTECTION;
      else 
      {
        handle->u.item.unlockItem = RESTORE_HEALTH;
        handle->u.item.value = (level/2) + getRand(4);
      }
      break;

    case BUG_FILE:
      handle->u.stats.level = level;
      handle->u.stats.health = level*2+getRand(2);
      handle->u.stats.strength = 1+getRand(level+1);
      handle->u.stats.protection = 1+getRand(level+1);
      sprintf( handle->name, "bug%d.txt", bugnum++);
      break;

    default:
      assert(0);
  }

  return handle;
}


void cat_a_file( Files_t* handle )
{
  assert(handle);

  switch( handle->type )
  {
    case USER_STATS_FILE:
      printf("\nUser stats\n");
      printf("\tLevel:      %3d\n", handle->u.stats.level);
      printf("\tHealth:     %3d / %3d\n", 
        handle->u.stats.health, handle->u.stats.maxhealth);
      printf("\tStrength:   %3d\n", handle->u.stats.strength);
      printf("\tProtection: %3d\n", handle->u.stats.protection);
      printf("\tXP/Next     %3d / %3d\n", 
         handle->u.stats.xp, handle->u.stats.xptonextlevel);
      printf("\n");
      break;

    case ROOT_HELP_FILE:
      printf("\nWelcome to RPGFS.\n\n");
      printf("  Use 'cd' to change subdirectories.\n");
      printf("  Use 'cat' to inspect files.\n");
      printf("  Use 'rm' to remove bugs (to allow movement).\n\n");
      printf("  Find a special file to destroy the filesystem.\n");
      printf("\n");
      break;

    case BUG_FILE:
      printf("\nBug stats\n");
      printf("\tLevel:      %3d\n", handle->u.stats.level);
      printf("\tHealth:     %3d\n", handle->u.stats.health);
      printf("\tStrength:   %3d\n", handle->u.stats.strength);
      printf("\tProtection: %3d\n", handle->u.stats.protection);
      printf("\n");
      break;

    case ITEM_FILE:
      switch (handle->u.item.unlockItem)
      {
        case INCREASE_STRENGTH:
          printf("Strength increase\n");
          
          break;
        case INCREASE_PROTECTION:
          printf("Protection increase\n");
          break;
        case RESTORE_HEALTH:
          printf("Health increase (%d)\n", handle->u.item.value);
          break;
        default:
          assert(0);
          break;
      }
      printf("\n");
      break;

    default:
      assert(0);
  }

  return;
}


void addFileToList( Subdirs_t* subdir, Files_t* file )
{
  if (subdir->list)
  {
    Files_t* walker = subdir->list;
    while( walker->next ) walker = walker->next;
    walker->next = file;
    file->next = (Files_t*)0;
  } 
  else 
  {
    subdir->list = file;
  }

  return;
}


Files_t* removeFileFromList( Subdirs_t* subdir, char* filename )
{
  Files_t* walker;

  walker = subdir->list;

  if (!walker) return (walker);

  if (!strncmp(walker->name, filename, strlen(walker->name)))
  {
    subdir->list = walker->next;
    walker->next = (Files_t*)0;
    return walker;
  }

  while (walker->next)
  {
    if (!strncmp(walker->next->name, filename, strlen(walker->name)))
    {
      Files_t* target = walker->next;
      walker->next = walker->next->next;
      target->next = (Files_t*)0;
      return target;
    }
    walker = walker->next;
  }

  return (Files_t*)0;
}


Files_t* findFileInList( Subdirs_t* subdir, char* filename )
{
  Files_t* walker;

  walker = subdir->list;

  while( walker )
  {
    if (!strncmp(walker->name, filename, strlen(filename))) break;
    walker = walker->next;
  }

  return walker;
}


int fileInstancesInSubdir( Subdirs_t* subdir, int type )
{
  Files_t* walker;
  int count = 0;

  walker = subdir->list;

  while( walker )
  {
    if (walker->type == type) count++;
    walker = walker->next;
  }

  return count;
}

