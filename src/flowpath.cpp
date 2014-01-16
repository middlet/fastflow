/*! 
	/file flowpath.cpp

	implementation of the code to extract paths from points in the flow algorithm

*/

# include "flowpath.h"

FlowPath::FlowPath ()
{

}

FlowPath::~FlowPath ()
{
	
}

void 
FlowPath::addPoints(std::vector<cv::Point2f> p1, std::vector<cv::Point2f> p2)
{

	/*
	for (uint pi=0; pi<pi.size(); ++pi)
	{
		for (uint ti=0; ti<_tracks.size(); ++ti)
		{	
			uint np = _tracks[ti].size();
			if (p1[pi]==_tracks[ti][np-1]) {
				_tracks[ti].push_back(p2[pi])
			}
		}
	}
	*/
	
}


const std::vector<std::vector<cv::Point2f> >
FlowPath::tracks () const
{
	return _tracks;
}

const uint
FlowPath::numTracks () const
{
	return _tracks.size();
}