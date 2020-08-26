# CSCI 460 - Operating Systems!

This is the base upstream repository for CSCI 460.
This repository is mostly intended to contain examples from class and serve as an example Github repository for students.

## What's Here?

Each week we will likely look at different code examples.
These code examples help us practice tools we use, help us to understand how an OS implements something, etc.
Each week a new directory (`weekN`) will be added to help us organize our examples.

The most important file here is our class `Vagrantfile`.
This file contains the configuration for the VM we are using in this class.

## Getting Started

Easy peasy! *(Assuming you have Git installed on your machine and an Internet connection.)*

> **NOTE:** My examples are all based on a unix-y terminal running atop macOS.
> If you use a different OS (e.g., Windows) your mileage may vary.

Open a terminal and run the following commands:

```bash
# for example: `~/projects/cs460/`
cd ~/dir/where/I/work/
git clone git@github.com:traviswpeters/cs460-code.git
cd cs460-code
```

If you do this, you'll want to run `git pull` from time to time so you get updates to this repository.

### "Synced Folder" (a.k.a. "Shared Folder")

In class we've talked about using _shared folders_ to share files between your host OS and your guest OS.
If we use keep running with our example above and use the directory where we created our `cs460-code` repo,
we can add the following line to our `Vagrantfile`.

```bash
config.vm.synced_folder "/Users/myHome/dir/where/I/work/cs460-code", "/home/vagrant/code"
# Note that we are using the absolute path here.
# I've had mixed results with using symbols that exapand to the correct directory
# (E.g., '~' for 'home directory). Try at your own risk...
```

Now when we access our VM there should be a directory (`~/code`) in the VM that is syncronized between the host and guest.

### Fork vs. Clone

Cloning this repo is a super easy way to download THIS repo to your machine.
You can then run `git pull` to get updates (e.g., run it before/after each class).
Think of this like a little sandbox where you can keep up-to-date with class code.

Alternatively, you can fork this repo to your personal account.
You can then configure an upstream remote to pull in changes from this repo.
This will also allow you to extend the repo as you please without stepping on anything we do here.
It also gives you the opportunity to contribute code back to this repo (talk to me if you have ideas for said contributions).

There may be instances where I ask you to contribute back to this repo (e.g., PA0).

At the end of the day, just remember:

**DO NOT PUSH ANY OF YOUR PRIVATE CODE TO THIS REPOSITORY!**
