#include "lattice.h"
#include "ising.h"
#include "metropolis.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <math.h>
#include <random>
#include <fstream>




int main() {

  // Generating the lattice object that can be reused for each Metropolis run
  Lattice lattice1(2,64);

  // Number of Markov chains
  int Nmc = 100000;

  // define a mersenne twister generator
  std::mt19937 gen;




  // Starting with T = 2.3 K

  // make a unique seed based on the current time
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();


  // initialize generator with the seed
  gen.seed(seed);

  // Generating the Ising object that can be ruesed by assinging the spins
  // randomly at the beginning with different seeds
  Ising ising1(lattice1, gen);


  // Metropolis algorithm for T = 2 K
  Metropolis metropolis1(ising1, lattice1, 2.0, Nmc);

  // Filename in which the energy and magnetization density is stored
  char energyValues1[] = "EnergyValues2.txt";
  char magnValues1[] = "MagnValues2.txt";

  //Starting the metropolis algorithm
  metropolis1.metroRun(ising1,lattice1, gen, energyValues1, magnValues1);

  std::cout << "Average e: " << metropolis1.averageE()<< " Average M: " << metropolis1.averageM()  << '\n';
  std::cout << "c = " << metropolis1.specific_heat() << " x = " << metropolis1.magnSuscept() << '\n';
  std::cout << '\n';




  // T = 2.3 K

  unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();



  // initialize generator with the seed
  gen.seed(seed1);

  // assigning the new seed for the next Markov run (cold configuration)
  ising1.randSpin(gen);

  // Metropolis algorithm for T = 2 K
  Metropolis metropolis2(ising1, lattice1, 2.3, Nmc);

  // Filename in which the energy and magnetization density is stored
  char energyValues2[] = "EnergyValues23.txt";
  char magnValues2[] = "MagnValues23.txt";

  //Starting the metropolis algorithm
  metropolis2.metroRun(ising1,lattice1, gen, energyValues2, magnValues2);

  std::cout << "Average e: " << metropolis2.averageE()<< " Average M: " << metropolis2.averageM()  << '\n';
  std::cout << "c = " << metropolis2.specific_heat() << " x = " << metropolis2.magnSuscept() << '\n';
  std::cout << '\n';




  // T = 2.6 K

  unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();


  // initialize generator with the seed
  gen.seed(seed2);

  // assigning the new seed for the next Markov run (cold configuration)
  ising1.randSpin(gen);

  // Metropolis algorithm for T = 2 K
  Metropolis metropolis3(ising1, lattice1, 2.6, Nmc);

  // Filename in which the energy and magnetization density is stored
  char energyValues3[] = "EnergyValues26.txt";
  char magnValues3[] = "MagnValues26.txt";


  //Starting the metropolis algorithm
  metropolis3.metroRun(ising1,lattice1, gen, energyValues3, magnValues3);

  std::cout << "Average e: " << metropolis3.averageE() <<  " Average M: " << metropolis3.averageM() << '\n';
  std::cout << "c = " << metropolis3.specific_heat() << " x = " << metropolis3.magnSuscept() << '\n';
  std::cout << '\n';
}
