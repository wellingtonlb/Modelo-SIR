#ifndef _DB_H_

#define _DB_H_

#include "sir.h"

void db_init();
void db_step();
void db_end();

extern char filefolder[256];
extern char filename[512];



#endif //_DB_H_
