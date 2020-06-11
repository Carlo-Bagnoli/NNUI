#pragma once

#include <iostream>

#define Deb(x) std::cout << #x << " " << x << "\n";

template<typename... T>
void read(T&&... args) {
    ((std::cin >> args), ...);
}


template<typename... T>
void write(T&&... args) {
    ((std::cout << args << "\n"), ...);
}
