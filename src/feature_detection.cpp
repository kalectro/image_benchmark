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
	// variables for timing
	ros::Time start;
	ros::Time stop;
	string detector_type;
	string extractor_type;
	string image_path;
	//ros::Publisher features_pub = nh.advertise<cv::Mat>("/image_benchmark/features", 10000);
	vector<KeyPoint> keypoints;
	// Init nonfree feature detection from OpenCV2
	initModule_nonfree(); 

	// get parameters from server
	// get image path
	if (nh.getParam("/feature_detection/image_path", image_path))
	{
		ROS_DEBUG("Found image path %s on server", image_path.c_str());
	}
	else
	{
		image_path = IMAGE_PATH;
		ROS_DEBUG("Found no image path on server, using default %s", image_path.c_str());
	}

	// get feature detector type
	nh.param<std::string>("/feature_detection/detector_type", detector_type, "SIFT");
	if (!(detector_type == "SURF" || detector_type == "SIFT" || detector_type == "ORB" ||detector_type == "BRISK" ||detector_type == "FAST"))
		ROS_INFO_ONCE("The selected detector type has not been tested yet, expect a segmentation error");

	// get feature extractor type
	nh.param<std::string>("/feature_detection/extractor_type", extractor_type, "SIFT");
	if (!(extractor_type == "SURF" || extractor_type == "SIFT" || extractor_type == "ORB" || extractor_type == "BRISK" || extractor_type == "FREAK"))
		ROS_INFO_ONCE("The selected detector type has not been tested yet, expect a segmentation error");
	
	// initialize OpenCV images and descriptors
	cv::Mat cv_image;
	cv::Mat descriptors;

	ROS_DEBUG("loading picture");
	cv_image  = cv::imread(image_path, 1); // Read RGB image

	if (!cv_image.data)
	{
		ROS_ERROR("Could not open or find image at file path:");
		cout << image_path << '\n';
		ROS_ERROR("Set parameter /feature_detection/image_path for file path to image");
		nh.shutdown();
	}

	// construct feature detector and descriptor extractor
	Ptr<FeatureDetector> detector = FeatureDetector::create(detector_type);
	Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create(extractor_type);

	// set the header line for a cvs output seperated by ;
	cout << "detection[ms];keypoints;detector;extraction;keypoints;image path;extractor\n";

	//while (nh.ok())
	for (int i=0;i<10;++i)
	{	
		// start timer
		start = ros::Time::now();
		// Detect feature points
		detector->detect(cv_image, keypoints);
		// stop the timer
		stop = ros::Time::now();
		// output time for detector
		cout << (stop.toNSec()-start.toNSec())/1000000 << ';' << keypoints.size() << ';' << detector_type << ';' ;

		// start timer
		start = ros::Time::now();
		// Get descriptors for keypoints
		extractor->compute(cv_image, keypoints, descriptors);
		// stop the timer
		stop = ros::Time::now();
		// nice debug output to show the computing time
		// ROS_DEBUG("It took %llu milliseconds for 1 image",(stop.toNSec()-start.toNSec())/1000000);
		// output time for feature extractor
		cout << (stop.toNSec()-start.toNSec())/1000000 << ';' << keypoints.size() << ';' << image_path << ';' << extractor_type << '\n';
	}
	return 0;
}
