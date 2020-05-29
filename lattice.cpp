#include <vector>
#include <iostream>
#include <chrono>
#include <math.h>
#include <random>
#include <fstream>

#include "lattice.h"


    // Calling the initializer for the lattice
Lattice::Lattice(int d, int l)
      : d{d},l{l},vol{l*l},spinStates(vol), neaNab(vol)
    {
      nearNaibFill();
    }


  // Function that fills up the nearest neignbour
void Lattice::nearNaibFill()
  {
    for (int i = 0; i < l ; i++){
      // outer loop for getting the x coordinates
     for (int j = 0; j < l ; j++){
       // inner loop for getting the y coordinates
       //std::cout << linearAdress(i,j) << '\n';
       neaNab[linearAdress(i,j)]= {left_neigh(i,j),right_neigh(i,j),up_neigh(i,j),down_neigh(i,j)};
     }
    }
  }

// function calculating linearAdress of left neighbour
int Lattice::left_neigh(int x, int y){
    if (x==0){
      return (linearAdress((l-1),y));
    }else {
      return linearAdress(x-1,y);
    }
}

// function calculating linearAdress of right neighbour
int Lattice::right_neigh(int x, int y){
    if (x==l-1){
      return (linearAdress(0,y));
    }else {return linearAdress(x+1,y);
    }
}

// function calculating linearAdress of up neighbour
int Lattice::up_neigh(int x, int y){
    if (y==0){
      return(linearAdress(x,(l-1)));
    }else {
      return linearAdress(x,(y-1));
    }
}

// function calculating linearAdress of down neighbour
int Lattice::down_neigh(int x,int y){
    if (y==l-1){
      return(linearAdress(x,0));
    }else {
      return linearAdress(x,(y+1));
    }
}

// function returning linearAdress for a given (x,y) coordinate for a lattice
int Lattice::linearAdress(int x, int y){
    // Starting with 0,0 = 0, 0,1 = 1, 0,2 = 2...
    return (l*x+y);
}

// Getting the volume
int Lattice::GetVolume() const{
  // returning the private variable volume
  return vol;
}

// Returning a Vector of the four nearest neighbours
std::vector<int> Lattice::get_nearNeigh(int linA){
  // returning the nearest neighbours as a vector
    return (neaNab[linA]);
}

Lattice::get_nearNeigh2(int linA, int nN){

    return()
}
