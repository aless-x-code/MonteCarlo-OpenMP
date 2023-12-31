#include <vector>
#include <iostream>
#include <random>
#include <omp.h>
#include <chrono>

using namespace std;

// functions generates random number: parameter mt(reference to generated random number), and uniform(ensures even probability of distribution for range of random number)
float rand_axis(mt19937& mt, uniform_real_distribution<float>& uniform)
{
    return uniform(mt);
}

int main()
{

    int num_threads = 0;
    int num_coordinates = 0;

    cout << "Enter number of coordinates: ";
    cin >> num_coordinates;
    cout << "Enter number of threads: ";
    cin >> num_threads;

    // initialize vectors
    vector<float> x;
    vector<float> y;
    vector<float> hypot;

    for (int i = 1; i <= num_coordinates; i++) { x.push_back(i); } // populate x vector
    for (int i = num_coordinates; i >= 1; i--) { y.push_back(i); } // populate y vector
    for (int i = 0; i < num_coordinates; i++) { hypot.push_back(x[i] + y[i]); } // populate hypotenuse vector


    auto start = chrono::high_resolution_clock::now(); // start timer

    // beging parallel processing
#pragma omp parallel num_threads(num_threads)
    {
        // private variables of each thread
        int myid = omp_get_thread_num();

        random_device seed; // create seed based on hardware
        mt19937 mt(seed()); // generate random based on Mersenne Twister
        uniform_real_distribution<float> uniform(0.0f, 1.0f); // uniform distribution in range

        // set equal segments of vector for each thread
        int mystart = myid * num_coordinates / num_threads;
        int myend = (myid + 1) * (num_coordinates / num_threads) - 1;

        for (int i = mystart; i < myend; i++) // threads push to vector ranges
        {
            x[i] = rand_axis(mt, uniform); // random x coordinate
            y[i] = rand_axis(mt, uniform); // random y coordinate
            hypot[i] = sqrtf(x[i] * x[i] + y[i] * y[i]); // puhs hypotenuse (square root - float type)
        }
    } // end of parallel processing
    auto stop = chrono::high_resolution_clock::now(); // stop timer

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);  // compute run time
    cout << "Total run time: " << duration.count() << " microseconds" << endl;

    float coord_inside_circle = 0.0;
    float p = 0.0;
    float pi = 0.0;

    for (int i = 0; i < num_coordinates; i++)
    {
        // if hypotenuse/distance is lower than one, then coordinate is inside the circle
        if (hypot[i] < 1)
            coord_inside_circle++;
    }
     
    p = coord_inside_circle / num_coordinates; // calculate ratio/probability
    pi = p * 4;

    cout << "PI approximated at " << pi << "\n";


    return 0;
}
