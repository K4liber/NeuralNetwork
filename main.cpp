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
        for( int i = 0; i < 100; i++ )
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
  
  return( 0 );
  
}

