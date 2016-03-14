#ifndef lib_h
#define lib_h

using namespace std;

void generateData();
int getStreamSize(string fileName);
double getEntropy(vector<double> histogram);
vector<double>  getData(string fileName);
vector<double>  getHistogram(vector<double> lines);

#endif

