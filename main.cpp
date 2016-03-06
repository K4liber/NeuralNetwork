#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <allegro.h> 

using namespace std;


void generateData(){
    fstream plik( "dane.txt", ios::out );
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

int getStreamSize(){
  fstream p;
  p.open( "dane.txt", ios::in | ios::out );
  int count = 0;
  if( p.good() == true ){
    while(p != 0){
      char dane[ 255 ];
      p.getline( dane, 255 );
      count++;
    }
    p.close();
  }
  return count-1;
}

int main()
{ 

  generateData();
  double data[getStreamSize()];
  
  fstream plik;
  plik.open( "dane.txt", ios::in | ios::out );
  
  if( plik.good() == true )
  {   
    int ii=0;
    while(plik != 0){
      char dane[ 255 ];
      plik.getline( dane, 255 );
      data[ii] = atof(dane);
      ii++;
    }
    plik.close();
  }
  
  allegro_init();
  install_keyboard();
  set_color_depth( 16 );
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0 );
  clear_to_color( screen, makecol( 128, 128, 128 ) );
  BITMAP * obrazek1 = NULL;
  obrazek1 = create_bitmap( 500, 500 );
  if( !obrazek1 )
  {
      set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
      allegro_message( "nie mogę załadować obrazka 1 !" );
      allegro_exit();
      return 0;
  }
  clear_to_color( obrazek1, makecol( 0, 0, 0 ) );
  
  //Funckja rysujaca
  for(int ii=0;ii<500;ii++){
    for(int jj=0;jj<500;jj++){
      if(abs(data[ii] - data[jj]) > 0.05)
	putpixel( obrazek1, ii, jj, makecol( 255, 255, 255 ) );
    }
  }
  blit( obrazek1, screen, 0, 0, 0, 0, obrazek1->w, obrazek1->h );
  readkey();
  destroy_bitmap( obrazek1 );
  
  allegro_exit();
  
  return( 0 );
  
}


