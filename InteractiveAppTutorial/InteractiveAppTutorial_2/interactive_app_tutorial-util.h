#ifndef UTIL_H
#define UTIL_H

static Scalar randomColor(RNG& rng)
{
  int icolor = (unsigned)rng;
  return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

#endif
