.section .data
message:
    .asciz "Min = %d, max = %d, sub = %d\n"
array:
      .int 541,72,37,41,542,64,72,58,19,100
minvalue:
      .int 0
maxvalue:
      .int 0
subtract:
      .int 0
.section .text
.globl _start
_start:
       mov $array, %rdi
       mov  $10, %rsi
       call getmax
       movl %eax, maxvalue

       mov $array, %rdi
       mov $10, %rsi
       call getmin
       movl %eax, minvalue

       sub  (maxvalue), %eax
       neg %eax
       movl %eax, subtract

       mov $message, %rdi
       movl (minvalue), %esi
       movl (maxvalue), %edx
       movl (subtract), %ecx
       call printf

       mov	$60, %rax
       mov	$0,  %rdi
       syscall
