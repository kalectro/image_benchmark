: ${1?"Usage: $0 /path/to/image.jpg"}
filename=benchmark_results.csv
if [ ! -f $filename ];
then
	echo "time[ms];keypoints;image path;detector type" > $filename
fi
for i in SURF SIFT BRISK ORB
	do rosrun image_benchmark feature_detection_node _detector_type:=$i  _image_path:=$1 >> $filename
done
