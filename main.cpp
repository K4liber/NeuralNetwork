#include "lib.h"

using namespace std;

int main(int argc,char *argv[])
{
  string fileName;
  double epsilon;
  
  if(argv[1])
    fileName = argv[1];
  else
    fileName = "dane.txt";
  
  if(argv[2])
    epsilon = atof(argv[2]);
  else
    epsilon = 0.01;
  
  /*
  //generateData();
  vector<double> dataFromFile = getData(fileName);
  int StreamSize = getStreamSize(fileName);
  vector< vector<int> > pixels = getPixels(dataFromFile,epsilon);
  vector<double> lines = getLines(pixels);
  //drawRecursiveDiagram(dataFromFile, epsilon);
  vector<double> histogram = getHistogram(lines);
  
  cout<<"Entropia: "<<getEntropy(histogram)<<endl;
  cout<<"Lines: "<<int(lines.size())<<endl;
  */
  
  logisticMap(epsilon);
  
  return( 0 );
  
}


