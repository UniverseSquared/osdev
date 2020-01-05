        global flush_gdt
flush_gdt:
        mov eax, [esp + 4]
        lgdt [eax]

        ;; Ensure that the segment selector registers contain the correct value
        ;; for the kernel data segment.
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax

        ;; Loading the correct kernel code segment into cs requires a far jump.
        jmp 0x08:flush_cs
flush_cs:
        ret
