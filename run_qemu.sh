#!/bin/sh

set -e -x

if [ $# -lt 1 ]
then
    echo "Usage: $0 DISK_IMG"
    exit 1
fi

cd $(dirname $0)
DISK_IMG=$1

if [ ! -f $DISK_IMG ]
then
    echo "file not found: $DISK_IMG"
    exit 1
fi

qemu-img create -f raw disk.img 200M
mkfs.fat -n 'EBIIIM OS' -s 2 -f 2 -R 32 -F 32 disk.img
mkdir -p mnt
sudo mount -o loop disk.img mnt
sudo mkdir -p mnt/EFI/BOOT
sudo cp ${DISK_IMG} mnt/EFI/BOOT/BOOTX64.EFI
sudo umount mnt
rm -rf mnt

qemu-system-x86_64 \
  -drive if=pflash,file=$HOME/osbook/devenv/OVMF_CODE.fd \
  -drive if=pflash,file=$HOME/osbook/devenv/OVMF_VARS.fd \
  -hda disk.img
