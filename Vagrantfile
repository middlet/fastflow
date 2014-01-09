#
# fast flow autobuild vm
#

# config options
ip = '10.53.0.0'
hostname = 'fastflow'
ram = '512'

# provision script
$script = <<SCRIPT
version="2.4.8"
export DEBIAN_FRONTEND=noninteractive

downloadfilelist="opencv-$version.tar.gz opencv-$version.zip"
downloadfile=
for file in $downloadfilelist;
do
	wget --spider http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/$version/$file/download
	if [ $? -eq 0 ]; then
		downloadfile=$file
	fi
done
if [ -z "$downloadfile" ]; then
	echo "could not find download file on sourceforge page"
	exit 1
fi

mkdir opencv
cd opencv

echo "installing dependencies"
sudo apt-get -q update
sudo apt-get -q upgrade
sudo apt-get -y install libopencv-dev build-essential checkinstall cmake pkg-config yasm libtiff4-dev libjpeg-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev python-dev python-numpy libtbb-dev libqt4-dev libgtk2.0-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils ffmpeg unzip

echo "downloading opencv" $version
wget -O $downloadfile http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/$version/$downloadfile/download

echo "installing opencv" $version
echo $downloadfile | grep ".zip"
if [ $? -eq 0 ]; then
	unzip $downloadfile
else
	tar -xvf $downloadfile
fi
cd opencv-$version
mkdir build
cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..
make
sudo make install
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
echo "opencv" $version "ready to be used"

echo "installing code dependencies"
sudo apt-get -y install libboost-filesystem-dev libboost-system-dev
SCRIPT


Vagrant.configure("2") do |config|
    config.vm.box = 'precise32'
    config.vm.box_url = 'http://files.vagrantup.com/precise32.box'
    config.vm.hostname = hostname
    config.vm.network :private_network, ip: ip
    config.vm.network :forwarded_port, guest: 31337, host: 31337

    config.vm.provider :virtualbox do |vb|
        vb.customize [
            'modifyvm', :id,
            '--name', hostname,
            '--memory', ram
        ]
    end
    config.vm.provision :shell, :inline => $script
end

