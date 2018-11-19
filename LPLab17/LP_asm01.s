.section .data
array:
      .int 100,95,90,80,70,60,40,30,50,55
.section .text
.globl _start
_start:
       nop

       mov   $array, %rdi
       mov   $10, %rsi
       call getmin

       mov    $60,  %rax
       mov    $0,   %rdi
       syscall

getmin:
       cmp    $0,   %rsi     #check if first param is zero
       jz getminend

       mov    $0,   %rax
       mov    $0,   %r12
getminloop:
       movl (%rdi, %r12, 4), %r13d
       cmpl %r13d, (%rdi, %rax, 4)
       cmova %r12, %rax
       inc %r12
       cmp %r12, %rsi
       jnz getminloop
getminloopend:
       movl (%rdi, %rax, 4), %eax
getminend:
       ret
