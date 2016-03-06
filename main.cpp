#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <allegro.h> 


using namespace std;


void generateData(){
    fstream plik( "dane1.txt", ios::out );
    if( plik.good() )
    {
        for( int i = 0; i < 500; i++ )
        {
            plik << i*cos(M_PI*i/50)<< endl;
            plik.flush();
        }
        plik.close();
    }
}

int getStreamSize(){
  fstream p;
  p.open( "dane1.txt", ios::in | ios::out );
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
  int StreamSize=getStreamSize();
  int connections1 [StreamSize][StreamSize];
  int connections2 [StreamSize][StreamSize];
  int nlines1=0;
  int nlines2=0;
  int sizesOfLines[5000];
  for(int ii=0;ii<5000;ii++){
    sizesOfLines[ii] = 0;
  }
  fstream plik;
  plik.open( "dane1.txt", ios::in | ios::out );
  
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
  for(int ii=0;ii<StreamSize;ii++){
    for(int jj=0;jj<StreamSize;jj++){
      if(abs(data[ii] - data[jj]) > 0.05){
	putpixel( obrazek1, ii, jj, makecol( 255, 255, 255 ) );
        connections1[ii][jj] = 0;
        connections2[ii][jj] = 0;
	}
      else{
	connections1[ii][jj] = 1;
        connections2[ii][jj] = 1;
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
      h=0;
      
      while(connections1[ii+k][jj+k]==1){
	connections1[ii+k][jj+k]=0;
	k++;
      }
      
      if(k>1){
	sizesOfLines[nlines1] = k;
	nlines1++;
      }
      while(connections2[StreamSize-h-ii][jj+h]==1){
	connections2[StreamSize-h-ii][jj+h]=0;
	h++;
      }
      
      if(h>1) 
	nlines2++;
    
    }
  }
  
  //Sprawdzamy czy to działa
  int unicalLenghts[1000];
  for(int ii=0;ii<1000;ii++){
    unicalLenghts[ii] = 0;
  }
  int indexOfUnical = 0;
  cout<<"liczba prostych wynosi: "<<nlines1<<" i "<<nlines2<<"\n";
  int index = 0;
  while(sizesOfLines[index] != 0){
    bool isUnical = true;
    for(int ii=0;ii<1000;ii++){
      if(sizesOfLines[index] == sizesOfLines[ii] && index != ii){
	isUnical = false;
	break;
      }
    }
    if(isUnical){
      unicalLenghts[indexOfUnical] = sizesOfLines[index];
      indexOfUnical++;
    }
    index++;
  }
  
  cout<<"Unikalne długości: "<<endl;
  int ll=0;
  cout<<unicalLenghts[0]<<endl;
  while(unicalLenghts[ll] != 0){
    cout<<unicalLenghts[ll]<<endl;
    ll++;
  }
  return( 0 );
  
}


