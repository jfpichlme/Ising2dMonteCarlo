#include "metropolis.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <map>
#include <chrono>
#include <random>
#include <fstream>



Metropolis::Metropolis(Ising &ising, Lattice &lattice, double temp, double Nmc)
           : ExpoMap(), temp{temp}, Nmc{Nmc}, eVec(Nmc), magnVec(Nmc), vol(lattice.GetVolume())
{
  // When Metropolis object is initialized, the lookup table containing the exponential
  // is filled up
  calcExpo(temp);
}

void Metropolis::calcExpo(double temp){
// Iserting the exponentials in a map (dictionary)
ExpoMap.insert({4, exp(-4*1/temp)});
ExpoMap.insert({8, exp(-8*1/temp)});
}


void Metropolis::metroRun(Ising &ising, Lattice &lattice, std::mt19937 gen, char *Energyfilename, char *Magnetfilname){
  // Paramters:       Ising = ising object priorly created
  //                  Lattice = lattic oject priorly created
  //                  gen   = seed for random number
  //                  *Energyfilename = filename in which the Energy density values are stored
  //                  *Magnetfilename = filename in which the absolute magnetization density is stored


  // File that saves the values for the absolute magnetization density
  std::ofstream magnetfile;
  magnetfile.open(Magnetfilname);

  // File that saves the values for the Energy density
  std::ofstream energyfile;
  energyfile.open(Energyfilename);

  // count for the acceptance rate
  int count = 0;

  // The energy is updated in the local variable Energy. During the Markov run
  // it is constantly updated by deltaE
  ising.calcEnergy(lattice);
  int Energy = ising.gete();

  ising.calcAbsM();
  int Magnetization = ising.getM();


  std::cout << "Markov run with temperature: " << temp << "K started" << '\n';
  // Defining the r for the reject accept step
  std::uniform_real_distribution<double> dist(0, 1);

  for (int i = 0; i < Nmc; i++){
    //outer loop for the number of sweeps in each Markov chain
    for (int k = 0; k < lattice.GetVolume(); k++){

      // calculating local deltas
      deltaE = ising.locDeltaE(lattice, k);
      deltaM = ising.locDeltaM(lattice, k);

      // calculating delta E
      //Bracket
      double r = dist(gen);

      if (deltaE < 0){
        // If delta E is smaller than 0 flip
        ising.flip(k);
        // update Energy
        Energy += deltaE;
        // update Magnetization
        Magnetization += deltaM;
        // counter for the acceptance Count
        count += 1;
      }else if (r <= ExpoMap[deltaE]){
        // if the uniform random number is smaller or equal to the exponential
        // flip the spin
        ising.flip(k);
        // update Energy
        Energy += deltaE;
        // update Magnetization
        Magnetization += deltaM;
        // counter for the acceptance Count
        count += 1;
      }
  }
  //ising.calcEnergy(lattice);
  //std::cout << Energy << " im Vergleich mit "<< ising.gete()<< '\n';
  //std::cout << (double)Energy/lattice.GetVolume() << " compared to " << ising.getEn() << '\n';
  //ising.calcAbsM();
  //std::cout << Magnetization << " im vergleich mit " << ising.getM() << '\n';
  //ising.calcAbsM();
  magnVec[i] = abs((double)Magnetization)/vol;
  eVec[i] = (double)Energy/vol;


  // Storing the derived values in the respective files
  magnetfile << i << "     " << magnVec[i] << '\n';
  energyfile << i << "     " << eVec[i] << '\n';
}
magnetfile.close();
energyfile.close();
std::cout << "Finished storing and calculation of absMagn and energy density" << '\n';
}

double Metropolis::averageE(){
  // Returning the average energy density (excluding the first 10.000)
  return average(eVec, 10000);
}

double Metropolis::averageM(){
  // Returing the average magnetization density (excluding the first 10.0000)
  return average(magnVec, 10000);
}

double Metropolis::specific_heat(){
 // Returning the specific heat for the System
  stdE = standDev(eVec, 10000);
  return pow(1/temp,2)*pow(stdE,2)*vol;
}

double Metropolis::magnSuscept(){
  // Returning the magnetic susceptibility for the System
  stdM = standDev(magnVec, 10000);
  return 1/temp * pow(stdM, 2)*vol;
}
