        global port_read_byte
port_read_byte:
        mov dx, [esp + 4]       ; the port to read from
        in  al, dx
        ret

        global port_write_byte
port_write_byte:
        mov al, [esp + 8]       ; the byte to be written
        mov dx, [esp + 4]       ; the port to write to
        out dx, al
        ret
