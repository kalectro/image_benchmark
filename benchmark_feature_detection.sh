: ${1?"Usage: $0 /path/to/image.jpg"}
filename=benchmark_results
i=0
while true
do if [ ! -f $filename$i.csv ]
then
	filename=$filename$i.csv
	break
fi
i=`echo "$i + 1" | bc`
done
for i in SURF SIFT BRISK ORB
	do rosrun image_benchmark feature_detection_node _detector_type:="BRISK" _extractor_type:=$i _image_path:=$1 >> $filename
done
