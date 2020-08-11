# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "hashicorp/bionic64"
  #config.vm.box = "generic/ubuntu1804"
  #config.vm.box = "generic/trusty32"
  config.vm.hostname = "vbox"

  config.vm.provider 'virtualbox' do |vb|
    vb.gui = false
    vb.customize ['modifyvm', :id, '--name', 'Generic Dev Box']
    vb.customize ['modifyvm', :id, '--memory', 2048]
  end


  # Don't check for updates on every 'vagrant up'
  config.vm.box_check_update = false

  # here, I sync the current directory (".") on my host machine with the VM (which can be located at "/home/vagrant/path/to/stuff")
  config.vm.synced_folder ".", "/home/vagrant/projects"
  #config.vm.synced_folder ".", "/home/vagrant/classes"

  # Enable provisioning with a shell script.
  config.vm.provision "shell", inline: <<-SHELL
    export DEBIAN_FRONTEND=noninteractive
    apt-get update
    apt-get upgrade -y
    apt-get install autoconf -y

    # some useful installs
    apt-get install vim  #editor
    apt-get install git  #VCS
    apt-get install tree #enhanced commandline output

    # installs for OS assignments
    apt-get install gdb  #debugger
    apt-get install imagemagick  #image tools

    # make core dumps easier to work with... credit: https://jvns.ca/blog/2018/04/28/debugging-a-segfault-on-linux/
    # - check the current core dump limit setting:
    #   `ulimit -c` 
    # - check the current core dump pattern: 
    #   `cat /proc/sys/kernel/core_pattern`
    # - kill the current process (a.k.a. generate a core dump to test your pattern): 
    #   `kill -s SIGABRT $$`
    ulimit -c unlimited
    #sudo sysctl -w kernel.core_pattern=/tmp/core-%e.%p.%h.%t
    #sudo sysctl -w kernel.core_pattern=~/core  <<< can't use '~' --- must use absolute path
    sudo sysctl -w kernel.core_pattern=/home/vagrant/core

    # surpress login banner w/ motd
    touch ~/.hushlogin
  SHELL
  config.vm.provision "shell", inline: "echo All done! Now run: vagrant ssh"
end
