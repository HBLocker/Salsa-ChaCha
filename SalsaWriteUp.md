# Salsa how it works

After I think two years ago I wrote these, I deviced to come back and write an overvew of how they work. 

Salsa20 is a modern and quick stream cipher, it was developed in 2005 by Bernstine who is a professor at the university of Illinois. 


The input to the function is the secret key, which can be 32 or 16 bytes long, an 8-byte long nonce concatenated with an additional block number.  The values change from 0 to 264-1 Every call to the expansion function increases the block number by one.


The main part of the algorithm is its hash functon which takes a 64 byte long imput data from the salsa20 expansion funciton and jumbles it up which will return a 64byte long ouput:
````
7439AC2BB218D2A395D7E87055BFEC43A8A7156399DAB60AE69960D0C1B43A72411E7BD535B8CF4598A568277BBF75D84344C39F450AC79B3C65279803FE04E8D690C494F71069BA879FC046156D11BD115B009CCA1FF5F2F2277DBAEA2D3760D54A8DD33C77529427FD945C41266EF22511865DCFE8ECAD4C7F253D24CEA2000547AB194E8135ED42891A905A884016F909E0DA6565FE590A9D3526D2EC7A3A857E67302755FEBE2BA179A9327D99E576D63C941B7E067E5E703663F6F4FD82B58B27FA798E7879C695ABCBDBA0D609DE330B96FD1448AE6DB81B0BE422745E8CE8DFBACE18DFE381B2E74A0EE0499024D010BB7FDA85D0E6B169FD0CDBD91B
````




#### Compressed explanation of Salsa20 specification.


The algorithm has three main parts to it:
- 32 bit addition preducing the sum of a + b Mod 32 of two 32 bit words a and b. 
-  32 bit XOR of a and b 
-  32 bit rotation of a and b shifting the bits to the left, a << b where b is constant. 

````
b ^= (a+d) <<< 7;
c ^= (b+a) <<< 9;
d ^= (c+b) <<< 13;
a^= (d+c) <<< 18;
````

#### Rowround function 


takes in 16 words as a imput and returns a 16 word sequence. 

Definition
```
If X is a 16 word input:
X = (x0,x1,x2 ..... x15)
Rowround(x) = (y0,y1,y2,y3,....y15)

(y0, y1, y2, y3) = quarterround(x0, x1, x2, x3)
(y5, y6, y7, y4) = quarterround(x5, x6, x7, x4)
(y10, y11, y8, y9) = quarterround(x10, x11, x8, x9)
(y15, y12, y13, y14) = quarterround(x15, x12, x13, x14)
```
#### columnround function 

The Columnround Function takes 16 words as input and returns 16-word sequence.
`````
If x is a 16-word input:
    x = (x0, x1, x2, ..., x15)
Then the function can be defined as follow:
columnround(x) = (y0, y1, y2, ..., y15)
Where 
(y0, y4, y8, y12) = quarterround(x0, x4, x8, x12)
y5, y9, y13, y1) = quarterround(x5, x9, x13, x1)
(y10, y14, y2, y6) = quarterround(x10, x14, x2, x6)
(y15, y3, y7, y11) = quarterround(x15, x3, x7, x11)

`````

#### Doubleround Function

This takes in 16 words as imput and returns a 16 word sequance. 
````
A double round is a column round followed by a row round:
doubleround(x) = rowround(columnround(x))
````

#### Littleendian Function

If b is a 4-byte sequence then littleendian(b) is a word.
````
If b = (b0, b1, b2, b3) then littleendian(b) b0 +b1+b2+b3
````

#### Salsa20 Hash Function
If x is a 64-byte sequence then Salsa20(x) is a 64-byte sequence.
````
In short: Salsa20(x) = x + doubleround10(x), where each 4-byte sequence is
viewed as a word in little-endian form

Then the 16 words are modified by 10 interations of the double round function.
(x0, x1, ..., x15) = doubleround10(w0, w1, ... w15)

Now the 16 words are recived as imput and ae added to the 15 words changed to 64 new bytes using the Littleendian Function. 
````
#### Expansion Function

If k is a 32-byte or 16-byte sequence and n is a 16-byte sequence then Salsa20k(n)
is a 64-byte sequence
````
 Salsa20Expansionk   = Salsa20Hash(a0, k0, a1, n, a2, k1, a3)
  a1 = (101, 120, 112, 97)
  a2 = (110, 100, 32, 51)
  a3 = (50, 45, 98, 121)
  a4 = (116, 101, 32, 107)
 ````
 
 
If the first sequence is 16-bytes long K.  Salsa20 Expansion  is defined by using the Salsa20 Hash function.

````
Salsa20(τ0, k, τ1, n, τ2, k, τ3)
where 
  a1 = (101, 120, 112, 97)
  a2 = (110, 100, 32, 51)
  a3 = (50, 45, 98, 121)
  a4 = (116, 101, 32, 107)
 
````
