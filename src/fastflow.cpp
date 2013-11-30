/*!
    \file fastflow.cpp

    this is the main code to generate the flow information from an
    image sequence

*/

// internal includes
# include "fastflow.h"

FastFlow::FastFlow (std::string fname)
    : _have_video(false)
{

    _vid.open(fname);

    cv::Mat frame;
    _vid >> frame;

    if (!_vid.isOpened())
    {
        std::cerr << "problem with " << fname << std::endl;
        return;
    }

    _have_video = true;

}

void
FastFlow::computeFlow (const unsigned int sframe, const unsigned int eframe)
{

    unsigned int fi=0;
    bool process = false;
    for (;;)
    {
        cv::Mat frame0;

        if (!_vid.read(frame0))
            break;

        fi++;

    }

    std::cout << "nframes = " << fi << " " << process << std::endl;

}