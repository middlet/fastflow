#
# fast flow autobuild vm
#

# config options
ip = '192.168.0.53'
hostname = 'fastflow'
ram = '512'

# provision script
$script = <<SCRIPT
echo "Installing OpenCV 2.4.7"
mkdir OpenCV
cd OpenCV
echo "Removing any pre-installed ffmpeg and x264"
sudo apt-get -qq update
sudo apt-get -y remove ffmpeg x264 libx264-dev
echo "Installing Dependenices"
sudo apt-get -y install libopencv-dev
sudo apt-get -y install build-essential checkinstall cmake pkg-config yasm
sudo apt-get -y install libtiff4-dev libjpeg-dev libjasper-dev
sudo apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev
sudo apt-get -y install python-dev python-numpy
sudo apt-get -y install libtbb-dev
sudo apt-get -y install libqt4-dev libgtk2.0-dev
sudo apt-get -y install libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev
sudo apt-get -y install x264 v4l-utils ffmpeg
echo "Downloading OpenCV 2.4.7"
wget -O OpenCV-2.4.7.tar.gz http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.4.7/opencv-2.4.7.tar.gz/download
echo "Installing OpenCV 2.4.7"
tar -xvf OpenCV-2.4.7.tar.gz
cd opencv-2.4.7
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON -D WITH_CUDA=OFF ..
make -j4
sudo make install
sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
echo "OpenCV 2.4.7 ready to be used"
sudo apt-get -y install libboost-filesystem-dev
sudo apt-get -y install libboost-system-dev
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

