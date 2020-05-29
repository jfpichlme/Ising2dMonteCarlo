#ifndef ISING_H
#define ISING_H



#include <vector>
#include "lattice.h"



class Ising
{

public:
  Ising(Lattice &lattice, std::mt19937 gen);
  void randSpin(std::mt19937 gen);
  void coldConfig();
  void calcEnergy(Lattice &lattice);
  void calcAbsM();
  double getEn() const;
  double getAbsM() const;
  int gete() const;
  void flip(int i);
  int locDeltaE(Lattice &lattice, int i);
  int getM() const;
  int locDeltaM(Lattice &lattice, int i);




private:
  std::vector<int> spinConfig;
  int AbsM;
  int E;




};
#endif // ising.h
