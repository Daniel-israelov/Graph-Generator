# Graph-Generator
C++ program to create Random Graphs according to a given Arrays of probabilities --> 3 different Arrays for 3 different attributes - Connectivity, Diamter, Isolated Vertex.

Values in the Array are chosen accroding to thresholds:

Threshold1 = Threshold3 = ln(v)/v.

Threshold2 = sqrt(2*threshold1).

Each Array has 10 values --> 5 values are smaller then the threshold & the other 5 are larger.

After creating a graph it will check 3 attributes:
1. Connectivity (att_indx = 1) --> Chekcs how many graphs are connected.
2. Diameter (att_indx = 2) --> Finds the diamter of a graph using BFS & counts how many graphs has diameter smaller or equal to 2.
3. Isolated Vertex (att_indx = 3) --> checks and counts how many graphs has at least 1 isolted vertex.

All results will be printed into a CSV file in 3 blocks at the same order above.

Each block has 2 rows:
1st row are the probabilities values and in the 2nd row under each probablilty there's the Assessment of the probability that the feature exists in the graph.
