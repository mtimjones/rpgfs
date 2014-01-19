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
          printf("You are logged out.\n");
          exit(0);
        }

      }
    }

    walker = walker->next;
  }

  return;
}
