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
	initModule_nonfree(); // Init nonfree feature detection
	
	// Give advertise some time
	sleep(1);

	ROS_DEBUG("time[ms];keypoints;image path;detector type");
	//while (nh.ok())
	for (int i=0;i<10;++i)
	{	
		// get parameters from server
		string image_path;
		string detector_type;
		if (nh.getParam("/feature_detection/image_path", image_path))
		{
			ROS_DEBUG("Found image path %s on server", image_path.c_str());
		}
		else
		{
			image_path = IMAGE_PATH;
			ROS_DEBUG("Found no image path on server, using default %s", image_path.c_str());
		}

		nh.param<std::string>("/feature_detection/detector_type", detector_type, "SIFT");
		if (!(detector_type == "SURF" || detector_type == "SIFT" || detector_type == "ORB" ||detector_type == "BRISK"))
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

		// start timer
		start = ros::Time::now();
		// find features using method SURF. Bad hard coding
		getFeatures(cv_image,keypoints,descriptors, detector_type);
		// stop the timer
		stop = ros::Time::now();
		// nice debug output to show the computing time
		ROS_DEBUG("It took %llu milliseconds for 1 image",(stop.toNSec()-start.toNSec())/1000000);
		// just output the number for easy copy/paste
		cout << (stop.toNSec()-start.toNSec())/1000000 << ';' << keypoints.size() << ';' << image_path << ';' << detector_type << '\n';
	}
	return 0;
}

// This function uses the OpenCV library to find features in an image
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
