/*! 
	/file flowpath.h

	given the results from the flow on a sequence create a series of paths

*/

# ifndef FFLOW_FLOWPATH_H
# define FFLOW_FLOWPATH_H

// opencv includes
# include "opencv2/opencv.hpp"

class FlowPath
{
public:
	FlowPath ();
	~FlowPath ();

private:
	std::vector<std::vector<cv::Point2f> > _tracks;

}; // class FlowPath

# endif // FFLOW_FLOWPATH_H