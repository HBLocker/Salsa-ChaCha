// based from the follwing paper
//https://pdfs.semanticscholar.org/3ebf/2fe53c0b245520b8b4da37996fb895de3c79.pdf
//https://cr.yp.to/snuffle/design.pdf
//slaa20 256-bit stream cipher alg
//salsa contains three main functions:
// 32 bit addition = a+b mod^32
//https://en.wikipedia.org/wiki/Salsa20
#include <stdio.h>
##include <stdint.h>
//papers denoted rotation in section
#define Rotation(x,n) (((x) << (n)) | ((x) >> (32-(n))))
//rotation  https://stackoverflow.com/questions/29676648/explaining-method-x-n-x-32-n
#define quarter(a,b,c,d) do {\
	b ^= Rotation(d+a, 7);\
	c ^= Rotation(a+b, 9);\
	d ^= Rotation(b+c, 13);\
	a ^= Rotation(c+d, 18);\
} while (0)

//main void goes here
