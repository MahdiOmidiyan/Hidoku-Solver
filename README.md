# Hidoku-Solver

A hidoku solver program for square and hexagonal cell written by mahdi omidiyan.

This Project is licensed under terms of the MIT license.

Input specifications should be listed in "matrix.dat" file as bellow :

First line )
"rect" or "hex" for type of table

Second line )
n m (n and m are numbers of rows and columns for rectangular table repectively, in case of hexagonal table with hexagonal cells only n should be specified for number of cells in each side of the table)

The following n lines )
each line has cell values of corresponding line in table with space separating them.
"0" indicates empty cell , "-1" is used for blocked cell which is not part of the desirable table ( The input table could be shaped other than perfect hexagon or rectangle) and other values starting from 1 for predefined cells.

"answer.dat" is created containing output cells in the same order as of input file just without separate line and blocked cells are ommited.
