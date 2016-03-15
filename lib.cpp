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
    if( plik.good() )
    {
        for( int i = 0; i < 500; i++ )
        {
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
  file.open( const_cast<char*>(("Dane/" + fileName).c_str()), ios::in | ios::out );
  if( file.good() == true )
  {   
    while(file != 0){
      char line[ 255 ];
      file.getline( line, 255 );
      data.push_back(atof(line));
    }
    file.close();
  }
  return data;
}

vector<double> getHistogram(vector<double> lines){
  double maxLine = *max_element(lines.begin(), lines.end());
  vector<double> histogram(maxLine+1);
  for( int i = 0; i < maxLine+1; i++ )
    histogram[i] = 0;
  
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
  allegro_init();
  install_keyboard();
  set_color_depth( 16 );
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1000, 1000, 0, 0 );
  clear_to_color( screen, makecol( 128, 128, 128 ) );
  BITMAP * diagram = NULL;
  diagram = create_bitmap( 1000, 1000 );
  if( !diagram )
  {
      set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
      allegro_message( "Picture cannot be loaded!" );
      allegro_exit();
  }
  clear_to_color( diagram, makecol( 0, 0, 0 ) );
  for(int ii=0;ii<dataFromFile.size();ii++){
    for(int jj=0;jj<dataFromFile.size();jj++){
      if(abs(dataFromFile[ii] - dataFromFile[jj]) > epsilon)
	putpixel( diagram, ii, jj, makecol( 255, 255, 255 ) );
    }
  }
  blit( diagram, screen, 0, 0, 0, 0, diagram->w, diagram->h );
  readkey();
  destroy_bitmap( diagram );
  allegro_exit();
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