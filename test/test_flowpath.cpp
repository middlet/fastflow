/*!
	\file flowpath_test.cpp

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

TEST_F(FlowPathTest, AddPointOK)
{
	std::vector<cv::Point2f> p1, p2;
	p1.push_back(cv::Point2f(2,2));
	p2.push_back(cv::Point2f(5,5));
	_fp.addPoints(p1, p2);

	EXPECT_EQ(2, _fp.numTracks());
}