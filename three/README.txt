Build Instructions
==================
% mkdir build
% cd build
% cmake ..
% make install

Compilen and Run
==================
% cd build
% make clean install
% cd ..
% ./inst/a3 <parameters>

How to use
==================
TimeStepper:
1. e--ForwardEuler
2. t--Trapezoidal
3. r--RK4

To run a simpleSystem:
% ./inst/a3 s e|t|r <stepsize>

To run a pendulumSystem
% ./inst/a3 p <numTotalParticle> <IndexParticle> e|t|r <stepsize>
//IndexParticle is the index of the particle that we want to see the springs connect to. 
//The fixed point is origin

To run a clothSystem
% ./inst/a3 c <GridSize> e|t|r <stepsize>
//The cloth is a square. 
//To toggle render of cloth, hit 'r'
//To toggle movement, hit 's'

//For step size, I used 0.01 when implementation


-No Collaborator
-No reference except Piazza
-No problem with the code
-No extra credit (Would you consider the movement as extra credit?)
-The assignments are really interesting! I like it! Thanks!
