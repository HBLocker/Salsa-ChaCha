# Salsa-ChaCha
I decided to implement salsa and ChaCha as cryptography is something which I find very interesting, ocne I can roughly see how the bits have been shifted this kind of then is easy to picture in my head. 
Denoted in the papers SALSA works like this:
a 64bit input x to salsa is split into 16bit in the words function. which is then xord to 32bits. 
The words are split by postive and negitive, meaning then are one off or oppisite each other. 
This is where the  name salsa comes from, as the dance mirrios one another. 
The rotations are all constant valeus. Each round is a quartor round which modies one full word per round. 

---ChaCha---
ChaCha works much the same as Salsa. but this one uses 4 additions,xors and rotations per full rotation. a sshown in the code, there is very little changes to create the ChaCha.

ChaCha, a variant of Salsa20(Daniel J. Bernstein) 
https://cr.yp.to/chacha/chacha-20080128.pdf
