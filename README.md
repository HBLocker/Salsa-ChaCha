I am enjoying cryptography as it is a subject which I have always loved and found fascinating how data can be scrambled. Having worked with post QR. It has made my passion for this subject much stronger. Here are some examples of algs I have implemented based on their papers. 
<p>
                   <h1> ---Salsa--- </h1>
 Once I can roughly see how the bits have been shifted this kind of then is easy to picture in my head. Denoted in the papers SALSA works like this: a 64bit input x to salsa is split into 16bit in the words function. which is then xord to 32bits. The words are split by positive and negative, meaning than are one-off or opposite
each other. This is where the name salsa comes from, as the dance mirrors one another. 
  
</p>

<p>
                  <h1>    ---ChaCha---  </h1>
ChaCha works much the same as Salsa. but this one uses 4 additions,xors and rotations per full rotation. a shown in the code, there is very little changes to create the ChaCha.
</p>
ChaCha, a variant of Salsa20(Daniel J. Bernstein) https://cr.yp.to/chacha/chacha-20080128.pdf

               <h1>     ---Blowfish---   </h1>

Blowfish is noting like both salsa and chacha:

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


Ref (Bruce Schneier)https://www.schneier.com/academic/blowfish/ 


