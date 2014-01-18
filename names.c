// names.c

#include "rpgtypes.h"

typedef struct {
  char *name;
  char used;
} names_t;

#define MAX_NAMES  122

names_t names[MAX_NAMES] = {
  {"main",0},
  {"test",0},
  {"hidden",0},
  {"temp",0},
  {"published",0},
  {"source",0},
  {"work",0},
  {"void",0},
  {"answer",0},
  {"queer",0},
  {"button",0},
  {"death",0},
  {"dog",0},
  {"watanabe",0},
  {"notes",0},
  {"printed",0},
  {"spool",0},
  {"logs",0},
  {"filth",0},
  {"porn",0},
  {"wafter",0},
  {"collation",0},
  {"ferret",0},
  {"misprints",0},
  {"guides",0},
  {"thoughts",0},
  {"nothing",0},
  {"bend",0},
  {"assoc",0},
  {"silver",0},
  {"octuple",0},
  {"kraus",0},
  {"basal",0},
  {"energy",0},
  {"home",0},
  {"feature",0},
  {"poetry",0},
  {"docs",0},
  {"runt",0},
  {"bullet",0},
  {"random",0},
  {"filate",0},
  {"curse",0},
  {"pulp",0},
  {"fish",0},
  {"history",0},
  {"personal",0},
  {"heliogram",0},
  {"hexadic",0},
  {"vapour",0},
  {"grades",0},
  {"runkle",0},
  {"saltpeter",0},
  {"public",0},
  {"chapters",0},
  {"private",0},
  {"videos",0},
  {"examples",0},
  {"secure",0},
  {"lost",0},
  {"found",0},
  {"dev",0},
  {"boot",0},
  {"usr",0},
  {"dev",0},
  {"lib",0},
  {"proc",0},
  {"media",0},
  {"etc",0},
  {"opt",0},
  {"bin",0},
  {"sbin",0},
  {"sys",0},
  {"system",0},
  {"mnt",0},
  {"blog",0},
  {"misc",0},
  {"games",0},
  {"pix",0},
  {"folder",0},
  {"changed",0},
  {"themes",0},
  {"website",0},
  {"tracing",0},
  {"wallpaper",0},
  {"tasks",0},
  {"perf",0},
  {"recovery",0},
  {"config",0},
  {"trent",0},
  {"pacific",0},
  {"trench",0},
  {"punkt",0},
  {"steps",0},
  {"scar",0},
  {"planet",0},
  {"time",0},
  {"challenges",0},
  {"flat",0},
  {"life",0},
  {"check",0},
  {"ignore",0},
  {"brace",0},
  {"vbox",0},
  {"homework",0},
  {"capture",0},
  {"searches",0},
  {"top",0},
  {"bottom",0},
  {"solution",0},
  {"desktop",0},
  {"light",0},
  {"dark",0},
  {"front",0},
  {"text",0},
  {"category",0},
  {"narrow",0},
  {"trash",0},
  {"gold",0},
  {"silver",0},
  {"easy",0},
  {"files",0}
};



char *getName( void )
{
  int index = getRand(MAX_NAMES);

  while (1) 
  {
    if (!names[index].used) {
      names[index].used = 1;
      return names[index].name;
    }

    if (++index == MAX_NAMES) index = 0;
  }

  return (char *)0;
}

