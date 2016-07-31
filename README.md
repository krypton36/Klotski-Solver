# Klotski Puzzle Solver
<br/>
### To Compile and Run p1:
% make<br/> 
% ./p1 1<br/> 
1 - Initial Position<br/> 
2 - Case one<br/> 
3 - Case two<br/> 
<br/> 
% ./p1 -(Valid Board Position)<br/> 
<br/> 
###Clean up:
% make clean<br/> 
<br/> 
<br/> 
-----------------------------------------------------------------------
Introduction
-----------------------------------------------------------------------
This program will solve the Klotski puzzle given any valid position.
The program will take a position and solve from it using the Breadth
First algorithm and the out put the shortest path. Each letter corresponds
the given piece and the position is placed on the topmost leftmost position
of the board.

The Board is 5 columns  and 4 rows:
 A = 2 column block and 1 row block.
 B = 1 column black and 2 row block.
 C = 2 column block and 2 row block.
 D = 1 column block and 1 row block.
 E = 1 column block and 1 row block. (Empty)

Initial position: AADCBDEDEAAD
Solution position: ABDDACADADEE



-----------------------------------------------------------------------
NOTE about p1
-----------------------------------------------------------------------
If the position given is not a valid position, it will cause the
program to malfunction.
