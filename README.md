A branch predictor written in C++, 
that accepts an abbreviated memory trace file as an input, 
then simulates seven different branch prediction techniques on it. 

The input to the branch predictor has to be an abbreviated memory trace file. Each line in the trace file should be composed of:

1) The address of the branch instruction itself (branch address)
2) The address the branch would go to if the branch were taken (branch target) 
3) and a flag indicating if the branch was taken (T) or not (N).

As an example, consider the following three lines:

48d237 48d220 N
48d244 48d1fb N
48be4b 48bec0 T

indicate that there was a branch instruction at address 0x48d237, but the branch was not taken,
followed by a branch instruction at address 0x48d244, which was also not taken, 
followed by a branch instruction at address 0x48be4b, which branched to address 0x48bec0.

The addresses are in hexadecimal 
and may be up to 16 characters long (64 bit addresses). 

For each trace file given to the predictor, it simulates the following branch prediction techniques:

1) Static branch prediction [STA]
2) Branch address hash [BAH]
3) Target address hash [TAH]
4) Branch and target address hash [BTA]
5) Branch address hash with collision detection [COL]
6) Saturation counter [SAT]
7) Two level branch prediction [TWO]
