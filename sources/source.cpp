// Copyright 2018 Your Name <your_email>

#include "header.hpp"
#include <ctime>

Cache::Cache() {
    _array = NULL;
    _experiments = number_of_experiments();
}


std::map<int, int> Cache::number_of_experiments() {
    std::map<int, int> experiments;
    int n = 1;
    experiments[n] = l1 / 2;
    while (pow(2, n) * translate < (3 / 2) * l3) {
        ++n;
        experiments[n] = pow(2, n - 1) * translate;
    }
    ++n;
    experiments[n] = (3 / 2) * l3;
    return experiments;
}


void Cache::directionType() {
    int number_of_experimets = _experiments.size();
    for (size_t i = 1; i <= static_cast<size_t>(number_of_experimets); ++i) {
        set_array(i);
        int size = _experiments[i] / sizeof(int);
        clock_t start = clock();
        for (size_t j = 1; j != static_cast<size_t>(iterations); ++j) {
            set_straight(size);
        }
        delete[] _array;
        clock_t end1 = clock();
        resultWindow("Straight", i, _experiments[i],
                     static_cast<double> (end1 - start) / CLOCKS_PER_SEC);
    }
}


void Cache::converseType() {
    int number_of_experimets = _experiments.size();
    for (size_t i = 1; i <= static_cast<size_t>(number_of_experimets); ++i) {
        set_array(i);
        int size = _experiments[i] / sizeof(int);
        clock_t start = clock();
        for (size_t j = 1; j != static_cast<size_t>(iterations); ++j) {
            set_back(size);
        }
        delete[] _array;
        clock_t end1 = clock();
        resultWindow("Back", i, _experiments[i],
                     static_cast<double> (end1 - start) / CLOCKS_PER_SEC);
    }
}


void Cache::randomType() {
    int number_of_experimets = _experiments.size();
    for (size_t i = 1; i <= static_cast<size_t>(number_of_experimets); ++i) {
        set_array(i);
        int size = _experiments[i] / sizeof(int);
        std::vector <size_t> myrand(size);
        srand(time(NULL));
        random_shuffle(myrand.begin(), myrand.end());
        clock_t start = clock();
        for (size_t j = 1; j != static_cast<size_t>(iterations); ++j) {
            set_random(size, myrand);
        }
        delete[] _array;
        clock_t end1 = clock();
        resultWindow("Random", i, _experiments[i],
                     static_cast<double> (end1 - start) / CLOCKS_PER_SEC);
    }
}


void Cache::set_array(int i) {
    int size = _experiments[i] / sizeof(int);
    _array = new int[size];
    for (size_t k = 0; k < static_cast<size_t>(size); ++k) {
        _array[k] = 0;
    }
}


void Cache::set_straight(int size) {
    unsigned now = time(0);
    for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
        _array[i] = rand_r(&now);
    }
}


void Cache::set_back(int size) {
    unsigned now = time(0);
    for (int i = size - 1; i >= 0; --i) {
        _array[i] = rand_r(&now);
    }
}

void Cache::set_random(int size, std::vector <size_t> &myrand) {
    unsigned now = time(0);
    for (size_t i = 0; i < static_cast<size_t>(size); ++i) {
        _array[myrand[i]] = rand_r(&now);
    }
}


void Cache::resultWindow(std::string const &travelVariant,
                         size_t const &numberOfExperiment, int const &size,
                         double const &timeOfArray) {
    std::cout << "travel_variant: " << travelVariant << std::endl;
    std::cout << "experiments: " << std::endl;
    std::cout << "   - experiment: " << std::endl;
    std::cout << "number: " << numberOfExperiment << std::endl;
    std::cout << "input_data: " << std::endl;
    std::cout << "buffer_size: " << size / (translate) << "mb" << std::endl;
    std::cout << "results: " << std::endl;
    std::cout << "duration: " << timeOfArray << std::endl;
}
