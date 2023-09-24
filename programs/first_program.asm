; My first program
mov  a, 0x05
inc  a
call function
msg  '(5+1)/2 = ', a    ; output message
end

function:
    div  a, 0x02
    ret
