#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>
#include <iomanip>  //for setprecision

using namespace std;

static Scalar randomColor(RNG& rng)
{
  int icolor = (unsigned)rng;
  return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

int dist(int x1, int y1, int x2, int y2){
  int dx = x1 - x2;
  int dy = y1 - y2;
  int result = sqrt(dx * dx + dy * dy);
  return result;
}

string toString(double value, int precision){
  stringstream sstr;
  sstr << fixed << setprecision(precision) << value;
  return sstr.str();
}

//--------------------------------------------------
string toString(int value){
  stringstream sstr;
  sstr << value;
  return sstr.str();
}

#endif
