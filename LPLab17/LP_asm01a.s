.section .data
.section .text
.globl getmin
.globl getmax

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

getmax:
       cmp    $0,   %rsi     #check if first param is zero
       jz getmaxend

       mov    $0,   %rax
       mov    $0,   %r12
getmaxloop:
       movl (%rdi, %r12, 4), %r13d
       cmpl %r13d, (%rdi, %rax, 4)
       cmovb %r12, %rax
       inc %r12
       cmp %r12, %rsi
       jnz getmaxloop
getmaxloopend:
       movl (%rdi, %rax, 4), %eax
getmaxend:
       ret
