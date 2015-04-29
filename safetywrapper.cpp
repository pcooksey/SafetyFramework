#include "safetywrapper.h"

std::clock_t prefix()
{
    return std::clock();
}
void suffix(std::clock_t start)
{
    std::cout << "Time: "
              << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000)
              << " ms"
              << std::endl;
}
