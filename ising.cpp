#include "ising.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <math.h>
#include <random>
#include <fstream>


Ising::Ising(Lattice &lattice, std::mt19937 gen)
      : spinConfig(lattice.GetVolume())
      {
        // When new Ising object gets constructed, a new random spin configuration is assigned
        //randSpin(gen);
        coldConfig();
      }


void Ising::calcEnergy(Lattice &lattice){
  E = 0;
  for (int i = 0; i< spinConfig.size(); i++){
    // Storing the vector of the neirest neighbour to avoid multiple function calls
    std::vector<int> neigh = lattice.get_nearNeigh(i);
    // Calculating the Energy of the configuration by adding up two sigma values
    E += -spinConfig[i]*(spinConfig[neigh[0]]+spinConfig[neigh[2]]);
  }
  //std::cout << "Debug output Energy: " << E << '\n';
}

double Ising::getEn() const{
  // returns the value of the energydensity
    return (double)E/spinConfig.size();
  }

int Ising::gete() const{
  // returns the value of the total energy
  return E;
}

int Ising::locDeltaE(Lattice &lattice, int i){
  // Return int instead of the vecotr increases speed by a factor of 4
  // calculating the enegy change in case one Spin i is flipped
  std::vector<int> neigh = lattice.get_nearNeigh(i);
  // Applying deltaE = 2*J*s_k * \sum s_i with i to k = next neighbours
  return 2*spinConfig[i]*(spinConfig[neigh[0]]+spinConfig[neigh[1]]+ spinConfig[neigh[2]]+ spinConfig[neigh[3]]);
}



void Ising::calcAbsM(){
  // calculating the absolute magnetization
  AbsM = 0;
  for (int i = 0; i< spinConfig.size(); i++){
    // Just looping over the Spins and summing them up
    AbsM += spinConfig[i];
  }
  //std::cout << "Debug output AbsM: " << AbsM << '\n';
}

int Ising::getM() const{
  // returns the magnetization
  return AbsM;
}


double Ising::getAbsM() const{
  //returns the absoute value of the magnetization
  return abs((double)AbsM)/spinConfig.size();
}


int Ising::locDeltaM(Lattice &lattice, int i){
  // calculating the Magnetization change delta m (minus because of the flip)
  return -2*spinConfig[i];

}


void Ising::flip(int i){
// The flip methode flips one spin value for linearAdress i
spinConfig[i] = -spinConfig[i];
}


void Ising::coldConfig(){

  for (int i = 0; i< spinConfig.size();i++){
    spinConfig[i] = -1;
  }
}


void Ising::randSpin(std::mt19937 gen){
    // define a uniform distribution for integers between 0 and 1
    std::uniform_int_distribution<int> unidist(0,1);
    // randomly assign a spin value of -1 or +1 to the system
    for (int i = 0; i < spinConfig.size(); i++){
      if(unidist(gen) <= 0.5){
        spinConfig[i] = -1;
      }else {
        spinConfig[i] = 1;
      }
    }
}
