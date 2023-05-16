# CirculantGenerator

## Software solution for searching for optimal and quasioptimal circulant topology graphs 

src - source code  
data - optimal circulant graphs  
qdata - quasioptimal circulant graphs

## Input format

On the command line, the input line is **\<V\> \<K\>** \<qr\> \<q_amount\>  

By default, an optimal graph of dimension **K** with **V** vertices is searched. Flag **q** enables search for quasioptimal graphs, flag **r** enables search among ring circulants. To specify the number of quasi-optimal graphs to search for, enter the value **q_amount**.

**V** and **K** are necessary parameters. 

If the query is incorrect, the message "Incorrect query" will be displayed.

**!q** terminates the software.

## Output format

The result is saved in the appropriate folder in the directory **dimK(r)** with filename **K(r)_V.csv**.

The .csv file contains the fields Vertices, Gen set, Diameter, Average distance, Bisection width, Connections.  
The results for quasioptimal graphs are ordered by increasing average distance and diameter.

A message with the filepath is displayed after saving the file.

