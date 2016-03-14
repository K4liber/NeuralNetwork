#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <allegro.h> 
#include <vector>
#include <algorithm>
#include <string>
#include "lib.h"

using namespace std;

int main(int argc,char *argv[])
{
  string fileName;
  double epsilon;
  cout<<"Argumentów: "<<argc<<endl;
  for(int i=0;i<argc;i++)
    cout<<"Argument: "<<argv[i]<<endl;
  
  if(argv[1])
    fileName = argv[1];
  else
    fileName = "dane.txt";
  
  if(argv[2])
    epsilon = atof(argv[2]);
  else
    epsilon = 0.01;
  
  //generateData();
  vector<double> dataFromFile = getData(fileName);
  int StreamSize=getStreamSize(fileName);
  int connections1 [StreamSize][StreamSize];
  vector<double> lines;
  
  allegro_init();
  install_keyboard();
  set_color_depth( 16 );
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1000, 1000, 0, 0 );
  clear_to_color( screen, makecol( 128, 128, 128 ) );
  BITMAP * obrazek1 = NULL;
  obrazek1 = create_bitmap( 1000, 1000 );
  if( !obrazek1 )
  {
      set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
      allegro_message( "nie mogę załadować obrazka 1 !" );
      allegro_exit();
      return 0;
  }
  clear_to_color( obrazek1, makecol( 0, 0, 0 ) );
  
  //Funckja rysujaca
  for(int ii=0;ii<StreamSize;ii++){
    for(int jj=0;jj<StreamSize;jj++){
      if(abs(dataFromFile[ii] - dataFromFile[jj]) > epsilon){
	putpixel( obrazek1, ii, jj, makecol( 255, 255, 255 ) );
        connections1[ii][jj] = 0;
	}
      else{
	connections1[ii][jj] = 1;
      }
    }
  }
 
  blit( obrazek1, screen, 0, 0, 0, 0, obrazek1->w, obrazek1->h );
  readkey();
  destroy_bitmap( obrazek1 );
  allegro_exit();
  
  int k,h;
  for(int ii=0;ii<StreamSize-1;ii++){
    for(int jj=0;jj<StreamSize-1;jj++){
      k=0;
      while(connections1[ii+k][jj+k]==1){
	connections1[ii+k][jj+k]=0;
	k++;
      }
      if(k>1)
	lines.push_back(k);
    }
  }
  
  vector<double> histogram = getHistogram(lines);
  
  cout<<"Entropia: "<<getEntropy(histogram)<<endl;
  cout<<"Lines: "<<int(lines.size())<<endl;

  return( 0 );
  
}


