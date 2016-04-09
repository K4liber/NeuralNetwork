#ifndef lib_h
#define lib_h

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <allegro.h> 
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void generateData();
int getStreamSize(string fileName);
double getEntropy(vector<double> histogram);
vector<double>  getData(string fileName);
vector<double>  getHistogram(vector<double> lines);
vector< vector<int> > getPixels(vector<double> dataFromFile, double epsilon);
void drawRecursiveDiagram(vector<double> dataFromFile, double epsilon);
vector<double> getLines(vector< vector<int> > pixels);
vector<double> getLogisticMap(int mapSize, int mapStart, double x0, double r);
void logisticMap(double epsilon);
vector<double> getNeuronDeviation (int N, double g, double time, double timeStep );
void drawEntropy(int N, double time, double timeStep, double gStart, double gStop, double gStep, double epsilon);
void drawReturnsMap (double param, int T);
void drawXnXnp1 (double param);

#endif

