# C++ Multithreading Approximation of Pi 

This project demonstrates a Monte Carlo simulation to approximate the value of PI using parallel processing. The simulation generates random coordinates within a unit square and checks how many fall within the unit circle. The ratio of the number of points inside the circle to the total number of points is used to estimate the value of PI.

![Monte Carlo method](https://i.imgur.com/VMYfWrm.gif)


## Features

- **Parallel Processing**: The program uses OpenMP to parallelize the generation of random points and calculation of the hypotenuse.
- **Random Number Generation**: Utilizes the Mersenne Twister algorithm for random number generation to ensure high-quality randomness.
- **Performance Measurement**: The program measures and outputs the total runtime, providing insight into the efficiency of the parallelization.

## Getting Started

### Prerequisites

To compile and run this project, you will need:

- OpenMP is more suitable with Windows, a VM can be used if working with other OS.
- Standard C++ libraries (iostream, vector, random, chrono).
- Understand how many threads does your system support. 

### Compiling


```bash
g++ -fopenmp -o monte_carlo_pi monte_carlo_pi.cpp
```

### Running

```bash
./monte_carlo_pi
```

You will be prompted to enter the number of coordinates and the number of threads to use for the parallel processing.

_Inputting a higher number of coordinates will increase accuracy, while more threads will increase performance._

### Example

```bash
Enter number of coordinates: 1000000
Enter number of threads: 4
Total run time: 123456 microseconds
PI approximated at 3.14159
```
