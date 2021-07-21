sudo apt-get autoremove# Linux Info

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

## VMWare Shared Folders
Add this to `/etc/fstab` to allow vmware shared folders to actually work:
```bash
# Allow VMWare Shared Folders to work:
.host:/         /mnt/hgfs       fuse.vmhgfs-fuse        defaults,allow_other,uid=1000   0       0
```
## Completely Remove Libre Office
```bash
> sudo apt-get remove --purge libreoffice*
> sudo apt-get clean
> sudo apt-get autoremove
```
And check with:
```aptitude search '~i' | grep libreoffice```
