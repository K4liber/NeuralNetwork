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
	//0.63 , 4.82 , 4.91 - uporzadkowanie , 2.235

	drawRecursiveDiagram(dataFromFile, epsilon);

	//vector <double> getNeuronDeviation(int N, double g, double time, double timeStep )
	//void drawEntropy(int N, double time, double timeStep, double gStart, double gStop, double gStep, double epsilon)
	*/
	//drawEntropy(100, 24000, 1, 0, 5, 0.02,epsilon);
	//drawReturnsMap(2.22);
	double g = 3.24;
	vector <double> neuronDeviationData = getNeuronDeviation(100, g , 26400, 0,24, 1);
	vector <double> normalizedNeuronDeviationData = normalizeData(neuronDeviationData);
	drawRecursiveDiagram(normalizedNeuronDeviationData, epsilon);
	drawReturnsMapFromData(neuronDeviationData,1);
	writeToFile(neuronDeviationData);

	vector< vector<int> > pixels = getPixels(neuronDeviationData,epsilon);
	vector<double> lines = getLines(pixels);
	vector<double> histogram = getHistogram(lines);
	cout<<"Entropia: "<<getEntropy(histogram)<<" g: "<<g<<endl;

	/*
	double g = 0.83;
	vector <double> neuronDeviationData = getNeuronDeviation(100, g , 26400, 0,24, 1);
	
	generateData();
	vector <double> Data = getData("dane1.txt");		
	writeToFile(Data);
	drawRecursiveDiagram(Data, epsilon);
	drawReturnsMapFromData(Data,1);
	vector< vector<int> > pixels = getPixels(Data,epsilon);
	vector<double> lines = getLines(pixels);
	vector<double> histogram = getHistogram(lines);
	cout<<"Entropia: "<<getEntropy(histogram)<<" g: "<<g<<endl;
	logisticMap(0.01);
	*/
	return( 0 );
  
}


