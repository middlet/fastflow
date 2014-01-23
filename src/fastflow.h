/*!
    \file fastflow.h

    this is the main code to generate the flow information from an
    image sequence
*/

# ifndef FFLOW_FASTFLOW_H
# define FFLOW_FASTFLOW_H

// c++ includes
# include <string>
# include <fstream>
# include <iomanip>

// boost includes
# include <boost/filesystem.hpp>

// opencv includes
# include "opencv2/opencv.hpp"

// my includes
# include "flowpath.h"

class FastFlow
{
public:
	FastFlow ();
    FastFlow (std::string fname);
	~FastFlow ();    

    void computeFlow (const uint sframe=0, const uint eframe = -1);

    void processFrame (cv::Mat f0, cv::Mat f1, std::vector<cv::Point2f> *points);

    void outputFlow (uint fi, std::vector<cv::Point2f> *points);
    void outputTracks ();

private:
    cv::VideoCapture _vid;
    bool _have_video;
    FlowPath _tracks;

}; // class FastFlow

# endif // FFLOW_FASTFLOW_H