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