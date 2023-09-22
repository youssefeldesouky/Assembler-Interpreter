; Fibonacci Program
mov   a, 8  ; Original Value
mov   d, a  ; Counter
mov   b, 0  ; F(n-1)
mov   c, 1  ; F(n)

loop:
    cmp     d, 0
    je      finish
    call    fibo
    dec     d
    jmp     loop

finish: call        print
        end

fibo:
    mov     e, b
    add     e, c
    mov     b, c
    mov     c, e
    ret

print:
    msg     "fibo(", a, ') = ', b
    ret
