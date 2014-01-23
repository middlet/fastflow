/*!
	\file test_fastflow.cpp

	test file for the fastflow code

*/

# include "../src/fastflow.h"

# include "gtest/gtest.h"

class FastFlowTest : public ::testing::Test 
{
protected:
	FastFlow _ff;

	cv::Mat createImage(uint fi) 
	{
		cv::Mat im(480, 640, CV_8UC3, cv::Scalar(0,0,0));
		rectangle(im, cv::Point2f(100+fi*5, 100), cv::Point2f(150+fi*5, 150), cv::Scalar(0,255,0), -1, 8);
		rectangle(im, cv::Point2f(100+fi*5, 100), cv::Point2f(150+fi*5, 150), cv::Scalar(255,0,0), 1);


		return im;
	}

}; // class FastFlowTest

/*
	test for processing a frame
*/
TEST_F(FastFlowTest, FrameProcessOK)
{
	// create test images
	cv::Mat im0 = createImage(0);
	cv::Mat im1 = createImage(1);
	imwrite("./out/rect.png", im0);
	std::vector<cv::Point2f> points[2];
	_ff.processFrame(im0, im1, points);

	EXPECT_EQ(4, points[0].size());
	EXPECT_EQ(4, points[1].size());

	EXPECT_LT(points[0][0].x-100, 2);
	EXPECT_LT(150-points[0][2].y, 2);
	EXPECT_LT(155-points[1][1].x, 2);
	EXPECT_LT(150-points[1][3].y, 2);


}
