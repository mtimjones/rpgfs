// init.c

#include <string.h>
#include "rpgtypes.h"

Subdirs_t* curpwd;

void addNode(Subdirs_t* cur, Subdirs_t* child)
{
  Subdirs_t* walker = cur->root;
  while (walker->next) walker = walker->next;
  walker->next = child;
  child->next = (Subdirs_t*)0;

  return;
}


void buildSubtree( Subdirs_t* current, int level )
{
  int children = numberOfChildren(level);

  Files_t* allocateFile( int, int );

  current->root = current->next = (Subdirs_t*)0;
  current->list = (Files_t*)0;

  // Add a bug?
  {
    int j;

    if (level < 3) j = 2; else j = 3;
    while (j--)
    {
      if ((level > 0) && (getSRand() < 0.75))
      {
        addFileToList( current, allocateFile( BUG_FILE, getRand(level)+1 ) );
      }
    }
  }

  // Add an item?
  if (getSRand() < (0.15*(float)level))
  {
    addFileToList( current, allocateFile( ITEM_FILE, level ) );
  }

  while (children--)
  {
    Subdirs_t* child = malloc(sizeof(Subdirs_t));

    strcpy(child->name, (const char *)getName());

    child->parent = current;

    child->attr = 0;

    if (current->root == (Subdirs_t*)0) 
    {
      current->root = child;
      current->next = (Subdirs_t*)0;
    } else addNode( current, child );

    buildSubtree( child, level+1 );

  }

  return;
}


void rpginit( void )
{
  extern Subdirs_t* dirlist[];
  extern int cur_depth;

  Files_t* allocateFile( int, int );

  Subdirs_t* root;
  Files_t* handle;

  curpwd = root = (Subdirs_t*)malloc(sizeof(Subdirs_t));

  dirlist[cur_depth++] = root;

  strcpy(root->name, "/");

  root->attr = ROOT_NODE;

  root->parent = (Subdirs_t*)0;

  buildSubtree( root, 0 );

  // Add root-level files
  handle = allocateFile( USER_STATS_FILE, 1 );
  addFileToList( root, handle );
  handle = allocateFile( ROOT_HELP_FILE, 1 );
  addFileToList( root, handle );

  return;
}

