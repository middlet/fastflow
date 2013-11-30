/*!
    \file fastflow.h

    this is the main code to generate the flow information from an
    image sequence
*/

# ifndef FFLOW_FASTFLOW_H
# define FFLOW_FASTFLOW_H

// c++ includes
# include <string>

// opencv includes
# include "opencv2/opencv.hpp"

class FastFlow
{
public:
    FastFlow (std::string fname);


private:
    cv::VideoCapture _vid;
    bool _have_video;


}; // class FastFlow

# endif // FFLOW_FASTFLOW_H