##########################################################################
# Created by:  Totten, Maxwell
# 		#1799187
# 		14 November 2021
#
# Assignment:   Lab 3: ASCII-Risks (Asterisks)
# 	        CSE 012, Computer Systems and Assembly Language
# 	        UC Santa Cruz, Fall 2021
#
# Description:  In this lab, we created an asterisk triangle to a user-inputted height. 
#		 Jumps were used to create for and while loops to complete this lab.
#
# Notes: 	 This program is intended to be run from the MARS IDE.
##########################################################################
.text

li $v0, 4		#print string
la $a0, prompt		#a0 = prompt
syscall			#initial prompt

li $v0, 5		#read input
syscall			#read input

move $t0, $v0		# $v0 -> $t0

while: 		
	bgt $t0, 0, break		#while input < 0...
	li $v0, 4			#print string
	la $a0, retry			#print "Invalid Input!"
	syscall
	
	li $v0, 4			#print string
	la $a0, new_line		#a0 = new_line
	syscall
	
	li $v0,4			#print string
	la $a0, prompt			#a0 = prompt
	syscall
	
	li $v0, 5			#read input
	syscall
	
	move $t0, $v0			# $v0 -> $t0
	j while				#continue while loop

break:			#end of while loop

num_loop: NOP
li $t2, 1		#initialize $t2 to 1, because asterisk triangle starts at 2


bge  $t1, $t0, program_exit #loop for numbers
li $v0, 1		#print integer
addi $t1, $t1, 1	#increment $t1
la $a0, ($t1)		#a0 = $t1
syscall

num_loop2: NOP

bge $t2, $t1, num_loop3 #nested loop for asterisks
li $v0, 4		#print string
la $a0, tab_asterisk	#a0 = tab_asterisk
addi $t2, $t2, 1	#increment $t2
syscall

j num_loop2		#jump to nested loop

num_loop3: 		#new line after asterisks
li $v0, 4		#print string
la $a0, new_line	#a0 = new_line
syscall

j num_loop		#jump to outer loop

program_exit: 		#exit program
li $v0, 10		#exit
syscall

.data

new_line: .asciiz "\n"
tab_asterisk: .asciiz "	*"
prompt: .asciiz "Enter the height of the pattern (must be greater than 0):\n"
retry: .asciiz "Invalid Entry!"
