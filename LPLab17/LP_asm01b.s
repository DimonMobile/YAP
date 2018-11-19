.section .data
array:
      .int 541,72,37,41,542,64,72,58,19,100
minvalue:
      .int 0
.section .text
.globl _start
_start:
       mov $array, %rdi
       mov $10, %rsi
       call getmin
       movl %eax, minvalue
       mov array, %rdi
       mov $10, %rsi
       call getmax
       mov	$60, %rax
       mov	$0, %rdi
       syscall
