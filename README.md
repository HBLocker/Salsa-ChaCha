

# Salsa20 and ChaCha


Lightweight implemetation of both Salsa20 and ChaCha:
I chose theese algrithms as they seemed fun to implement.




Salsa20s quarter round is stated as follows:

    b ^= (a+d) <<< 7;
    c ^= (b+a) <<< 9;
    d ^= (c+b) <<< 13;
    a^= (d+c) <<< 18;

 ChaCha is as follows
 
    a += b; d ^= a; d <<<= 16;
    c += d; b ^= c; b <<<= 12;
    a += b; d ^= a; d <<<= 8;
    c += d; b ^= c; b <<<= 7;

Reffrences:
D. J. Bernstein. (NA). The Salsa20 core. Available: http://cr.yp.to/salsa20.html. Last accessed NA.

Jean-Philippe, et al (2007)  New Features of Latin Dances:Analysis of Salsa, ChaCha, and Rumba

 Daniel J. Bernstein.(na)   ChaCha a varient of Salsa20  
  
