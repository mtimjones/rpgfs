#include "rpgtypes.h"

Subdirs_t* dirlist[7]={0, 0, 0, 0, 0, 0, 0};
int cur_depth = 0;

int unlocked = 0;

void cmd_ls( void )
{
  extern Subdirs_t* curpwd;
  Subdirs_t* cur = curpwd->root;
  Files_t* files = curpwd->list;

  printf(".\n");
  printf("..\n");

  while (cur)
  {
    printf("%s\n", cur->name);
    cur = cur->next;
  }

  while (files)
  {
    printf("%s\n", files->name);
    files = files->next;
  }

  return;
}

void cmd_pwd( void )
{
  int i;

  for (i = 0 ; i < cur_depth ; i++)
  {
    if (dirlist[i] == (Subdirs_t*)0) break;
    else printf("%s", dirlist[i]->name);
    if (i > 0) printf("/");
  }
  printf("\n");

  return;
}

void cmd_cd( char* file )
{
  Files_t* user;

  extern Subdirs_t* curpwd;

  int filelen = strlen(file);

  if (fileInstancesInSubdir( curpwd, BUG_FILE ) )
  {
    printf("Can't cd at this time.\n");
    return;
  }

  if      (!strncmp(file, "..", filelen))
  {
    // User want to move up the filesystem.
    extern Subdirs_t* curpwd;
    if (curpwd->attr & ROOT_NODE) return;

    user = removeFileFromList( curpwd, "user.txt" );

    // Move up one subdirectory
    curpwd = curpwd->parent;

    addFileToList( curpwd, user );

    cur_depth--;

    return;
  }
  else if (!strncmp(file, ".", filelen))
  {
    // No action is required.
    return;
  }
  else
  {
    Subdirs_t* cur = curpwd->root;

    // Search for the filename
    while (cur)
    {
      if (!strncmp(file, cur->name, filelen))
      {
        user = removeFileFromList( curpwd, "user.txt" );
        curpwd = cur;
        addFileToList( curpwd, user );
        dirlist[cur_depth++] = cur;
        return;
      }
      cur = cur->next;
    }

  }

  printf("No such file or directory.\n");

  return;
}


void cmd_cat( char* file )
{
  int filelen = strlen(file);
  Files_t* handle;

  Files_t* findFileInList( Subdirs_t*, char* );

  extern Subdirs_t* curpwd;

  handle = findFileInList( curpwd, file );

  if (handle) cat_a_file( handle );
  else printf("No such file.\n");

  return;
}


void cmd_rm( char* file )
{
  int filelen = strlen(file);
  Files_t* object;

  extern Subdirs_t* curpwd;
  Files_t* findFileInList( Subdirs_t*, char* );

  object = findFileInList( curpwd, file );

  if (object)
  {

    if (!strncmp(object->name, "user.txt", filelen))
    {
      printf("\nYou are logged out.\n\n");
      exit(0);
    } 
    else if (!strncmp(object->name, "key.txt", filelen))
    {
      unlocked = 1;
      (void)removeFileFromList( curpwd, file );
      free(object);
    }
    else if (!strncmp(object->name, "help.txt", filelen))
    {
      (void)removeFileFromList( curpwd, file );
      free(object);
    }
    else if (object->type == BUG_FILE)
    {
      Files_t* user = findFileInList( curpwd, "user.txt" );

      bugsAttack( user );

      assert(user);

      if (getSRand() < hit(user->u.stats.strength,object->u.stats.strength))
      {
        int damage;

        damage = dmg(user->u.stats.level, user->u.stats.strength,
                      object->u.stats.protection);

        printf("%s damaged %d\n", object->name, damage);

        object->u.stats.health -= damage;

        if (object->u.stats.health <= 0) {

// Instead, add three files (health, strength, protection), and allow
// the user to pick one.  After the selection, delete the other two.

          printf("bug is dead.\n");
          (void)removeFileFromList( curpwd, file );

          user->u.stats.xp += 
            (object->u.stats.strength + object->u.stats.protection);

          if (user->u.stats.xp >= user->u.stats.xptonextlevel)
          {
            printf("Increased level\n");
            user->u.stats.level++;
            user->u.stats.xptonextlevel = 
              user->u.stats.xptonextlevel +
                (int)(user->u.stats.xptonextlevel * 1.1);

            if (getSRand() < 0.3)
            {
              printf("Strength increased.\n");
              user->u.stats.strength++;
            }
            else if (getSRand() < 0.6)
            {
              printf("Protection increased.\n");
              user->u.stats.protection++;
            }
            else
            {
              printf("Health increased.\n");
printf("%d/%d\n", user->u.stats.health, user->u.stats.maxhealth);
              user->u.stats.maxhealth += (getRand(user->u.stats.level)+1);
              user->u.stats.health += 
                getRand(user->u.stats.maxhealth - user->u.stats.health);
printf("%d/%d\n", user->u.stats.health, user->u.stats.maxhealth);
            }
          }

          return;

        }

      }
    
    }
    else if (object->type == ITEM_FILE)
    {
      Files_t* user = findFileInList( curpwd, "user.txt" );

      (void)removeFileFromList( curpwd, file );

      if (object->u.item.unlockItem == INCREASE_STRENGTH)
      {
        user->u.stats.strength++;
        printf("Strength increased\n");
      }
      else if (object->u.item.unlockItem == INCREASE_PROTECTION)
      {
        user->u.stats.protection++;
        printf("Protection increased\n");
      }
      else if (object->u.item.unlockItem == RESTORE_HEALTH)
      {
        int inc = object->u.item.value;
        if (user->u.stats.health + object->u.item.value > 
              user->u.stats.maxhealth)
        {
          inc = user->u.stats.maxhealth - user->u.stats.health;
        }
        user->u.stats.health += inc;

        printf("Health restored %d\n", inc);
      }
    }
    else
    {
      printf("File not found.\n");
    }
  }
  else
  {
    printf("File not found.\n");
  }

  return;
}

void cmd_format( void )
{
  Files_t* findFileInList( Subdirs_t*, char* );
  extern Subdirs_t* curpwd;

  if (unlocked)
  {
    Files_t* user = findFileInList( curpwd, "user.txt" );

    cmd_cat("user.txt");

    printf("Filesystem deleted.\n");

    exit(0);
  }
  else 
  {
    printf("Command not found.\n");
  }

  return;
}


void processCommand( char *cmd, char *option )
{
  int cmdlen = strlen(cmd);

  if      (!strncmp(cmd, "ls", cmdlen)) cmd_ls();
  else if (!strncmp(cmd, "pwd", cmdlen)) cmd_pwd();
  else if (!strncmp(cmd, "cd", cmdlen)) cmd_cd( option );
  else if (!strncmp(cmd, "cat", cmdlen)) cmd_cat( option );
  else if (!strncmp(cmd, "rm", cmdlen)) cmd_rm( option );
  else if (!strncmp(cmd, "format", cmdlen)) cmd_format();
  else printf("Command not recognized.\n");

  return;
}


void performShell( void )
{
  char cmdline[80] = {0};
  char lastcmd[80] = {0};
  char cmd[80];
  char option[80];
  int ret;

  printf("\nUser is logged in.\n\n");

  while (1) 
  {
    printf("$ ");
    cmdline[0] = 0;
    (void)gets(cmdline);

    if (cmdline[0] == '!') strcpy(cmdline, lastcmd);

    ret = sscanf(cmdline, "%s %s", cmd, option);

    if (ret >= 1) 
    {
      processCommand( cmd, option );
      if (cmdline[0] != '!') strcpy(lastcmd, cmdline);
    }

  }

  return;
}
