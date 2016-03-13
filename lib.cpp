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