# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  # A few different VMs...
  config.vm.box = "hashicorp/bionic64"
  #config.vm.box = "generic/ubuntu1804"
  #config.vm.box = "generic/trusty32"

  # X-forwarding
  # Thanks, https://computingforgeeks.com/how-to-enable-and-use-ssh-x11-forwarding-on-vagrant-instances/
  config.ssh.forward_agent = true
  config.ssh.forward_x11 = true

  config.vm.hostname = "vbox"

  config.vm.provider 'virtualbox' do |vb|
    vb.gui = false
    vb.customize ['modifyvm', :id, '--name', 'DevBox460']
    vb.customize ['modifyvm', :id, '--memory', 2048]
  end

  # Don't check for updates on every 'vagrant up'
  config.vm.box_check_update = false

  # here, I sync the current directory (".") on my host machine with the VM (which can be located at "/home/vagrant/path/to/stuff")
  config.vm.synced_folder ".", "/home/vagrant/projects"
  config.vm.synced_folder "/Users/twp/projects/classes/msu-cs460-code", "/home/vagrant/code"

  # Permissioned provisioning with a shell script.
  config.vm.provision "shell", inline: <<-SHELL
    echo 'Doing privileged provisioning...'
    whoami

    export DEBIAN_FRONTEND=noninteractive

    apt-get update
    apt-get upgrade -y
    apt-get install autoconf -y

    # make sure we have our manuals...
    apt-get install man -y
    apt-get install manpages-dev -y
    apt-get install manpages-posix -y
    apt-get install manpages-posix-dev -y

    # some useful installs
    apt-get install vim -y  # editor
    apt-get install git -y  # DVCS
    apt-get install tree -y # enhanced commandline output

    # installs for OS assignments
    apt-get install gcc -y          # compiler
    apt-get install gdb -y          # debugger
    apt-get install valgrind -y     # memory debugger
    apt-get install xauth -y        # x11
    apt-get install x11-apps -y     # e.g., xeyes, xclock
    apt-get install imagemagick -y  # image tools
  SHELL

  # Non-root provisioning with a shell script.
  config.vm.provision "shell", privileged: false, inline: <<-SHELL
    echo 'Now doing non-root provisioning...'
    whoami

    # surpress login banner w/ motd
    touch ~/.hushlogin

    # update ls & prompt colors
    if ! grep -q 'LS_COLORS' ~/.bashrc; then
        echo "overriding some color settings..."
        curl -s https://gist.githubusercontent.com/traviswpeters/e392e571bfdfb1939a9f233b1bb47f68/raw/f6a1a21f3dc95107091f7ef29233e612c6aa058c/custom_shell_colors.sh -o .mycolors
        cat .mycolors >> ~/.bashrc

        # while we are at it...
        echo 'colo desert' >> ~/.vimrc
        echo 'syntax on' >> ~/.vimrc
    fi

    # update ulimit and core dump pattern for user's core dumps (a little hacky, but oh well...)
    if ! grep -q 'ulimit -c' ~/.bashrc; then
        echo "overriding core dump settings..."
        echo '\n# overriding core dump settings' >> ~/.bashrc
        echo 'ulimit -c unlimited' >> ~/.bashrc
        echo 'sudo sysctl -w kernel.core_pattern=/home/vagrant/core > /dev/null 2>&1' >> ~/.bashrc
    fi
  SHELL

  config.vm.provision "shell", inline: "echo All done! Now run: vagrant ssh"
end
