



#include <iostream>



void
loop (int& n)
{
    int eax = n;
    int ecx = 0;
    int rsi[] = {10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5}; // 16 elements
    for (int edx = 0; edx != 15; ++edx)
    {
        eax = rsi[eax];
        ecx += eax;
    }

    if (eax == 15)
        std::cout << "n = " << n << " ecx = " << ecx << std::endl;
}


int
main (int argc, char* argv[])
{
    for (int i = 0; i != 15; ++i)
        loop (i);
    // result n = 5 ecx = 115

    return EXIT_SUCCESS;
}