#include <stdlib.h>
#include "utils.h"
#include "graph.h"
Point* new_point(int x, int y)
{
    Point* new = (Point*)malloc(sizeof(Point));
    new->x = x;
    new->y = y;
    return new;
}