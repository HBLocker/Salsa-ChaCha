I am enjoying cryptography as it is a subject which I have always loved and found fascinating how data can be scrambled. Having worked with post QR. It has made my passion for this subject much stronger. Here are some examples of algs I have implemented based on their papers. 
<p>
  <center>    <h1> ---Salsa--- </h1> </center>
 Once I can roughly see how the bits have been shifted this kind of then is easy to picture in my head. Denoted in the papers SALSA works like this: a 64bit input x to salsa is split into 16bit in the words function. which is then xord to 32bits. The words are split by positive and negative, meaning than are one-off or opposite
each other. This is where the name salsa comes from, as the dance mirrors one another. 
  
</p>

<p>
  <center>      <h1>    ---ChaCha---  </h1>   </center>
ChaCha works much the same as Salsa. but this one uses 4 additions,xors and rotations per full rotation. a shown in the code, there is very little changes to create the ChaCha.
</p>

<p>
  
  
<p>
  <center>      <h1>    ---Cube Hash---  </h1>   </center>
 
different type of hash, but the codde was moded form Salsa and ChaCha why it is in this repo. So the code goes though many different swaps much like turning a cube. 
The rotation rounds can be seen going though the combiniaitons then each part is hashed and xord each time. I am not 100% if what i have done is correct, but the output looks close enough. 
</p>
<p>
  
  
  
ChaCha, a variant of Salsa20(Daniel J. Bernstein) https://cr.yp.to/chacha/chacha-20080128.pdf
CubeHash(Daniel J. Bernstein) https://cr.yp.to/chacha/chacha-20080128.pdf
               



