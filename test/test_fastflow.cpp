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

	cv::Mat createImage(uint xi, uint yi) 
	{
		cv::Mat im(480, 640, CV_8UC3, cv::Scalar(0,0,0));
		rectangle(im, cv::Point2f(xi, yi), cv::Point2f(xi+50, yi+50), cv::Scalar(0,255,0), -1, 8);
		rectangle(im, cv::Point2f(xi, yi), cv::Point2f(xi+50, yi+50), cv::Scalar(255,0,0), 1);

		return im;
	}

	void createVideo (std::string fname)
	{
		cv::Mat im0 = createImage(100, 100);
		cv::Mat im1 = createImage(105, 105);
		cv::Mat im2 = createImage(110, 100);
		cv::Mat im3 = createImage(115, 105);

		cv::VideoWriter vid;
		vid.open(fname, CV_FOURCC('M', 'J', 'P', 'G'), 3, cv::Size(640, 480), true);
		vid << im0 << im1 << im2 << im3;
		vid.release();		
	}

}; // class FastFlowTest

/*
	test for processing a frame
*/
TEST_F(FastFlowTest, FrameProcessOK)
{
	// create test images
	cv::Mat im0 = createImage(100, 100);
	cv::Mat im1 = createImage(105, 100);
	std::vector<cv::Point2f> points[2];
	_ff.processFrame(im0, im1, points);

	EXPECT_EQ(4, points[0].size());
	EXPECT_EQ(4, points[1].size());

	EXPECT_LT(points[0][0].x-100, 2);
	EXPECT_LT(150-points[0][2].y, 2);
	EXPECT_LT(155-points[1][1].x, 2);
	EXPECT_LT(150-points[1][3].y, 2);
}


/*
	a sequence of 3 frames  
*/
TEST_F(FastFlowTest, FrameSequenceOK)
{

	std::string fname = "./frameseq.avi";
	createVideo(fname);
	_ff.setVideoSource(fname);
	_ff.computeFlow(0,4);


}
