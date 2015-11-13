# Linear-Road-Benchmark-Data-Driver

## How to compile

1.Creating object files

```
g++ -pthread -g -c LRDataProvider.cpp MemTuples.cpp Tuple.cpp
```
2.Linking libraries
```
ar cru libLRDataProvider.a LRDataProvider.o MemTuples.o Tuple.o    				
ranlib libLRDataProvider.a
```
3.Compile yourCfile.cpp to yourCfile.o object file
```
g++ -c DataFeeder.cpp
```
4.Link DataFeeder.o to YourExecutedFileName (e.g.'myDataFeeder') by using:
```
g++ -o myDataFeeder DataFeeder.o -pthread libLRDataProvider.a
```
Make sure libLRDataProvider.a is always behind -pthread and other libaries

5.Run YourExecutedFileName by typing:
```
./myDataFeeder ./Data/datafile20seconds.dat
```
Reference: [Linear Road: Installation Guide: Data Driver](http://www.cs.brandeis.edu/~linearroad/datadriverinstall.html)