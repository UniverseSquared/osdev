        MULTIBOOT_MAGIC    equ 0x1BADB002
        MULTIBOOT_FLAGS    equ 0x0
        MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

        KERNEL_STACK_SIZE equ 4096
        section .bss
        align 4
kernel_stack:
        resb KERNEL_STACK_SIZE
kernel_stack_end:

        section .multiboot
        align 4
        dd MULTIBOOT_MAGIC
        dd MULTIBOOT_FLAGS
        dd MULTIBOOT_CHECKSUM

        section .text
        global boot
boot:   mov esp, kernel_stack_end

        extern kmain
        call kmain

halt:   hlt
        jmp halt
