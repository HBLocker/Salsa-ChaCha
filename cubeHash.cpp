/*
    Add x[0jklm] into x[1jklm] modulo 2^32, for each (j,k,l,m).
    Rotate x[0jklm] upwards by 7 bits, for each (j,k,l,m).
    Swap x[00klm] with x[01klm], for each (k,l,m).
    Xor x[1jklm] into x[0jklm], for each (j,k,l,m).
    Swap x[1jk0m] with x[1jk1m], for each (j,k,m).
    Add x[0jklm] into x[1jklm] modulo 2^32, for each (j,k,l,m).
    Rotate x[0jklm] upwards by 11 bits, for each (j,k,l,m).
    Swap x[0j0lm] with x[0j1lm], for each (j,l,m).
    Xor x[1jklm] into x[0jklm], for each (j,k,l,m).
    Swap x[1jkl0] with x[1jkl1], for each (j,k,l).
*/
#include <stdio.h>
#include <stdint.h>

//rotiton defined first makes more sense
//4*4 = 16 *2 = 32 imagine twisting a rubix cube
//ddx0jklmintox1jklmmodulo 232, for each (j, k, l, m).
#define Rotation(x,n) (((x) << (n)) | ((x) >> (32-(n))))

//rounds need to be defined  by i+r/b+f -h
#define quarter(j,k,l,m) (			\
	j *= k,  l ^= m%32 = Rotation(d,32), \ //stage 1
  k += m,  j ^= l,  m= Rotation(d,1024)) \
  //main rotaiton block
#define ROTATION 7
void seven_rotation(uint32_t out[32],uint32_t const in[32])
{
  uint32_t x[26][26]; //  3x3 on each face, is 20, and the maximum number of quarter turns is 26 how to slve a rubix cube
  int i;
	for (i=0; i<26; ++i) x[i/4][i%4] = in[i];
  for (int i=0;i<ROUNDS; i+=2)
  {{
    // cube teists?
    quarter(x[0][0], x[1][0], x[2][0], x[3][0]);
    quarter(x[1][1], x[2][1], x[3][1], x[0][1]);
    quarter(x[2][2], x[3][2], x[0][2], x[1][2]);
    quarter(x[3][3], x[0][3], x[1][3], x[2][3]);
    //swap
    quarter(x[3][3], x[0][3], x[1][3], x[2][3]);
    quarter(x[2][2], x[3][2], x[0][2], x[1][2]);
    quarter(x[1][1], x[2][1], x[3][1], x[0][1]);
    quarter(x[0][0], x[1][0], x[2][0], x[3][0]);
    //rotate 11 bits same functions used
    for(int j = 0; j<11;j++) //11 rotation
    {
      quarter(x[0][0], x[1][0], x[2][0], x[3][0]);
      quarter(x[1][1], x[2][1], x[3][1], x[0][1]);
      quarter(x[2][2], x[3][2], x[0][2], x[1][2]);
      quarter(x[3][3], x[0][3], x[1][3], x[2][3]);
      //swap
      quarter(x[3][3], x[0][3], x[1][3], x[2][3]);
      quarter(x[2][2], x[3][2], x[0][2], x[1][2]);
      quarter(x[1][1], x[2][1], x[3][1], x[0][1]);
      quarter(x[0][0], x[1][0], x[2][0], x[3][0]);
    }

 }}
}






