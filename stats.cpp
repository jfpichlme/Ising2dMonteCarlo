#include <vector>
#include <iostream>
#include "stats.h"
#include <math.h>
using namespace std;




double average(vector<double> &data, int start){
double total = 0;

  for (unsigned i=start; i<data.size();i++){
      total += data.at(i);
  }
  return total/(data.size()-start);
}


double standDev(vector<double> &data, int start){
  double avg = average(data, start);
  double s = 0;

  for (unsigned i = start; i<data.size(); i++){
    s += pow(data.at(i)-avg, 2);
  }

  double staDev = sqrt(s/(data.size()-start-1));
  return staDev;
}
