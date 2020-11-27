// based from the follwing paper
//https://pdfs.semanticscholar.org/3ebf/2fe53c0b245520b8b4da37996fb895de3c79.pdf
//https://cr.yp.to/snuffle/design.pdf
//slaa20 256-bit stream cipher alg
//salsa contains three main functions:
// 32 bit addition = a+b mod^32
//https://en.wikipedia.org/wiki/Salsa20
//https://cr.yp.to/salsa20.html
#include <stdio.h>
#include <stdint.h>
//papers denoted rotation in section
#define Rotation(x,n) (((x) << (n)) | ((x) >> (32-(n))))
//rotation  https://stackoverflow.com/questions/29676648/explaining-method-x-n-x-32-n
#define quarter(a,b,c,d) do {\
	b ^= Rotation(d+a, 7);\
	c ^= Rotation(a+b, 9);\
	d ^= Rotation(b+c, 13);\
	a ^= Rotation(c+d, 18);\
} while (0)
//taken from https://cr.yp.to/salsa20.html
void main_salasa_word(uint32_t out[16],uint32_t const in[16])
{
	uint32_t x[4][4];
	int i;
	for (i=0; i<16; ++i) x[i/4][i%4] = in[i];
	for (i=0; i<10; ++i)
	{
		//20 rounds
		quarter(x[0][0], x[1][0], x[2][0], x[3][0]); //even values
		quarter(x[1][1], x[2][1], x[3][1], x[0][1]);
		quarter(x[2][2], x[3][2], x[0][2], x[1][2]);
		quarter(x[3][3], x[0][3], x[1][3], x[2][3]);
		//////////////////////////////////////////////
		quarter(x[0][0], x[0][1], x[0][2], x[0][3]); 	// odd values
		quarter(x[1][1], x[1][2], x[1][3], x[1][0]);
		quarter(x[2][2], x[2][3], x[2][0], x[2][1]);
		quarter(x[3][3], x[3][0], x[3][1], x[3][2]);
	}
	for (i=0; i<16; ++i) out[i] = x[i/4][i%4] + in[i];
}
//block takes in the tranformed text,
void salsa20_Block(uint32_t *message, uint64_t mlen, uint32_t key[32], uint64_t nonce)
{
#define LE(p) ( (p)[0] | ((p)[1]<<8) | ((p)[2]<<16) | ((p)[3]<<24) )
uint32_t in[16] =
{
LE(c), LE(key),LE(key+4),LE(key+8),LE(key+12), LE(c+4), nonce=0x01A4, nonce >>32,
index&0xffffffff, index>>32,  LE(c+8), LE(key+16),LE(key+20), LE(key+24), LE(key+28),LE(c+12)};
//takes key values incs up plus the nonce value (rnaodm) then does the shift asdenoted by the creator
uint64_t word_out[16];
//return
main_salasa_word(word_out,in);
int i;
for (i=0; i<64; ++i) out[i] = 0xff & (wordout[i/4] >> (8*(i%4))); //255 max value & wordout /64/4 hashed with 64 modlo *8 
}

}

//main void goes here
