# Covid Contact Tracing
## By: Avi Fischer and Sudarshan Maramganty
This is a contact tracing program that stores information about contacts the people during the coronavirus pandmeic. It stores these contacts in graphs and stores information about where they occured, when they occured and wether or not the people involved are positive for coronavirus.

# How to Run
To compile the code and run the test cases call:
```
g++ ./main.cpp
./a.exe
```
or use your favourite IDEs build function. The code will attempt to print emojies to communicate the results of the test cases which depending on you terminal may or may not actually be printed.

# Graph Representation
The Graph object stores a vector of GraphNodes.

# GraphNodes
Each GraphNode is a struct that stores strings that represent the person's ID, first name and last testing date and a boolean the represents whether they are Covid positive. Each node also has three arrays, one stores pointers to it's connected nodes, one stores the number of days since the last contact and one stores the meeting locations.

# File Storage
This program can store graphs and read them in text files. The files contain one node per line and individual values are seperated by commas. The connections of a node are listed after the values. There are three attributes of connections, the node being connected to, the days since meeting and the location. For each node, connection details are listed after the attributes, but only if the connected node is defined previously in the file. When a node is added to the graph, nodes that it is connected to are modified to contain a link to it. Each line of the file must end in a comma or the program will loop infinitely.
