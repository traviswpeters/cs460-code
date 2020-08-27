# CSCI 460 - Operating Systems!

This is the base upstream repository for CSCI 460.

This repository is mostly intended to contain examples from class and serve as an example GitHub repository for students.

Also, to use GitHub effectively in this class we require a rather particular way of setting things up.
Below I outline how you can setup two repositories: one private and one public.
**Your private repo** will be where you check in your solo work (early programming assignments) and for our grading.
**Your public repo** can be used to contribute things back to this class repo.

> These instructions are adapted from [CSCI 366 (Systems Programming)](https://github.com/msu/csci-366-fall2020) @ Montana State University.
> Many thanks to Carson Gross for paving the way.
> In fact, there are some videos from 366 that may be useful if this is confusing to you (below).
> Make sure you follow OUR directions below though - remember, this is CSCI 460, not CSCI 366 :-)
> 1. [Setting Up Your Git Repositories](https://youtu.be/MFBeFUorg3w)
> 2. [GitHub Repo Diagram Explained](https://www.youtube.com/watch?v=zMwEQN8oG7E)

### Getting Started

1. Please follow the steps in the _**Setup Your PRIVATE Repo (via Clone)**_ section below.
2. Please follow the steps in the _**Setup Your PUBLIC Repo (via Fork)**_ section below.
3. Please follow the steps in the _**Register Your PRIVATE Repo (via Pull Request)**_ section below.
4. Check out additional info in the _**Other Things To Know**_ section.

> **NOTE:** My examples are all based on a Unix-y terminal running atop macOS.
> If you use a different OS (e.g., Windows) your mileage may vary.

# Setup Your PRIVATE Repo (via Clone)

**Your private repository** will be used for your individual work and our grading.
Unfortunately, GitHub doesn't let you fork a repo _and then_ make it private.
Thus, rather than the traditional Forking model, we are going to use a Copy model for the class.
Please use the following steps to create a *PRIVATE* version of this repo for your work:

- Create a *private* repository in your own account by
    - Going to <https://github.com/new>
    - Enter the name `csci-460-fall2020-private`
    - Select `Private`
    - Navigate to the `Settings` -> `Manage Access` section
    - Add `traviswpeters` (Travis's GitHub handle) and `reesep` (Reese's GitHub handle) as collaborators
- Now run the following git commands, substituting your GitHub username and NetID where required:
```bash
$ git clone https://github.com/traviswpeters/cs460-code.git csci-460-fall2020-private
$ cd csci-460-fall2020-private
$ git remote set-url origin git@github.com:<YOUR-GITHUB-USERNAME>/csci-460-fall2020-private.git
$ git remote add upstream https://github.com/traviswpeters/cs460-code.git
```

You now have a private copy of the repository on GitHub.
You can push and pull to this repository with the standard `git pull` and `git push` commands.

When you want to get an update from the public class repository you can run this command:

```
$ git pull upstream master
```

You might want to do this at least each week, but likely before each class.

# Setup Your PUBLIC Repo (via Fork)

**Your public repository** can be used for contributing back to the class repository and
to register your private repository.
Please fork this repository to your personal account.

**DO NOT PUSH YOUR INDIVIDUAL WORK CODE TO THIS REPOSITORY**

<!-- I highly recommend against cloning the public respoitory to your local system, to avoid confusion between the two.  -->
<!-- You can edit files in the public repository via the web interface, and that will be much safer. -->

### Register Your PRIVATE Repo (via Pull Request)

In your forked copy of the class repo (the public version), please add a file to the `/repos` directory that is named
```
<YOUR NET ID>.txt
```
with the git URL of your private repository.

For example, if I were a student with the NetID `W43m513` and my GitHub username was `studentIAm`
I would add a file named `W43m513.txt` to `/repos` with the following line:
```
git@github.com:studentIAm/csci-460-fall2020-private.git
```

And then create a pull request against this repository.

We will accept the pull request, and your private work repo will be registered for the class at that point.

# Other Things To Know

### Word of Caution

In CSCI 460 it is highly recommended that students **DO NOT** clone their public fork of this repository to their local system.
This is to avoid confusion between your public and private repos.
If this applies to you (i.e., you are prone to confusion), you should know that there is no need to have the public repo on your local system;
you can edit files in the public repository via the web interface and submit pull requests there too.

### Programming Assignments (PA)

Once you've created your **private repository**, you can create separate directories for each assignment.
Each programming assignment should be kept in its own directory (`/pa0`, `/pa1`, `/pa2`, etc.).
Please do your solo work in the appropriate homework directory.
Remember, **DO NOT PUSH YOUR INDIVIDUAL WORK CODE TO THE PUBLIC REPOSITORY**

### Setup An SSH Identity

Setting up an SSH identity makes it possible for you to interact with GitHub repos via the command line
without having to re-enter your password all the time.
If you've already setup an SSH key to have passwordless access to GitHub on the command line, you can probably skip this step.
You can check to see if you have a key setup by looking in your `~/.ssh/` directory.
If there is nothing there, or if you don't have a key dedicated to using with GitHub, you should read on.

> **NOTE: **You _should_ be able to run the following commands as-is, but know that I haven't tested how this works on Windows...

```bash
# make sure you are in your ~/.ssh/ folder
# (this is where you will stash SSH keys, a config file, etc.)
cd ~/.ssh

# generate your SSH keypair...
ssh-keygen -t rsa -b 4096 -f ~/.ssh/id_rsa_github -C "id_rsa_github is an SSH key specifically for GitHub work"
# You can hit enter twice to indicate "no passphrase".
```

> **SECURITY TIP:** In theory you should use a non-empty passphrase to protect your SSH keys.
> In practice we may decide that usability/access outweighs some threats/risks...

### Class Code By The Week

Each week we will likely look at different code examples.
These code examples help us practice tools we use, help us to understand how an OS implements something, etc.
For weeks with code examples, a new directory (`weekN`) will be added to help us organize our examples.

### VirtualBox and Vagrant

The most important file here IMHO is our class `Vagrantfile`.
This file contains the configuration for the VM we are using in this class.

### "Synced Folder" (a.k.a. "Shared Folder")

In class we've talked about using _shared folders_ to share files between your host OS and your guest OS.
Once you know you've cloned the repo to your local system you can add a line like this to your `Vagrantfile`:

```bash
config.vm.synced_folder "/Users/myHome/dir/where/I/work/cs460-code", "/home/vagrant/code"
# Note that we are using the absolute path here.
# I've had mixed results with using symbols that expand  to the correct directory
# (E.g., '~' for 'home directory). Try at your own risk...
```

Now when we access our VM, there should be a directory (`~/code`) in the VM that is synchronized between the host and guest.

This will enable you to, for example, edit code in your preferred editor on your host,
and compile/run code on the guest.

At the very least, however, means that your code is not actually stored on the VM; code is stored on your host.
This enables you to delete (`vagrant destroy`) your VM, create a new VM, and pick right up where you left off with your work.

_**WARNING:**_ This means you need to make sure you never save files that you want to keep directly to the VM.
Important files should be stored on the host and version-controlled with Git/GitHub.
