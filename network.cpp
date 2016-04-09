#include "lib.h"

using namespace std;

vector<double> getNeuronDeviation (int N, double g, double time, double timeStep )
{
	int Nneighbours=1;
	double period=time/8;
	double neuronS0=1;
	double signalAmplitiude=100;
	vector<double> neuronsH;
	vector<double> neuronsS;
	vector<double> neuronDeviation;
	double sum;
	for(int i=0; i<N; i++)
	{
		neuronsH.push_back(0);
		neuronsS.push_back(neuronS0);
	}
	for(double t=0; t<time; t+=timeStep)
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
			sum+=pow((neuronsS[i]),2.0);
		}
		neuronDeviation.push_back(sum/N);
	}
return neuronDeviation;
}


void drawEntropy(int N, double time, double timeStep, double gStart, double gStop, double gStep, double epsilon){
	allegro_init();
	install_keyboard();
	set_color_depth( 16 );
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1000, 1000, 0, 0 );
	clear_to_color( screen, makecol( 255, 255, 255 ) );
	BITMAP * diagram = NULL;
	diagram = create_bitmap( 1000, 1000 );
	if( !diagram ){
		set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
		allegro_message( "Picture cannot be loaded!" );
		allegro_exit();
	}
	clear_to_color( diagram, makecol( 255, 255, 255 ) );
	double previosEntropy = 0;
	int rysuj = 0;
	double entropy;
	for(double g=gStart;g<=gStop;g+=gStep){
		vector<double> data = getNeuronDeviation(N,g,time,timeStep);
		vector< vector<int> > pixels = getPixels(data,epsilon);
		vector<double> lines = getLines(pixels);
		vector<double> histogram = getHistogram(lines);
		entropy = getEntropy(histogram);
		if(rysuj)
			line(diagram, 100+g/gStop*800, 600-previosEntropy*80, 100+(g+gStep)/gStop*800, 600-entropy*80, makecol( 0, 0, 0 ) );
		previosEntropy = entropy;
		rysuj = 1;
	}
	blit( diagram, screen, 0, 0, 0, 0, diagram->w, diagram->h );
	readkey();
	destroy_bitmap( diagram );
	allegro_exit();
}
