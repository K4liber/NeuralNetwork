#include "lib.h"

using namespace std;

int main(int argc,char *argv[])
{
  double epsilon;
  
  if(argv[1])
    epsilon = atof(argv[1]);
  else
    epsilon = 0.01;

  
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

 // vector<double> data = getNeuronDeviation(100,0.008,1000,1);
  drawRecursiveDiagram(dataFromFile, epsilon);
  
 	
  //void drawEntropy(int N, double time, double timeStep, double gStart, double gStop, double gStep, double epsilon)
  
 // drawEntropy(10, 1000, 1, 0, 1, 0.01,epsilon);

  return( 0 );
  
}


