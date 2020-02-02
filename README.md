# lem_in
42 Algorithm project

![oops something went wrong, try to check on https://raw.githubusercontent.com/ldedier/lem_in/master/resources/lemin.gif](https://raw.githubusercontent.com/ldedier/lem_in/master/resources/lemin.gif)

This project is about getting through an unweighted graph with N ants with these constraints:

* there can't be 2 ants on the same node at the same time (except for the starting/ending node)
* ants must take as few turns as possible to all get to the end

## Maps

Maps are text files describing this structure:

```
N
##start
room1 X1 Y1
room2 X2 Y2
room3 X3 Y3
##end
room4 X4 Y4

room1-room2
room1-room4
room2-room3
room3-room4
```

* N describes the number of ants
* room1 is the starting room 
* room4 is the ending room 
* The links between rooms are the hyphen lines ("-")

## Result

The result of the program is the repeat of the map on standard output, followed by the progress of ants at each turn in this format:

```
L1-room3 L2-room2
```

where LN describes the number of the ant, going toward its next room

## Bonus

A program called lem-in_visu should be piped directly to the output of the program and provides a graphic interface to show the progress of the ants

## Usage

* ./lem-in < mapAsFileName
* ./lem-in < mapAsFileName | ./lem-in_visu
