#include "rpgtypes.h"

Subdirs_t* dirlist[7]={0, 0, 0, 0, 0, 0, 0};
int cur_depth = 0;


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

  object = removeFileFromList( curpwd, file );

  if (object)
  {
    if (!strncmp(object->name, "user.txt", filelen))
    {
      printf("\nYou are dead.\n\n");
      exit(0);
    } 
    else if (!strncmp(object->name, "help.txt", filelen))
    {
      free(object);
    }
    else
    {
      printf("File not found.\n");
    }
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
  else printf("Command not recognized.\n");

  return;
}


void performShell( void )
{
  char cmdline[80];
  char cmd[80];
  char option[80];
  int ret;

  while (1) 
  {
    printf("$ ");
    cmdline[0] = 0;
    (void)gets(cmdline);

    ret = sscanf(cmdline, "%s %s", cmd, option);

    if (ret >= 1) processCommand( cmd, option );

  }

  return;
}