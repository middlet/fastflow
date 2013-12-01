#
# fast flow autobuild vm
#

# config options
ip = '192.168.0.53'
hostname = 'fastflow'
ram = '512'

# provision script
$script = <<SCRIPT
version="$(wget -q -O - http://sourceforge.net/projects/opencvlibrary/files/opencv-unix | egrep -m1 -o '\"[0-9](\.[0-9])+' | cut -c2-)"
echo "Installing OpenCV" $version
mkdir OpenCV
cd OpenCV
echo "Removing any pre-installed ffmpeg and x264"
sudo apt-get -qq remove ffmpeg x264 libx264-dev
echo "Installing Dependenices"
sudo apt-get -qq install libopencv-dev build-essential checkinstall cmake pkg-config yasm libtiff4-dev libjpeg-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev python-dev python-numpy libtbb-dev libqt4-dev libgtk2.0-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils ffmpeg
echo "Downloading OpenCV" $version
wget -O OpenCV-$version.tar.gz http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/$version/opencv-"$version".tar.gz/download
echo "Installing OpenCV" $version
tar -xvf OpenCV-$version.tar.gz
cd opencv-$version
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON -D WITH_CUDA=OFF ..
make -j 4
sudo make install
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
echo "OpenCV" $version "ready to be used"
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

