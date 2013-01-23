/*
 * Simple Feature detection for benchmarking purpose
 *
 *  Created on: Jan 15, 2013
 *      Author: frk1pal
 */

#include "feature_detection.h"

int main(int argc, char **argv)
{
  	ros::init(argc, argv, "feature_detection");
	ros::NodeHandle nh;
	ros::Time start;
	ros::Time stop;
	//ros::Publisher features_pub = nh.advertise<cv::Mat>("/image_benchmark/features", 10000);
	vector<KeyPoint> keypoints;
	vector<KeyPoint> keypoints2;
	initModule_nonfree(); // Init nonfree feature detection

	// Give advertise some time
	sleep(1);

	cv::Mat cv_image;
	cv::Mat descriptors;

	ROS_INFO("loading pictures");
	cv_image  = cv::imread(IMAGE_PATH_RGB, 1); // Read RGB image

	if (!cv_image.data)
	{
		ROS_ERROR("Could not open or find images, check image_publisher.h for file paths");
	}
	
	while (nh.ok())
	{
		// start timer
		start = ros::Time::now();
		//for(int i=0;i<30;++i)
		//{
			getFeatures(cv_image,keypoints,descriptors, "SURF");
			//features_pub.publish(keypoints);
			cout << "found so many descriptors " << keypoints.size() << '\n';
		//}
		stop = ros::Time::now();
		ROS_DEBUG("It took %llu milliseconds for 1 images",(stop.toNSec()-start.toNSec())/1000000);
		cout << (stop.toNSec()-start.toNSec())/1000000 <<'\n';
		sleep(0.5);
	}
}


void getFeatures(const Mat& img, vector<KeyPoint>& keypoints, Mat& descriptors,
                             const string& detectorType)
{
  // Use second channel, if input image contains multiple ones
  Mat img_proc(img.rows, img.cols, CV_8UC1);
  Mat out[] = {img_proc};
  if (img.dims > 1)
  {
    int from_to[] = {1, 0};
    mixChannels(&img, 1, out, 1, from_to, 1);
  }
  else
  {
    img_proc = img;
  }

  // Detect feature points
  Ptr<FeatureDetector> detector = FeatureDetector::create(detectorType);
  detector->detect(img_proc, keypoints);

  // Get descriptors for keypoints
  Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create(detectorType);
  extractor->compute(img_proc, keypoints, descriptors);
}
