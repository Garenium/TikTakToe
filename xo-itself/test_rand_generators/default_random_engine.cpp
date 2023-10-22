#include <iostream>
#include <random>

int main() {
    std::random_device rd;  // Initialize a random device to provide seed
    std::default_random_engine generator(rd());  // Create a random number generator with a random seed
    std::uniform_int_distribution<int> distribution(0.0, 1.0);  // Define the range [0, 1]

    int random_number = distribution(generator);  // Generate a random number between 0 and 1
    std::cout << "Random number between 0 and 1: " << random_number << std::endl;

    return 0;
}
