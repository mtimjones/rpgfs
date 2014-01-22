#include "rpgtypes.h"

typedef struct {
  int constant;
  int variant;
} depth_entry_t;

const depth_entry_t children_at_depth[6] = {
  { 4, 0 }, // 0
  { 2, 1 }, // 1
  { 1, 2 }, // 2
  { 2, 1 }, // 3
  { 0, 0 }  // 4
};


int numberOfChildren( int level )
{
  assert( level < 6 );
  return children_at_depth[level].constant + 
          getRand(children_at_depth[level].variant);
}
