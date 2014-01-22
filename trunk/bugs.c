#include "rpgtypes.h"

void bugsAttack( Files_t* user )
{
  Files_t* walker;

  extern Subdirs_t* curpwd;

  walker = curpwd->list;

  while (walker)
  {
    if (walker->type == BUG_FILE)
    {
      if (getSRand() < hit(walker->u.stats.strength, user->u.stats.strength))
      {
        int damage;

        damage = dmg(walker->u.stats.level, walker->u.stats.strength,
                      user->u.stats.protection);

        printf("%s hits with %d damage.\n", walker->name, damage);

        user->u.stats.health -= damage;

        if (user->u.stats.health <= 0)
        {
          game_over( user );
        }

      }
    }

    walker = walker->next;
  }

  return;
}


void game_over( Files_t* user )
{
   extern int cur_depth;

   printf("You have been unexpectedly logged out at level %d.\n\n", cur_depth);
   printf("Your stats were:\n\n");
   printf("\tLevel:      %3d\n", user->u.stats.level);
   printf("\tHealth:     %3d / %3d\n",
     user->u.stats.health, user->u.stats.maxhealth);
   printf("\tStrength:   %3d\n", user->u.stats.strength);
   printf("\tProtection: %3d\n", user->u.stats.protection);
   printf("\tXP/Next     %3d / %3d\n",
      user->u.stats.xp, user->u.stats.xptonextlevel);
   printf("\tBugs Killed %3d\n", user->u.stats.bugs_killed);
   printf("\tItems Used  %3d\n", user->u.stats.items_used);
   printf("\n");

   exit(0);
}
