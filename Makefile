# Atlanti's Project Operating System Makefile
# Use the main target to create the iso image. It will create the 'apros.iso' image that you an use
# to boot the Operating System.
# You must have a valid grub installation to perform the image creation.

AS=~/opt/cross/bin/i586-elf-as
CC=~/opt/cross/bin/i586-elf-gcc

all:
	# Bootstrap
	$(AS) bootstrap/boot.s -o bootstrap/boot.o

	# Kernel
	$(CC) -c kernel/kernel.c -o kernel/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

	# Linking
	$(CC) -T support/apros.lds -o apros.bin -ffreestanding -O2 -nostdlib bootstrap/boot.o kernel/kernel.o

	# Creating bootable iso file.
	mkdir -p iso
	mkdir -p iso/boot
	cp apros.bin iso/boot/kernel.bin
	mkdir -p iso/boot/grub
	cp extra/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o apros.iso iso

test_qemu: all
	qemu-system-i386 -cdrom apros.iso

# Clean directory
clean:
	$(RM) *.img *.o mtoolsrc *~ menu.txt *.img *.elf *.bin *.map *.iso
	$(RM) *.log *.out *.bochs
	$(RM) bootstrap/*.o bootstrap/*~
	$(RM) kernel/*.o kernel/*~
	$(RM) support/*~
	$(RM) extra/*~
	$(RM) -r iso
	$(RM) -r boot

