#include <iomanip>
#include <iostream>
#include <limits>
#include <chrono>

// Allow to change the floating point type
using my_float = long double;

my_float pi_taylor(size_t steps) {
    my_float pi = 0.0f;
    int sign = 1;
    // avoid operating with floating values
    for (size_t i = 0; i < steps; i++) {
        pi += 1 / (2.0f * i + 1.0f)*sign;
        sign = -sign;
    }
    return 4*pi;
}

int main(int argc, const char *argv[]) {

    // read the number of steps from the command line
    if (argc != 2) {
        std::cerr << "Invalid syntax: pi_taylor <steps>" << std::endl;
        exit(1);

    }

    size_t steps = std::stoll(argv[1]);

    auto start = std::chrono::steady_clock::now();
    auto pi = pi_taylor(steps);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;

    std::cout << "For " << steps << ", pi value: "
        << std::setprecision(std::numeric_limits<my_float>::digits10 + 1)
        << pi << std::endl;

    std::cout << "Time: " << time.count() << " seconds" << std::endl;
}
