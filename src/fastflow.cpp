/*!
    \file fastflow.cpp

    this is the main code to generate the flow information from an
    image sequence

*/

// internal includes
# include "fastflow.h"

FastFlow::FastFlow (std::string fname)
    : _have_video(false)
{

    _vid.open(fname);

    cv::Mat frame;
    _vid >> frame;

    if (!_vid.isOpened())
    {
        std::cerr << "problem with " << fname << std::endl;
        return;
    }

    _have_video = true;

}

void
FastFlow::computeFlow (const uint sframe, const uint eframe)
{

    unsigned int fi=0;
    bool process = false;
    cv::Mat frame0, frame1;
    while (true)
    {
        if (!_vid.read(frame0))
            break;
        if (fi>=sframe && fi<eframe)
        {
            std::cout << fi << std::endl;
            if (fi!=sframe)
                frame0 = frame1.clone();

            std::ostringstream os;
            os << "./out/image_" << std::setw(9) << std::setfill('0') << fi << ".png";
            imwrite(os.str().c_str(), frame0);
            
            if (!_vid.read(frame1))
                break;

            float start = cv::getTickCount();
            std::vector<cv::Point2f> points[2];
            processFrame(frame0, frame1, points);
            _tracks.addPoints(points[0], points[1]);
            outputFlow(fi, points);
            std::cout << "\t" << (cv::getTickCount() - start) / cv::getTickFrequency() << std::endl;

            if (fi==eframe-1)
                break;
        }

        fi++;

    }

    outputTracks();

    std::cout << "nframes = " << (fi-sframe) << " " << process << std::endl;

}

void
FastFlow::processFrame(cv::Mat f0, cv::Mat f1, std::vector<cv::Point2f> *points)
{
    // move these params out
    cv::Ptr<cv::FeatureDetector> feat = new cv::FastFeatureDetector();
    cv::TermCriteria termcrit(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03);
    cv::Size subPixWinSize(10,10), winSize(31,31);
    // convert to grayscale
    cv::Mat f0g, f1g;
    cv::cvtColor(f0, f0g, CV_BGR2GRAY);
    cv::cvtColor(f1, f1g, CV_BGR2GRAY);
    // compute flow
    std::vector<cv::KeyPoint> kpoints;
    feat->detect(f0g, kpoints);
    for (uint ki=0; ki<kpoints.size(); ++ki)
            points[0].push_back(kpoints[ki].pt);
    std::vector<uchar> status;
    std::vector<float> error;
    if (kpoints.size()>0)
        cv::calcOpticalFlowPyrLK(f0g, f1g, points[0], points[1], status, error, winSize, 3, termcrit, 0, 0.001);
}

void
FastFlow::outputFlow(uint fi, std::vector<cv::Point2f> *points)
{
    boost::filesystem::path dirname("./out");
    if (boost::filesystem::is_regular_file(dirname))
        return;
    if (!boost::filesystem::is_directory("./out"))
        boost::filesystem::create_directories("./out");
    std::ostringstream fname, oiname;
    fname << "./out/flow_" << std::setw(9) << std::setfill('0') << fi << ".flo";
    oiname << "./out/flow_" << std::setw(9) << std::setfill('0') << fi << ".png";

    cv::Mat im(480, 640, CV_8UC3, cv::Scalar(0,0,255));
    std::ofstream of;
    of.open(fname.str().c_str());
    for (uint pi=0; pi<points[0].size(); ++pi)
    {
        float x0 = points[0][pi].x, y0 = points[0][pi].y;
        float x1 = points[1][pi].x, y1 = points[1][pi].y;
        of << x0 << " " << y0 << " " << (x1-x0) << " " << (y1-y0) << std::endl;
        line(im, cv::Point(x0,y0), cv::Point(x1,y1), cv::Scalar(0,255,0), 1, 8);
    }
    imwrite(oiname.str().c_str(), im);
    of.close();
}

void
FastFlow::outputTracks ()
{
    std::vector<std::vector<cv::Point2f> > tracks = _tracks.tracks();

    cv::Mat im(480, 640, CV_8UC3, cv::Scalar(0,0,255));

    for (uint ti=0; ti<tracks.size(); ++ti)
    {
        for (uint pi=1; pi<tracks[ti].size(); ++pi)
        {
            line(im, tracks[ti][pi-1], tracks[ti][pi], cv::Scalar(0,255,0), 1, 8);
        }
    }

    imwrite("./out/tracks.png", im);

}