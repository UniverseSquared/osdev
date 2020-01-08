# osdev

A small x86 kernel that doesn't do much.

## Building

Building the kernel requires an i686-elf GCC cross-compiler. Assuming you have
this installed, building can be done as follows:

```bash
$ git clone https://github.com/UniverseSquared/osdev.git
$ cd osdev
$ make
```

The built `kernel.elf` can then be booted using a multiboot-compliant bootloader
such as [GRUB](https://www.gnu.org/software/grub/), or under QEMU using the
command `make run` or `make run-kvm` to enable KVM and use your host CPU for the VM.
