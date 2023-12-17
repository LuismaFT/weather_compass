
#include "utils.h"

float mv_to_celsius(int mv) {
    return (float) ((mv-500)/10);
}

float mv_to_lux(int mv) {
    return (float) ((mv*10000)/((1500-mv)*150));
}

float value_to_percent(int mv){
   return (float) (mv*0.05);
}
