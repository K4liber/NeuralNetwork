#include "lib.h"

using namespace std;

int main(int argc,char *argv[])
{
  double epsilon;
  
  if(argv[1])
    epsilon = atof(argv[1]);
  else
    epsilon = 0.01;


  vector<double> data = getNeuronDeviation(100,0.008,1000,1);
  drawRecursiveDiagram(data, epsilon);

  return( 0 );
  
}
