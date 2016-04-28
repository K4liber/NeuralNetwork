#include "lib.h"

using namespace std;

double getEntropy(vector<double> histogram){
  double entropy = 0;
  for( int i = 1; i < histogram.size(); i++ ){
    if(histogram[i] > 0 )
      entropy-=histogram[i]*log(histogram[i]);
  }
  return entropy;
}

void generateData(){
  fstream plik( "dane1.txt", ios::out );
  if( plik.good() ){
    for( int i = 0; i < 1000; i++ ){
      plik << sin(M_PI*i/50)<< endl;
      plik.flush();
    }
    plik.close();
  }
}

int getStreamSize(string fileName){
  fstream file;
  file.open( const_cast<char*>(("Dane/" + fileName).c_str()), ios::in | ios::out );
  int count = 0;
  if( file.good() == true ){
    while(file != 0){
      char dane[ 255 ];
      file.getline( dane, 255 );
      count++;
    }
    file.close();
  }
  return count-1;
}

vector<double> getData(string fileName){
  vector<double> data;
  fstream file;
  file.open( const_cast<char*>((fileName).c_str()), ios::in | ios::out );
  if( file.good() == true ){   
    while(file != 0){
      char line[ 255 ];
      file.getline( line, 255 );
      data.push_back(atof(line));
    }
    file.close();
  }
  double max = *max_element(data.begin(),data.end());
  double min = *min_element(data.begin(),data.end());
  for(int ii=0;ii<data.size();ii++)
    data[ii] = 2*(data[ii] - min)/(max-min) -1;
  
  return data;
}

vector<double> normalizeData(vector<double> data){
	double max = *max_element(data.begin(),data.end());
	double min = *min_element(data.begin(),data.end());
	for(int ii=0;ii<data.size();ii++)
		data[ii] = 2*(data[ii] - min)/(max-min) -1;
	
	return data;
}
vector<double> getHistogram(vector<double> lines){
  double maxLine = *max_element(lines.begin(), lines.end());
  vector<double> histogram(maxLine+1);
  
  for( int i = 0; i < lines.size(); i++){
    int index = (int)lines[i];
    histogram[index] += (double)(1/(double)lines.size());
  }
  return histogram;
}

vector< vector<int> > getPixels(vector<double> dataFromFile, double epsilon){
  vector < vector <int> > pixels;
  int dataSize = dataFromFile.size();
  pixels.resize(dataSize);
  for(int ii=0;ii<pixels.size();ii++)
    pixels[ii].resize(dataSize);
  
  for(int ii=0;ii<dataSize-1;ii++){
    for(int jj=0;jj<dataSize-1;jj++){
      if(abs(dataFromFile[ii] - dataFromFile[jj]) > epsilon){
        pixels[ii][jj] = 0;
      }
      else{
	pixels[ii][jj] = 1;
      }
    }
  }
  return pixels;
}

void drawRecursiveDiagram(vector<double> dataFromFile, double epsilon){
	fstream recX1( "recX1.txt", ios::out );
	fstream recY1( "recY1.txt", ios::out );


	for(int ii=0;ii<dataFromFile.size();ii++){
		for(int jj=0;jj<dataFromFile.size();jj++){
			if(abs(dataFromFile[ii] - dataFromFile[jj]) < epsilon){
				//putpixel( diagram, ii, jj, makecol( 200, 0, 0 ) );
				if( recX1.good() ){
					recX1 << ii<< endl;
					recX1.flush();
				}
				if( recY1.good() ){
					recY1 << jj<< endl;
					recY1.flush();
				}
			}
		}
	}

	recX1.close();
	recY1.close();
}


vector<double> getLines(vector< vector<int> > pixels){
  vector<double> lines;
  int k,h;
  for(int ii=0;ii<pixels.size();ii++){
    for(int jj=0;jj<pixels[ii].size();jj++){
      k=0;
      while(pixels[ii+k][jj+k]==1){
	pixels[ii+k][jj+k]=0;
	k++;
      }
      if(k>1)
	lines.push_back(k);
    }
  }
  return lines;
}

vector<double> getLogisticMap(int mapSize, int mapStart, double x0, double r){
  vector<double> logisticMap;
  double xn = x0;
  for(int ii=0;ii<mapSize + mapStart;ii++){
    xn = r*xn*(1.-xn);
    if(ii>mapStart-1)
      logisticMap.push_back(xn);
  }  
  return logisticMap;
}

void drawReturnsMap (double g)
{
	fstream returnsMapX( "returnsMapX.txt", ios::out );
	fstream returnsMapY( "returnsMapY.txt", ios::out );

	//vector <double> getNeuronDeviation(int N, double g, double time, double timeStart,int period, double timeStep );
	vector<double> neuronDeviation=getNeuronDeviation(100,g,5000,0,24,1);
	vector<double> neuronDeviationSlided=getNeuronDeviation(100,g,5000,0,24,1);
	
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

	for( int i=0;i<neuronDeviation.size();i++ ){
		if( returnsMapX.good() ){
			returnsMapX << neuronDeviation[i]<< endl;
			returnsMapX.flush();
		}
		if( returnsMapY.good() ){
			returnsMapY << neuronDeviationSlided[i]<< endl;
			returnsMapY.flush();
		}
	/*
	for( int j=-5;j<6;j++ ){
		
		putpixel( diagram, logMap[i]*1000+j, logMappT[i]*1000, makecol( 0, 0, 0 ) );
		putpixel( diagram, logMap[i]*1000, logMappT[i]*1000+j, makecol( 0, 0, 0 ) );
	}
	*/
	}
	blit( diagram, screen, 0, 0, 0, 0, diagram->w, diagram->h );
	readkey();
	destroy_bitmap( diagram );
	allegro_exit();
	returnsMapX.close();
	returnsMapY.close();

}

void drawReturnsMapFromData (vector <double> signal, int T)
{
	fstream returnsMapX( "returnsMapX.txt", ios::out );
	fstream returnsMapY( "returnsMapY.txt", ios::out );
	
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

	for( int i=0;i<signal.size()-T;i++ ){
		if( returnsMapX.good() ){
			returnsMapX << signal[i]<< endl;
			returnsMapX.flush();
		}
		if( returnsMapY.good() ){
			returnsMapY << signal[i+T]<< endl;
			returnsMapY.flush();
		}
	/*
	for( int j=-5;j<6;j++ ){
		
		putpixel( diagram, logMap[i]*1000+j, logMappT[i]*1000, makecol( 0, 0, 0 ) );
		putpixel( diagram, logMap[i]*1000, logMappT[i]*1000+j, makecol( 0, 0, 0 ) );
	}
	*/
	}
	blit( diagram, screen, 0, 0, 0, 0, diagram->w, diagram->h );
	readkey();
	destroy_bitmap( diagram );
	allegro_exit();
	returnsMapX.close();
	returnsMapY.close();

}


void drawXnXnp1 (double param)
{
	vector<double> logMap=getLogisticMap(1000,1000,0.1,param);
	
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

	for( int i=0;i<(logMap.size()-1);i++ ){
	for( int j=-5;j<6;j++ ){

	putpixel( diagram,logMap[i]*1000,logMap[i+1]*1000, makecol( 0, 0, 0 ) );
	cout<<logMap[i]<<endl;
	}
	}
	blit( diagram, screen, 0, 0, 0, 0, diagram->w, diagram->h );
	readkey();
	destroy_bitmap( diagram );
	allegro_exit();

}


void logisticMap(double epsilon){

	fstream entropyLogistic( "entropyLogistic.txt", ios::out );

	vector<double> logisticMap1;
	double logisticEpsilon = epsilon;
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
	for( double i=0;i<999;i++ ){
		logisticMap1=getLogisticMap(1000,1000,0.1,3.5+(double)i/2000);
		vector< vector<int> > logisticMap1Pixels = getPixels(logisticMap1,logisticEpsilon);
		vector<double> logisticMap1Lines = getLines(logisticMap1Pixels);
		//drawRecursiveDiagram(logisticMap1, logisticEpsilon);
		vector<double> logisticMap1Histogram = getHistogram(logisticMap1Lines);
		double logisticMapEntropy = getEntropy(logisticMap1Histogram);
		//putpixel( diagram, i*10, 800-logisticMapEntropy*100, makecol( 0, 0, 0 ) );	
		line(diagram, i, 100-previosEntropy*80, (i+1), 100-logisticMapEntropy*80, makecol( 0, 0, 0 ) );
		previosEntropy = getEntropy(logisticMap1Histogram);
		if( entropyLogistic.good() ){
			entropyLogistic << logisticMapEntropy << endl;
			entropyLogistic.flush();
		}
	}
	blit( diagram, screen, 0, 0, 0, 0, diagram->w, diagram->h );
	readkey();
	destroy_bitmap( diagram );
	allegro_exit();
	entropyLogistic.close();

}

void writeToFile(vector <double> signal){
	fstream plik( "signal.txt", ios::out );
	if( plik.good() ){
		for( int i = 0; i < signal.size(); i++ )
			plik << signal[i] << endl;
		plik.flush();
	}
	plik.close();
}

