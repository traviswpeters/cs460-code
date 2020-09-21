# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  # A few different VMs...
  config.vm.box = "hashicorp/bionic64"

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
  #config.vm.synced_folder "/path/on/host/file/system", "/home/vagrant/dir/on/guest"

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
    apt-get install gcc-multilib -y # multi architecture and 32-/64- bit support
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

    # add hook in bashrc to grab updates to cs460 customizations and apply them.
    if ! grep -q 'cs460customizations' ~/.bashrc; then
cat >> ~/.bashrc <<EOL

# fetch the most up-to-date cs460 customizations
curl -sS https://raw.githubusercontent.com/traviswpeters/cs460-code/master/cs460customizations -o .cs460customizations

# source our customizations
if [ -f ~/.cs460customizations ]; then
    source ~/.cs460customizations
fi

EOL
    fi

  SHELL

  config.vm.provision "shell", inline: "echo All done! Now run: vagrant ssh"
end
