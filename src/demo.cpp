#include <iostream>
#include "matrix.hpp"

int main()
{
    Matrix M=Matrix::rand(4,4);
    std::cout<<M.inverse();
}
