#include "lib.h"

using namespace std;

vector <double> getNeuronDeviation(int N, double g, double time, double timeStep ){
	int neigh = 3;
	double deviation = 0;
	vector <double> neuronDeviation;
	int timeStart = 200;

	vector <double> S0;
	S0.resize(N);
	for(int i=0;i<N;i++)
		S0[i] = ( 2.*rand()/RAND_MAX ) -1;

	vector<double> H;
	H.resize(N);

	vector<double> S;
	S.resize(N);
	for(int i=0;i<N;i++)
		S[i] = S0[i];

	vector <vector<double> > J;
	J.resize(N);
	for(int i=0;i<N;i++){
		J[i].resize(N);
		for(int l=0;l<i;l++){
			J[i][l] = ( 2.*rand()/RAND_MAX ) -1;
			J[l][i] = J[i][l];
		}	
	}

	for(int t=0;t<time+timeStart;t++){

		for(int j=0; j<N; j++){
			for(int z=(j-neigh);z<=(j+neigh);z+=1){
				if(z>0 && z<N)
					H[j]+=(double)J[j][z]*(double)S[z];
			}
		}

		
		for( int j=0; j<N; j++)
			S[j]=(double)tanh((double)g*(double)H[j]);//+(double)signalAmplitiude*(double)sin(t/period*2*M_PI));

		//Zerowe warunki brzegowe
		S[0] = 0;
		S[N-1] = 0;
	
		for( int i=0; i<N; i++)
			deviation+=pow((S0[i] - S[i]),2.0);

		neuronDeviation.push_back((double)deviation/(double)N);
		

		for(int i=0; i<N; i++)
			H[i] = (double)0;
		
		deviation = 0;
	
	}
	return neuronDeviation;
}

vector<double> getNeuronDeviation2 (int N, double g, double time, double timeStep )
{
	int Nneighbours=3;
	double period=1;
	vector <double> neuronS0;
	double signalAmplitiude=3;
	vector<double> neuronsH;
	vector<double> neuronsHp;
	vector<double> neuronsS;
	vector<double> neuronDeviation;
	double sum;
	vector <vector<double> > J;
	J.resize(N);
	double start = period*50;
	for(int i=0;i<J.size();i++){
		J[i].resize(N);
		for(int l=0;l<i;l++){
			J[i][l] = ( 2.*rand()/RAND_MAX ) -1;
			J[l][i] = J[i][l];
		}	
	}

	for(int i=0; i<N; i++)
	{
		neuronS0.push_back((double)(( (double)2.*(double)((double)rand()/(double)RAND_MAX)) -(double)1.));
		neuronsH.push_back((double)0);
		neuronsHp.push_back((double)1);
		neuronsS.push_back(neuronS0[i]);
	}
	for(int t=0; t<time; t+=1)
	{
		sum=0;

		for(int i=0; i<N; i++){
			neuronsH[i] = (double)0.;
			}

		if(t>0){
			for( int j=0; j<N; j++)
			{
				neuronsS[j]=(double)tanh((double)g*(double)neuronsHp[j]+(double)signalAmplitiude*(double)sin(t/period*2*M_PI));
				
			}
		
			for( int i=0; i<N; i++)
			{
				sum+=pow((neuronS0[i] - neuronsS[i]),2.0);
			}
			if(t>200){
				neuronDeviation.push_back((double)sum/(double)N);
				cout<<(double)sum/(double)N<<endl;
			}
		}

		for(int j=0; j<N; j++)
		{
			for(int z=(j-Nneighbours);z<=(j+Nneighbours);z+=1)
			{

				if(j!=z && z>0 && z<N){
					neuronsH[j]+=(double)J[j][z]*(double)neuronsS[z];
				}
			}
			neuronsHp[j] = neuronsH[j];
			if(t==100)
				cout<<"T=100 J="<<j<<" "<<neuronsHp[j]<<endl;
			if(t==101)
				cout<<"T=101 J="<<j<<" "<<neuronsHp[j]<<endl;
			if(t==102)
				cout<<"T=102 J="<<j<<" "<<neuronsHp[j]<<endl;
		}	
		
	}
	return neuronDeviation;
}


void drawEntropy(int N, double time, double timeStep, double gStart, double gStop, double gStep, double epsilon){
	fstream plik( "networkData.txt", ios::out );
	

	
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
		if( plik.good() ){
			plik <<entropy<< endl;
			plik.flush();
		}
		if(rysuj)
			line(diagram, 100+g/gStop*800, -previosEntropy*80+800, 100+(g+gStep)/gStop*800, -entropy*80+800, makecol( 0, 0, 0 ) );
		previosEntropy = entropy;
		
		rysuj = 1;
	}
	blit( diagram, screen, 0, 0, 0, 0, diagram->w, diagram->h );
	readkey();
	destroy_bitmap( diagram );
	allegro_exit();
	plik.close();
}
