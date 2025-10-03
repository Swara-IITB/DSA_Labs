#include "alloc.h"

void alloc_measure( unsigned VSIZE_RANGE, unsigned REPEAT, std::map<unsigned,float>& m ) {
  std::vector<int> a;
  ClockCounter time;
  for(unsigned i=0; i<REPEAT; i++){
    for(unsigned j=0; j<VSIZE_RANGE; j++){
      time.start();
      a.push_back(0);
      m[j+1] += time.stop();
    }
  }
  for(unsigned j=1; j<=VSIZE_RANGE; j++){
      m[j]/= REPEAT;
  }
 
  
}
