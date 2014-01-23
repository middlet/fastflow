/*!
	\file test_flowpath.cpp

	test file for the flowpath code

*/

# include "../src/flowpath.h"

# include "gtest/gtest.h"

class FlowPathTest : public ::testing::Test 
{
protected:
	FlowPath _fp;

	std::vector<cv::Point2f> randomPoints(uint N) 
	{
		std::vector<cv::Point2f> points;
		cv::RNG rng;
		for (uint pi=0; pi<N; pi++)
		{
			points.push_back(cv::Point(rng.uniform(0, 255), rng.uniform(0, 255)));
		}

		return points;
	}

}; // class FlowPathTest

/*
	add the first set of tracks
*/
TEST_F(FlowPathTest, AddInitialTrack)
{
	std::vector<cv::Point2f> p;
	p.push_back(cv::Point2f(1,1));
	p.push_back(cv::Point2f(2,2));
	p.push_back(cv::Point2f(3,3));

	_fp.addInitialPoints(p);

	std::vector<std::vector<cv::Point2f> > tracks = _fp.tracks();

	EXPECT_EQ(3, _fp.numTracks());
	EXPECT_EQ(cv::Point2f(1,1), tracks[0][0]);
	EXPECT_EQ(cv::Point2f(2,2), tracks[1][0]);
	EXPECT_EQ(cv::Point2f(3,3), tracks[2][0]);
}


/*
	add a new point to an existing track
*/
TEST_F(FlowPathTest, AddPoint)
{
	std::vector<cv::Point2f> p1, p2;
	p1.push_back(cv::Point2f(2,2));
	p2.push_back(cv::Point2f(5,5));
	_fp.addPoints(p1, p2);
	std::vector<std::vector<cv::Point2f> > track = _fp.tracks();

	EXPECT_EQ(1, _fp.numTracks());
	EXPECT_EQ(cv::Point2f(2,2), track[0][0]);
	EXPECT_EQ(cv::Point2f(5,5), track[0][1]);
	EXPECT_EQ(2, track[0].size());
}

/*
	there is an additional point on the second image
*/
TEST_F(FlowPathTest, AddPointNew)
{
	std::vector<cv::Point2f> p1, p2;
	p1.push_back(cv::Point2f(2,2));
	p2.push_back(cv::Point2f(5,5));
	p2.push_back(cv::Point2f(3,3));
	_fp.addPoints(p1, p2);
	std::vector<std::vector<cv::Point2f> > tracks = _fp.tracks();

	EXPECT_EQ(2, _fp.numTracks());
	EXPECT_EQ(cv::Point2f(2,2), tracks[0][0]);
	EXPECT_EQ(cv::Point2f(5,5), tracks[0][1]);
	EXPECT_EQ(2, tracks[0].size());
	EXPECT_EQ(cv::Point2f(3,3), tracks[1][0]);
	EXPECT_EQ(1, tracks[1].size());
}
