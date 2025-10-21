
# MST Algorithm -> Fredman + Tarjan

A representation of the famous and very powerfull algorithm of the Minimum Spanning Tree (MST) of the two genius Fredman and Tarjan.
The algorithm consists in the utilization of the fibonacci heap to implement the priority queue, where your complexity of the Big O dont overpass the base of log.
Developed in ocurrency of the matter of graphs (Theory of Graphs), where is addressed the various ways to resolve the problem of the MST, but our algorithm is a litle bit faster than Prim's algorithm and Kruskal's.


## Authors

- https://github.com/GabrielPissininMenossi
- https://github.com/matheusmen1


## Documentation

The original article of the Tarjan and Freadman
[Documentation](https://www.cl.cam.ac.uk/teaching/1011/AlgorithII/1987-FredmanTar-fibonacci.pdf)


## Run Locally

Clone the project

```bash
  git clone https://github.com/matheusmen1/FredmanAndTarjanAGM.git
```

Go to the project directory

```bash
  cd FredmanAndTarjanAGM
```

Install dependencies

- Download Conio2.h to run the interface components, or... execute whithout the library conio2.h and the comands given by the library, like: textcolor(), getch(), gotoxy(), and more, is easy to find the comands that are used by the library conio2.h

- Download g++ if you dont have installed in your machine (linux normaly have by default some compiler by language C/C++)

- Link to download Conio2.h: https://sourceforge.net/projects/conio/

Compile your project

```bash
  gcc FredmanAndTarjan.cpp -o FredmanAndTarjan
```

Execute your file (linux)

```bash
  ./FredmanAndTarjan
```

Execute your file (windows)

```bash
  FredmanAndTarjan
```
