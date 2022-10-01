main:
  addi $a0, $0, 10
  jal fib
  addi $s0, $v0, 0
end:
  j end
fib:
  addi $sp, $sp, -12
  sw $ra, 0($sp)
  sw $s0, 4($sp)
  sw $s1, 8($sp)
  addi $t0, $0, 2
  slt $t0, $a0, $t0
  beq $t0, $0, else
  addi $v0, $a0, 0
  j close
else:
  addi $s0, $a0, 0
  addi $a0, $s0, -1
  jal fib
  addi $s1, $v0, 0
  addi $a0, $s0, -2
  jal fib
  add $v0, $v0, $s1
close:
  lw $ra, 0($sp)
  lw $s0, 4($sp)
  lw $s1, 8($sp)
  addi $sp, $sp, 12
  jr $ra
