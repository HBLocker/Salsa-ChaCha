

# Salsa20 and ChaCha


Lightweight implemetation of both Salsa20 and ChaCha:
I chose theese algorithms as they seemed fun to implement.




## Salsa20s quarter round is stated as follows:

    b ^= (a+d) <<< 7;
    c ^= (b+a) <<< 9;
    d ^= (c+b) <<< 13;
    a^= (d+c) <<< 18;


## salsa output
need to debug later  
##  ChaCha is as follows
 
    a += b; d ^= a; d <<<= 16;
    c += d; b ^= c; b <<<= 12;
    a += b; d ^= a; d <<<= 8;
    c += d; b ^= c; b <<<= 7;


## ChaCha output:
this is a wokring example
10D41590280E5481833E289AA47BF0EF0B682D6C2FC59D8BEC0D41A33F1BC3764DB91E2DE747F54FF514A89DFBFBA4DD906FCD1ABFB82508A2996E67D2931DE5E55C2D9DB3F571300F5DD225C590A30AB3B8B289ED5579ECF5108770EF889734E405FE3E84D04723DDB8041B81FFD172417A999A1FF002CB204E56A1E627CA3D8CFAE199A9EBA18A678E0508F99BE3CF3A6BA8E5A23360D5F14BFA8BCB4400F353548AFFB805BD1F715C1348B3121D5CF6597FBD8D84E4336EC61BB1B46C49DE59FE0D4DF1EC82526A6B9225EBA53DD8830EA028D0532C1981F8DDA3D2208E642ADB9FD2A52DCD3C3F1BC4003F505FEF729E68B86C0CC7419DECB020B04AB37D


## How to run
g++  -o NameOfOutfile -w filename.cpp 
Then run ./NameOfOutfile 

Type whatever you want to see it working. 


## Reffrences:
D. J. Bernstein. (NA). The Salsa20 core. Available: http://cr.yp.to/salsa20.html. Last accessed NA.

Jean-Philippe, et al (2007)  New Features of Latin Dances:Analysis of Salsa, ChaCha, and Rumba

 Daniel J. Bernstein.(na)   ChaCha a varient of Salsa20  
  
