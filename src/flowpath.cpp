/*! 
	/file flowpath.cpp

	implementation of the code to extract paths from points in the flow algorithm

*/

# include "flowpath.h"

FlowPath::FlowPath ()
	: _havetrack( false )
{

}

FlowPath::~FlowPath ()
{
	
}

void 
FlowPath::addPoints(std::vector<cv::Point2f> p1, std::vector<cv::Point2f> p2)
{

	if (!_havetrack)
	{
		addInitialPoints(p1);
		_havetrack = true;
	}

	for (uint pi=0; pi<p2.size(); ++pi)
	{
		cv::Point2f pp1 = p1[pi];
		bool found = false;
		for (uint ti=0; ti<_tracks.size(); ++ti)
		{
			cv::Point2f pp2 = _tracks[ti].back();
			if (pp1==pp2)
			{
				_tracks[ti].push_back(p2[pi]);
				found = true;
				break;
			}
		}
		if (!found)
		{
			_tracks.push_back(std::vector<cv::Point2f>());
			_tracks.back().push_back(p2[pi]);
		}
	}
}

void
FlowPath::addInitialPoints(std::vector<cv::Point2f> p)
{
	// add all the points as the start of the track
	for (uint pi=0; pi<p.size(); ++pi)
	{
		cv::Point2f pp;
		pp.x = p[pi].x;
		pp.y = p[pi].y;
		_tracks.push_back(std::vector<cv::Point2f>());
		_tracks[pi].push_back(pp);
	}
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