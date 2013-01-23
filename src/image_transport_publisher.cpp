#include "image_transport_publisher.h"

namespace enc = sensor_msgs::image_encodings;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "image_transport_publisher");
	ros::NodeHandle nh;
	ros::Time start;
	ros::Time stop;
	image_transport::ImageTransport it(nh);
	image_transport::Publisher image_pub = it.advertise("/image_benchmark", 30);

	// Give advertise some time
	sleep(1);

	// Load images
	cv_bridge::CvImagePtr cv_ptr(new cv_bridge::CvImage);

	cv::Mat cv_image;

	ROS_INFO("loading pictures");
	cv_image  = cv::imread(IMAGE_PATH_RGB, 1); // Read RGB image

	if (!cv_image.data)
	{
		ROS_ERROR("Could not open or find images, check image_publisher.h for file paths");
	}

	cv_ptr->image = cv_image;

	// Write msg data
	cv_ptr->encoding = "bgr8"; // image encoding
while (nh.ok())
{
	// start timer
	start = ros::Time::now();
	for(int i=0;i<30;++i)
	{
	  image_pub.publish(cv_ptr->toImageMsg());
	  ROS_DEBUG("Published 1 image");
	}
	stop = ros::Time::now();
	ROS_DEBUG("It took %llu milliseconds for 30 images",(stop.toNSec()-start.toNSec())/1000000);
	cout << (stop.toNSec()-start.toNSec())/1000000 <<'\n';
}
	return 0;
}
