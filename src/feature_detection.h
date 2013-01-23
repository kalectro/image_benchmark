/*
 * feature_detection.h
 *
 *  Created on: Jan 15, 2013
 *      Author: frk1pal
 * This program is a very simple feature detection for benchmarking purpose
 */

#include "ros/ros.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "algorithm"
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

static const string IMAGE_PATH_RGB = "/home/frk1pal/images/rgb.jpg";
static const string IMAGE_PATH_DEPTH = "/home/frk1pal/images/depth.png";

  // Determine the feature points and their descriptors with one defined method, e.g. "SURF". The second channel is used,
  // if the input image contains several channels.
  void getFeatures(const Mat& img, vector<KeyPoint>& keypoints, Mat& descriptors, const string& detectorType);
