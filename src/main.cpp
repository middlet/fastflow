/*!
    \file main.cpp

    main program to run the code

*/

// c++ includes
# include <iostream>

// internal includes
# include "fastflow.h"

int
main (int argc, char *argv[])
{
    if (argc<2)
    {
        std::cerr << "not enough arguments\n" << "usage : ./fflow <file>" << std::endl;
        return -1;
    }

    FastFlow f(argv[1]);

    return 0;
}