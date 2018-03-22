#if !defined(mRAMD_H)
  #define mRAMD_H
  #define _BORLAND_RAND
  #ifdef _BORLAND_RAND
    #define MULTIPLIER      0x015a4e35L
    #define INCREMENT       1
  #endif
  #ifdef _VISUALC_RAND
    #define MULTIPLIER      0x343fdL
    #define INCREMENT       0x269ec3
  #endif

union _mseed_type
{
  unsigned int integer32[2];
  long long integer64;
};

#define ramd  _ramd
#define MRAND_MAX     0x7fff
//#define ramd  _lramd
//#define MRAND_MAX     0x7fffffff
inline void sramd( unsigned seed );
inline int _ramd( void );
inline long _lramd( void );
inline double UniformRand( double max, double min );
inline double UniformRand();
double NormalRand( double mean, double s );

inline void sramd( unsigned seed )
{
  extern _mseed_type __mSeed__;
  __mSeed__.integer32[0] = seed;
  __mSeed__.integer32[1] = 0;
  ramd();
}

inline int _ramd( void )
{
  extern _mseed_type __mSeed__;
  __mSeed__.integer32[0] = MULTIPLIER * __mSeed__.integer32[0] + INCREMENT;
  return ( ( int )( __mSeed__.integer32[0] >> 16 ) & 0x7fff );
}

inline long _lramd( void )
{
  extern _mseed_type __mSeed__;
  __mSeed__.integer64 = MULTIPLIER * __mSeed__.integer64 + INCREMENT;
  return((int)((__mSeed__.integer64>>16) & 0x7fffffffL));
  /*
  _EBX = __mSeed__.integer32[0];
  _ESI = __mSeed__.integer32[1];

  asm mov eax, ebx
  asm mov ecx, 015Ah
  asm mov ebx, 4E35h


  asm test eax, eax
  asm jz nohi1
  asm mul ebx

  nohi1 :
  asm xchg ecx, eax
  asm mul esi
  asm add eax, ecx

  asm xchg eax, esi
  asm mul ebx
  asm add edx, esi

  asm add eax, 1
  asm adc edx, 0
  asm mov ebx, eax
  asm mov esi, edx

  __mSeed__.integer32[0] = _EBX;
  __mSeed__.integer32[1] = _ESI;
  return _ESI & 0x7fffffff;
  */
}
inline double UniformRand() //產生-1~1之間的浮點亂數
{
  return ramd() * 2.0 / MRAND_MAX - 1.0;
}

inline double UniformRand( double max, double min )
{
  return ramd() * ( max - min ) / MRAND_MAX + min;
}

//================================================================================

#endif
