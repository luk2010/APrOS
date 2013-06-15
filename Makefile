# Atlanti's Project Operating System Makefile
# Use the main target to create the iso image. It will create the 'apros.iso' image that you an use
# to boot the Operating System.
# You must have a valid grub installation to perform the image creation.

CC=gcc
CFLAGS  = -Wall -nostdlib -nostdinc -ffreestanding -march=i386 -m32
LDFLAGS = --warn-common -melf32_x86_64 --gc-sections

OBJECTS = bootstrap/boot.o kernel/kernel.o
KERNEL_OBJ   = kernel.elf

MULTIBOOT_IMAGE = apros.iso
PWD := $(shell pwd)

# main target
all: $(MULTIBOOT_IMAGE)

#Iso target
$(MULTIBOOT_IMAGE): $(KERNEL_OBJ)
	mkdir iso/
	mkdir -p iso/boot/grub
	cp extra/grub.cfg iso/boot/grub/grub.cfg
	cp $(KERNEL_OBJ) iso/$(KERNEL_OBJ)
	grub-mkrescue -o $(MULTIBOOT_IMAGE) iso

#kernel image
$(KERNEL_OBJ): $(OBJECTS) ./support/apros.lds
	$(LD) $(LDFLAGS) -T ./support/apros.lds -o $@ $(OBJECTS)
	-nm -C $@ | cut -d ' ' -f 1,3 > apros.map

# Create objects from C source code
%.o: %.c
	$(CC) -I$(PWD) -c $< $(CFLAGS) -o $@

# Create objects from assembler (.S) source code
%.o: %.S
	$(CC) -I$(PWD) -c $< $(CFLAGS) -DASM_SOURCE=1 -o $@

# Clean directory
clean:
	$(RM) *.img *.o mtoolsrc *~ menu.txt *.img *.elf *.bin *.map *.iso
	$(RM) *.log *.out bochs*
	$(RM) bootstrap/*.o bootstrap/*~
	$(RM) kernel/*.o kernel/*~
	$(RM) support/*~
	$(RM) extra/*~
	$(RM) -r iso

