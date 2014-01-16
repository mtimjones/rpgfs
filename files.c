#include "rpgtypes.h"
#include <strings.h>

Files_t *allocateFile( int type, int level )
{
  Files_t* handle;
  int value;

  handle = (Files_t*)malloc(sizeof(Files_t));

  bzero( (void*)handle, sizeof(Files_t) );

  handle->type = type;

  switch( type )
  {
    case USER_STATS_FILE:
      handle->u.stats.level = 1;
      handle->u.stats.health = 10;
      handle->u.stats.strength = 1;
      handle->u.stats.protection = 1;
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
      if (value < 3) handle->u.item.unlockItem = INCREASE_STRENGTH;
      else if (value < 6) handle->u.item.unlockItem = INCREASE_PROTECTION;
      else 
      {
        handle->u.item.unlockItem = RESTORE_HEALTH;
        handle->u.item.value = (level/2) + getRand(4);
      }
      printf("Item %d\n", handle->u.item.unlockItem);
      break;

    case BUG_FILE:
      strcpy( handle->name, "bug.txt");
      handle->u.stats.level = level;
      handle->u.stats.health = level*2+getRand(3);
      handle->u.stats.strength = 1+getRand(level*2);
      handle->u.stats.protection = 1+getRand(level*2);
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
      printf("\tHealth:     %3d\n", handle->u.stats.health);
      printf("\tStrength:   %3d\n", handle->u.stats.strength);
      printf("\tProtection: %3d\n", handle->u.stats.protection);
      printf("\n");
      break;

    case ROOT_HELP_FILE:
      printf("\nWelcome to RPGFS.\n\n");
      printf("  Use 'cd' to change subdirectories.\n");
      printf("  Use 'cat' to inspect files.\n");
      printf("  Use 'rm' to remove bugs (to allow movement).\n\n");
      printf("  Find a special file to destroy the filesystem.\n\n");
      break;

    case BUG_FILE:
      printf("\nBug stats\n");
      printf("\tLevel:      %3d\n", handle->u.stats.level);
      printf("\tHealth:     %3d\n", handle->u.stats.health);
      printf("\tStrength:   %3d\n", handle->u.stats.strength);
      printf("\tProtection: %3d\n", handle->u.stats.protection);
      printf("\n");
      break;

    default:
      assert(0);
  }

  return;
}


void addFileToList( Subdirs_t* subdir, Files_t* file )
{
  printf("adding %s\n", file->name);
  if (subdir->list)
  {
    Files_t* walker = subdir->list;
    printf("%s  ", walker->name);
    while( walker->next ) walker = walker->next;
    walker->next = file;
    file->next = (Files_t*)0;
  } 
  else 
  {
    subdir->list = file;
    printf("empty");
  }
printf("\n");

  return;
}


// BUG HERE...
Files_t* removeFileFromList( Subdirs_t* subdir, char* filename )
{
  Files_t* walker;

  walker = subdir->list;

  if (!walker) return (walker);

  if (!strncmp(walker->name, filename, strlen(filename)))
  {
    subdir->list = walker->next;
    walker->next = (Files_t*)0;
    return walker;
  }

  while (walker->next)
  {
    if (!strncmp(walker->next->name, filename, strlen(filename)))
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


