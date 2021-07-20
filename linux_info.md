# Linux Info

## Basic Setup
1. `sudo apt-get install vim`

## Turn of and Disable Swap
* `sudo swapoff -a`
* Remove swap from fstab

## Set Default Editor
`sudo update-alternatives --config editor`

## No Password Sudo
* `sudo visudo`
* add `<user> ALL=(ALL) NOPASSWD: ALL` on last line.

