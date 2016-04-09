#include "lib.h"

using namespace std;

int main(int argc,char *argv[])
{
  double g;
  double epsilon;

  if(argv[1])
    g = atof(argv[1]);
  else
    g = 3.5;

  if(argv[2])
    epsilon = atof(argv[2]);
  else
    epsilon = 0.01;

  /*vector<double> data = getLogisticMap(1000, 1000, 0.1, g);
  drawRecursiveDiagram(data, epsilon);
  vector< vector<int> > pixels = getPixels(data,epsilon);
  vector<double> lines = getLines(pixels);
  //drawRecursiveDiagram(dataFromFile, epsilon);
  vector<double> histogram = getHistogram(lines);*/
  drawXnXnp1 (g);
  
  //cout<<"Entropia: "<<getEntropy(histogram)<<endl;

  return( 0 );
}  

