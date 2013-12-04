Matching_Point_Sets
===================

Term Project for Advanced Algorithms

Given two 2d point sets P and Q and a real number alpha in [0,1].
Let P = {p_i: i=1,2,...,m} and Q = {q_j: j=1,2,...,n}.
Let r = radius of the largest circle such that if we consider the circles of radius r 
centered at points of P, then they do not intersect each other in their interiors.
Let C_i be the circle of radius r and centered at point p_i.
A point q_j of Q is said to match a point p_i of P if only the point q_j of Q lies inside C_i
(and no other point inside C_i).

Let k = floor (alpha.min(m,n)).
Q is said to match P if k points of Q are found to match with k points of P in the aforesaid manner.
Find the match, if any.

Output should be a single image containing: 

-- All points p_i in blue.
-- Each point q_j in red if it matches some point p_i. 
   Show this C_i in blue.
-- All non-matched points of Q in yellow.

You have to save the output as an image in svg format:
http://www.w3schools.com/svg/


HOW TO:

To run the program type following :$ bash setup.sh

INPUT FOR RANDOM NUMBERS:
m (Number of points of P)
n (Number of points of Q)
alpha (as specified in question)

INPUT FROM FILE:
The first line of input contains a two integer(m,n) and a double(a).
Next line contains 4 space seperated positive doubles, minX maxX minY maxY.
m is number of points in P set. n is number of points in Q set. a is alpha
Next m lines contain 2 space seperated doubles px, py denoting a point in P set.
Nest n lines contain 2 space seperated doubles qx, qy denoting a point in Q set.

OUTPUT:
The svg image in gnuplot as required.

PROCESS:
A randomized set of point-sets P and Q of the specified sizes will be generated. The range of the floating point co-ordinates is between 0 and 800. 

Thereafter, the distance between the closest pair of points in P is evaluated in O(mlog(m)) time using the divide and conquer algorithm. The required common radius of the largest non-overlapping circles is half of this.

