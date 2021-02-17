#include <stdio.h>
#include <stdint.h>
#include <iostream>
//papers denoted rotation in section
#define Rotation(x,n) (((x) << (n)) | ((x) >> (32-(n))))
//rotation  https://stackoverflow.com/questions/29676648/explaining-method-x-n-x-32-n
#define quarter(a, b, c, d) (			\
	a += b,  d ^= a,  d = Rotation(d,7),\
	c += d,  b ^= c,  b = Rotation(b,9),\
	a += b,  d ^= a,  d = Rotation(d,13),\
	c += d,  b ^= c,  b = Rotation(b,18))
#define ROUNDS 20	//ref https://tools.ietf.org/html/rfc7539 1.1 see rounds for define
//taken from https://cr.yp.to/salsa20.html
void main_chacha_word(uint32_t out[16],uint32_t const in[16])
{
	uint32_t x[4][4];
	int i;
	for (i=0; i<16; ++i) x[i/4][i%4] = in[i];

	for (i=0; i<10; ++i)
  for (i =0;i <ROUNDS;i +=2)
  {
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
	}
	for (i=0; i<16; ++i) out[i] = x[i/4][i%4] + in[i];
}
//transformation fothe block mentioend in https://eprint.iacr.org/2007/472.pdf
//salsa takes in 32bit words, and a 256bit key,64bit nonce value.
void main_block(uint8_t *out, uint8_t key[32], uint64_t nonce, uint64_t index)
{
	//stattic const to stop change of vlaue.
	static const char c[16] = "0xff";
	//an attempt at the "quarterround" function, which is used for SALSA20
	//bellow is a shit to the right for the values
	#define LE(p) ( (p)[0] | ((p)[1]<<8) | ((p)[2]<<16) | ((p)[3]<<24) )
	uint32_t in[16] = {LE(c),LE(key),LE(key+4), LE(key+8),LE(key+12),LE(c+4),nonce&0xff,
  nonce>>32, index&0xff, index>>32,LE(c+8),LE(key+16),LE(key+20),LE(key+24), LE(key+28),LE(c+12)};
	uint32_t wordout[16];
	main_chacha_word(wordout, in);
	int i;
	for (i=0; i<64; ++i) out[i] = 0xff & (wordout[i/4] >> (8*(i%4)));
}
void salsa20_main_function(uint8_t *message, uint64_t mlen, uint8_t key[32], uint64_t nonce)
{
	int i;
	uint8_t block[64];
	for (i=0; i<mlen; i++) {
		if (i%64 == 0) main_block(block, key, nonce, i/64);
		message[i] ^= block[i%64]; //64 bit shift is here
	}
}
int  main () {
	uint8_t key[32] = {0};
	uint64_t nonce = 0;
	uint8_t msg[256] = {0};
	std::cin>>msg;

	salsa20_main_function(msg, sizeof(msg), key, nonce);
	int i; for (i=0; i<sizeof(msg); ++i) printf("%02X", msg[i]); printf("\n");
}
