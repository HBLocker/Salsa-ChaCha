//64bit cipher
//cipher two parts
//part A -> Key_expansion into sevral keys.
//http://www.naturalspublishing.com/files/published/359vv11fyaeh31.pdf
//F(XL) = ((S1,a+S2,bmod232)X OR S3,c)+S4,dmod232
#define  MAXBYTES 56
#define N 16
typedef struct {
  uint32_t P[16+2]; //max 32 bits but used per round  ref fig 1 
  uint32_t S[4][256];   
}BLOWFISH_ALG; 

unsigned long F(BLOWFISH_ALG*ctx,uint32_t x) //denoted in 2.2 
{
  uint32_t a,b,c,d; 
  uint32_t y; 
  //BITWISE 
  d = x & 0x00F; // d = x and 0 
  x >>=8; //32 bit int sidt to 8
  c = x & 0x00FF;
  x >>= 8;
  b = x & 0x00FF;
  x >>= 8;
  a = x & 0x00FF; 
  ///////KEY EXPANSION ROUND HERE 
  y = ctx->S[0][a] + ctx->S[1][b];
  y = y ^ ctx->S[2][c];
  y = y + ctx->S[3][d];  
   return y; 
}
//encryption function here 





/*
Data: Plaintext (64 bits) and P1, P2, , P18
Result: Ciphertext (64 bits)
Divide plaintext into two 32-bit halves: XL , XR;
fori=1 to 16do
    Calculate XL = XL XOR Pi;
    Calculate XR = F(XL) XOR XR
    Swap XL and XR (undo the last swap)
    end
Calculate XR = XR XOR P17
Calculate XL = XL XOR P18;
Recombine XL and XR (ciphertext)
  


*/
