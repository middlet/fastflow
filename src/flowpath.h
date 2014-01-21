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

	void addPoints(const std::vector<cv::Point2f> p1, const std::vector<cv::Point2f> p2);
	void addInitialPoints(const std::vector<cv::Point2f> p);

	const std::vector<std::vector<cv::Point2f> > tracks () const;
	const uint numTracks () const;

private:
	std::vector<std::vector<cv::Point2f> > _tracks;
	bool _havetrack;

}; // class FlowPath

# endif // FFLOW_FLOWPATH_H