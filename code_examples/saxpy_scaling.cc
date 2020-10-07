#include <iostream>
#include <random>
#include <thread>
#include <vector>

// assume a container
template <typename T>
void saxpy(T& z, const typename T::value_type A, const T& x, const T& y,
        size_t begin, size_t end)
{
    for(size_t i = begin; i < end; ++i) {
         z[i] = A * x[i] + y[i];
    }
}

int main() {

    const size_t N = 1024*1024*1024;
    const float A = 3.14f;
    using vf = std::vector<float>;
    vf z(N, 0.0f);
    vf x, y;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    for(size_t i = 0; i < N; ++i) {
        float value = dis(gen);
        x.push_back(value);
        y.push_back(value); // reduce execution time
    }

    std::vector<std::thread> thread_vector;
    std::vector<std::chrono::milliseconds> extime_thread;

    size_t max_threads = std::min(48u, std::thread::hardware_concurrency());
    for(size_t current_threads = 1; current_threads <= max_threads; ++current_threads) {
        // ToDo : run several times and check median and deviation
        // launch the work
        auto start = std::chrono::steady_clock::now();
        for(size_t i = 0; i < current_threads-1; ++i) {
            size_t begin = i * (N/current_threads);
            size_t end   = begin + N/current_threads;
            thread_vector.push_back(std::thread(saxpy<vf>, std::ref(z), A,
                    std::ref(x), std::ref(y), begin, end));
        }
        size_t begin = (current_threads-1)*(N/current_threads);
        size_t end = std::max(N, begin + N/current_threads);
        thread_vector.push_back(std::thread(saxpy<vf>, std::ref(z), A,
                std::ref(x), std::ref(y), begin, end));

        // wait for completion
        for(size_t i = 0; i < current_threads; ++i) {
            thread_vector[i].join();
        }
        auto stop = std::chrono::steady_clock::now();
        extime_thread.push_back(
                std::chrono::duration_cast<std::chrono::milliseconds>
                (stop-start));

        // clean the vector array
        thread_vector.clear();
    }

    std::cout << "threads, time (ms)" << std::endl;
    for(size_t i = 0; i < extime_thread.size(); ++i) {
        std::cout << i+1 << ", " << extime_thread[i].count() << std::endl;
    }
}

