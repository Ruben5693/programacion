#include <cmath>
#include "mramd.h"
_mseed_type __mSeed__;
double NormalRand( double mean, double s )
{
  static double V1, V2, S;
  static int phase = 0;
  double X;

  if ( phase == 0 )
  {
    do
    {
      V1 = UniformRand();
      V2 = UniformRand();
      S = V1 * V1 + V2 * V2;
    }
    while ( S >= 1 || S == 0 );

    X = V1 * std::sqrt( -2 * std::log( S ) / S );
  }
  else
    X = V2 * std::sqrt( -2 * std::log( S ) / S );
  phase = 1 - phase;

  return mean + X * s;
}
