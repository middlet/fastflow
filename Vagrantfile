#
# fast flow autobuild vm
#

# config options
ip = '10.53.0.0'
hostname = 'fastflow'
ram = '512'

Vagrant.configure("2") do |config|
    config.vm.box = 'precise32'
    config.vm.box_url = 'http://files.vagrantup.com/precise32.box'
    config.vm.hostname = hostname
    config.vm.network :private_network, ip: ip

    config.vm.provider :virtualbox do |vb|
        vb.customize [
            'modifyvm', :id,
            '--name', hostname,
            '--memory', ram
        ]
    end
    config.vm.provision "shell", path: "./build_opencv.bash"
end

