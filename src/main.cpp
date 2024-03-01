//#define TESTS

#ifndef TESTS

// Standard C++ Library Headers
#include <iostream>

// User-Defined Headers
#include "Application.hpp"

// Main Function
int main() {
    std::cout << "\n------------ App Creation ------------\n";
    Application app{"Graphics Engine", 1900, 950};

    std::cout << "\n------------ Main Program ------------\n";
    app.run();

    std::cout << "\n---------- App Destruction -----------\n";
    return 0;
}

#else

// Standard C++ Library Headers
#include <cstdlib>
#include <iostream>

// User-Defined Headers
#include "maths/transformations.hpp"
#include "maths/Matrix4.hpp"

int main() {
    srand(time(nullptr));

    Matrix4 mat;
    for(int i = 0 ; i < 4 ; ++i) {
        for(int j = 0 ; j < 4 ; ++j) {
            mat(i, j) = static_cast<float>((-10 + rand() % (10 + 1 - (-10))));
        }
    }

    std::cout << "determinant = " << determinant(mat) << "\n\n";
    std::cout << "mat =\n" << mat << "\n\n";
    std::cout << "inverse(mat) =\n" << inverse(mat) << "\n\n";

    vec3 v1{static_cast<float>((-10 + rand() % (10 + 1 - (-10)))),
             static_cast<float>((-10 + rand() % (10 + 1 - (-10)))),
             static_cast<float>((-10 + rand() % (10 + 1 - (-10))))};

    vec3 v2{static_cast<float>((-10 + rand() % (10 + 1 - (-10)))),
             static_cast<float>((-10 + rand() % (10 + 1 - (-10)))),
             static_cast<float>((-10 + rand() % (10 + 1 - (-10))))};

    std::cout << "v1" << v1 << '\n';
    std::cout << "v2" << v2 << '\n';
    std::cout << "rotate(v1, v2) * v1 = " << (rotate(v1, v2) * v1) << '\n';

    return 0;
}

#endif