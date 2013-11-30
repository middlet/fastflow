/*!
    \file main.cpp

    main program to run the code

*/

# include "fastflow.h"

int
main (int argc, char *argv[])
{
    if (argc<2)
    {
        std::cerr << "not enough arguments\n" << "usage : ./fflow <file>" << std::endl;
        exit();
    }
}