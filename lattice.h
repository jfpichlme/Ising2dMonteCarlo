#ifndef LATICCE_H
#define LATICCE_H

#include <vector>
#include <iostream>
#include <chrono>
#include <math.h>
#include <random>
#include <fstream>


// Defining the class Latice which creates an object that can be used by e.b Ising
class Lattice
{

// Arguments for lattice: d = Dimension l1 = GridLength1, L2 = GridLength2,
// vol = Volume of the Lattice (Nr of all spins)
private:
    int d;
    int l;
    int vol;
    std::vector< std::vector<int>> neaNab;
    // Function that fills up the nearest neignbour
    void nearNaibFill();
    int left_neigh(int x, int y);
    int right_neigh(int x, int y);
    int up_neigh(int x, int y);
    int down_neigh(int x,int y);
    int linearAdress(int x, int y);


public:
  std::vector<double> spinStates;
  Lattice(int d, int l);
  int GetVolume() const;
  std::vector<int> get_nearNeigh(int linA);
};

#endif // Lattice.h
