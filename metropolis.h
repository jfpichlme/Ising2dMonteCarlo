#ifndef METROPOLIS_H
#define METROPOLIS_H

#include <vector>
#include "lattice.h"
#include "ising.h"
#include "stats.h"
#include <math.h>
#include <map>
#include <random>
#include <fstream>


class Metropolis{

public:
  Metropolis(Ising &ising, Lattice &lattice, double temp, double Nmc);
  void metroRun(Ising &ising, Lattice &lattice, std::mt19937 gen, char *Energyfilename, char *Magnetfilname);
  std::vector<double> magnVec;
  std::vector<double> eVec;
  double averageE();
  double averageM();
  double stdE;
  double stdM;
  double specific_heat();
  double magnSuscept();




private:
  int deltaE;
  int deltaM;
  int vol;
  double temp;
  double Nmc;
  void calcExpo(double temp);
  std::map<int, double> ExpoMap;
  std::ofstream energyfile;
  std::ofstream magnetfile;


};
#endif // Metroplis.h
