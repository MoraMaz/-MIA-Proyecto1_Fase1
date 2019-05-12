#ifndef REPORTS_H_
#define REPORTS_H_
#include <stdlib.h>
#include <stdio.h>
#include <Structs.h>
#include <string.h>
#include "time.h"
#include "math.h"
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

int rep_disk(char id[5], char path[200]);
int rep_mbr(char id[5], char path[200]);

#endif /* REPORTS_H_ */
