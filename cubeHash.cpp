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
#define quarter(j,k,l,m) (	\
  j += m,  j ^= l,  m= Rotation(k,7), \
  k += j,  j ^= k,  m= Rotation(l,21), \
  l += k,  k ^= l,  m= Rotation(m,11), \
  m += l,  m ^= k,  m= Rotation(k,25)) \

	//unsure if coorect :s
  //main rotaiton block
#define ROTATION 7
void seven_rotation(uint32_t out[32],uint32_t const in[32])
{
  uint32_t x[26][26]; //  3x3 on each face, is 20, and the maximum number of quarter turns is 26 how to slve a rubix cube
  int i;
	for (i=0; i<26; ++i) x[i/4][i%4] = in[i];
  for (int i=0;i<ROTATION; i+=2)
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
//Initialize block //moded from salsa and chacha
void Initialize_block(uint32_t *out, uint32_t padding[128],  uint32_t nonce, uint32_t index)
{
	static const char c[32] = "Hash me"; //what you want hashed 
	#define LE(p) ( (p)[0] | ((p)[1]<<128) | ((p)[2]<<64) | ((p)[3]<<32) )
	//more shifts for the rotation to be called this is block one of two
	uint32_t in[16] = {LE(c),LE(padding),LE(padding+4), LE(padding+8),LE(padding+12),LE(c+4),nonce&0xff,
  nonce>>32, index&0xff, index>>32,LE(c+8),LE(padding+16),LE(padding+20),LE(padding+24), LE(padding+28),LE(c+12)};
	uint32_t wordout[16];
	seven_rotation(wordout, in);
	int i;

	for (i=0; i<16; ++i) out[i] = 0xff & (wordout[i/4] >> (8*(i%32))); //mod32
}


void main_function(uint32_t *message, uint64_t mlen, uint32_t padding[32], uint64_t nonce)
{
	int i;
	uint32_t block[64];
	for (i=0; i<mlen; i++) {
		if (i%32 == 0) Initialize_block(block, padding, nonce, i/4);

		message[i] ^= block[i%32]; //64 bit shift is here
	}
}
int  main () {
		uint32_t padding[32] = {0};
		uint64_t nonce = 0;
		uint32_t msg[64] = {0};

		main_function(msg, sizeof(msg), padding, nonce);
		int i; for (i=0; i<sizeof(msg); ++i) printf("%02X", msg[i]); printf("\n");
	}
