#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "utils/matrix.h"

TMatrix* fcfs(TMatrix *c);
TMatrix* lrjf(TMatrix *c);
TMatrix* heuristic(TMatrix *c);

#endif
