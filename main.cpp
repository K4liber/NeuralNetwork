#include "lib.h"

using namespace std;

int main(int argc,char *argv[])
{
  double epsilon;
  srand( time( NULL ) );
  if(argv[1])
    epsilon = atof(argv[1]);
  else
    epsilon = 0.01;

  /*
  generateData();
  vector<double> dataFromFile = getData("dane1.txt");
 // int StreamSize = getStreamSize(fileName);
  vector< vector<int> > pixels = getPixels(dataFromFile,epsilon);
  vector<double> lines = getLines(pixels);
  //drawRecursiveDiagram(dataFromFile, epsilon);
  vector<double> histogram = getHistogram(lines);
  
  cout<<"Entropia: "<<getEntropy(histogram)<<endl;
  cout<<"Lines: "<<int(lines.size())<<endl;
  //logisticMap(epsilon);

  
  drawRecursiveDiagram(dataFromFile, epsilon);
  
 	
  //void drawEntropy(int N, double time, double timeStep, double gStart, double gStop, double gStep, double epsilon)
  */
  //drawEntropy(100, 100, 1, 0.05, 5, 0.05,epsilon);
  vector<double> data = getNeuronDeviation(10,2,10,1);
  return( 0 );
  
}


