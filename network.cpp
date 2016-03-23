#include "lib.h"

using namespace std;

vector<double> getNeuronDeviation (int N, double g, double time, double timeStep )
   {
     int Nneighbours=1;
     double period=2;
     double neuronS0=1;
     double signalAmplitiude=1;
     vector<double> neuronsH;
     vector<double> neuronsS;
     vector<double> neuronDeviation;
     double sum;
     for(int i=0; i<N; i++)
	{
	  neuronsH.push_back(0);
	  neuronsS.push_back(neuronS0);
	}
     for(double t=0; t<time; t=+timeStep)
	{
	sum=0;
	for(int j=0; j<N; j++)
	    {
            if(j>0)
            {
            	for(int z=(j-Nneighbours);z<=(j+Nneighbours);z+=Nneighbours)
	     	    {
                    if(j!=z)
                     	{
			 neuronsH[j]+=neuronsS[z];
			}
		    }
	    }
	}
     for( int j=0; j<N; j++)
	{
 	  neuronsS[j]=tanh(g*neuronsH[j]+signalAmplitiude*sin(t/period*2*M_PI));
        }
     for( int i=0; i<N; i++)
	{
	  sum+=pow((neuronS0-neuronsS[i]),2.0);
	}
        neuronDeviation.push_back(sum/N);
       }
	
         
     return neuronDeviation;
}
     
