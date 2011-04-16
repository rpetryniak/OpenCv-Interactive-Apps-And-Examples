#include <math.h>

int dist(int x1, int y1, int x2, int y2){
  int dx = x1 - x2;
  int dy = y1 - y2;
  int result = sqrt(dx * dx + dy * dy);
  return result;
}

inline const char*  getCmdOption(const char * name, const char * defaut, const int argc, const char *const * argv)
{
  const char *res = 0;

  if (argc>0) {
    int k = 0;
    while (k<argc && strcmp(argv[k],name)) ++k;
    res = (k++==argc?defaut:(k==argc?argv[--k]:argv[k]));
  } else res = defaut;

  return res;
}
