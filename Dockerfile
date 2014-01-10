# opencv
#
# building:
#	docker build -t <name> .
#
# running with similar mounting to vagrant
#	docker run -v `pwd`:/vagrant -t <name> -i /bin/bash

from		ubuntu:12.04
maintainer	middlet@gmail.com

run			echo "deb http://archive.ubuntu.com/ubuntu precise universe multiverse" >> /etc/apt/sources.list

run			apt-get update
run			apt-get install -y wget

add			./build_opencv.bash /tmp/build_opencv.bash
run			/bin/bash /tmp/build_opencv.bash
