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
for j in SURF SIFT BRISK ORB FAST
	for i in SURF SIFT BRISK ORB FREAK
		do rosrun image_benchmark feature_detection_node _detector_type:=$j _extractor_type:=$i _image_path:=$1 >> $filename
	done
done
