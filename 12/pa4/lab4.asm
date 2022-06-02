# Fall 2021 CSE12 Lab 4 Template
######################################################
# Macros made for you (you will need to use these)
######################################################

# Macro that stores the value in %reg on the stack 
#	and moves the stack pointer.
.macro push(%reg)
	subi $sp $sp 4
	sw %reg 0($sp)
.end_macro 

# Macro takes the value on the top of the stack and 
#	loads it into %reg then moves the stack pointer.
.macro pop(%reg)
	lw %reg 0($sp)
	addi $sp $sp 4	
.end_macro

#################################################
# Macros for you to fill in (you will need these)
#################################################

# Macro that takes as input coordinates in the format
#	(0x00XX00YY) and returns x and y separately.
# args: 
#	%input: register containing 0x00XX00YY
#	%x: register to store 0x000000XX in
#	%y: register to store 0x000000YY in
.macro getCoordinates(%input %x %y)
	# YOUR CODE HERE
	
	srl %x, %input, 16
	la $t1, (%x)
	
	sll $t1, $t1, 16
	sub %y, %input, $t1

	
	
.end_macro

# Macro that takes Coordinates in (%x,%y) where
#	%x = 0x000000XX and %y= 0x000000YY and
#	returns %output = (0x00XX00YY)
# args: 
#	%x: register containing 0x000000XX
#	%y: register containing 0x000000YY
#	%output: register to store 0x00XX00YY in
.macro formatCoordinates(%output %x %y)
	# YOUR CODE HERE
	sll %output, %x, 16		#move x left 16
	add %output, %output, %y	#add y, so output = 0x0000XXYY
	
.end_macro 

# Macro that converts pixel coordinate to address
# 	  output = origin + 4 * (x + 128 * y)
# 	where origin = 0xFFFF0000 is the memory address
# 	corresponding to the point (0, 0), i.e. the memory
# 	address storing the color of the the top left pixel.
# args: 
#	%x: register containing 0x000000XX
#	%y: register containing 0x000000YY
#	%output: register to store memory address in
.macro getPixelAddress(%output %x %y)
	# YOUR CODE HERE
	mul %output, %y, 128		# output = y*128
	add %output, %x, %output	# output = output + x
	mul %output, %output, 4	# output = output*4
	add %output, %output, 0xffff0000	#output = 0xffffXXYY
		
.end_macro


.text
# prevent this file from being run as main


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  Subroutines defined below
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#*****************************************************
# Clear_bitmap: Given a color, will fill the bitmap 
#	display with that color.
# -----------------------------------------------------
# Inputs:
#	$a0 = Color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
clear_bitmap: nop
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)
	
	li $t1, 0xffff0000	
	li $t2, 0		# loop counter
	sw $a0,($t1)		# first dot
	line:
		add $t1, $t1, 4		# iterate one word over
		sw $a0,($t1)		# make dot
		add $t2, $t2, 1		# iterate loop counter
		bge $t2, 16383, n	# break when screen is filled
		j line			# loop
	
 	
	n:
	jr $ra
#*****************************************************
# draw_pixel: Given a coordinate in $a0, sets corresponding 
#	value in memory to the color given by $a1
# -----------------------------------------------------
#	Inputs:
#		$a0 = coordinates of pixel in format (0x00XX00YY)
#		$a1 = color of pixel in format (0x00RRGGBB)
#	Outputs:
#		No register outputs
#*****************************************************
draw_pixel: nop
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)

	getCoordinates($a0, $t0, $t1)		# get coord
	getPixelAddress($t2, $t0, $t1)		# get pixel 
	
	sw $a1, ($t2)				# store color in pixel
	
	jr $ra
	
#*****************************************************
# get_pixel:
#  Given a coordinate, returns the color of that pixel	
#-----------------------------------------------------
#	Inputs:
#		$a0 = coordinates of pixel in format (0x00XX00YY)
#	Outputs:
#		Returns pixel color in $v0 in format (0x00RRGGBB)
#*****************************************************
get_pixel: nop
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)

	getCoordinates($a0, $t0, $t1)		# get coord
	getPixelAddress($t2, $t0, $t1)		# get pixel
	
	lw $v0, 0($t2)				#get color from pixel

	jr $ra

#*****************************************************
# draw_horizontal_line: Draws a horizontal line
# ----------------------------------------------------
# Inputs:
#	$a0 = y-coordinate in format (0x000000YY)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_horizontal_line: nop
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)
	
	sll $t1, $a0, 8		# formatting
	mul $t1, $t1, 2		# formatting
	li $t3, 0xffff0000	# formatting
	add $t1, $t3, $t1	# formatting
	li $t2, 0		# loop counter
	horizontal:
		sw $a1, ($t1)		# draw dot
		add $t1, $t1, 4		# iterate one word over
		add $t2, $t2, 1		# iterate loop
		bge $t2, 128, n2	# break when line reaches edge of screen
		j horizontal
	n2:	
 	jr $ra


#*****************************************************
# draw_vertical_line: Draws a vertical line
# ----------------------------------------------------
# Inputs:
#	$a0 = x-coordinate in format (0x000000XX)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_vertical_line: nop
	
	# YOUR CODE HERE, only use t registers (and a, v where appropriate)
	la $t1, ($a0)		# load $a0 value
	mul $t1, $t1, 4		# align to word boundary
	li $t3, 0xffff0000	# formatting
	add $t1, $t3, $t1	# formatting
	li $t2, 0		# loop counter
	li $t4, 0x00000200	# loop iterator
	vertical:
		sw $a1, ($t1)		# draw dot
		add $t1, $t1, $t4	# iterate one word over
		add $t2, $t2, 1		# iterate loop counter
		bge $t2, 128, n3	# break at edge of sceen
		j vertical
	n3:	
 	jr $ra
	
 
#*****************************************************
# draw_crosshair: Draws a horizontal and a vertical 
#	line of given color which intersect at given (x, y).
#	The pixel at (x, y) should be the same color before 
#	and after running this function.
# -----------------------------------------------------
# Inputs:
#	$a0 = (x, y) coords of intersection in format (0x00XX00YY)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_crosshair: nop
	move $t9, $a0		#storing a0 so I don't lose it
	
	#****using getPixel
	getPixelAddress($t2, $t0, $t1)		# get pixel
	
	lw $t8, 0($t2)				# get color of pixel
	
	getCoordinates($a0, $t6, $t7)		# get coord
	move $t0, $t6				# store into temp
	move $t1, $t7				# store into temp
	
	#****************
	
	move $a0, $t7		# $a0 = 0x000000YY
	
	#****using draw_horizontal_line

	sll $t1, $a0, 8		# formatting
	mul $t1, $t1, 2		# formatting
	li $t3, 0xffff0000	# formatting
	add $t1, $t3, $t1	# formatting
	li $t2, 0		# loop counter
	horizontal_crosshair:
		sw $a1, ($t1)		# draw dot
		add $t1, $t1, 4		# iterate one word over
		add $t2, $t2, 1		# iterate loop counter
		bge $t2, 128, n2_crosshair	# break at edge of screen
		j horizontal_crosshair
	n2_crosshair:
	#****************
	
	move $a0, $t6		# $a0 = 0x000000XX
	
	#****draw_vertical_line	
	la $t1, ($a0)		# load $a0 value
	mul $t1, $t1, 4		# align to word boundary
	li $t3, 0xffff0000	#formatting
	add $t1, $t3, $t1	#formatting
	li $t2, 0		# loop counter
	li $t4, 0x00000200	# loop iterator value
	vertical_crosshair:
		sw $a1, ($t1)		# draw dot
		add $t1, $t1, $t4	# iterate one word over
		add $t2, $t2, 1		# iterate loop counter
		bge $t2, 128, n3_crosshair	#break at edge of screen
		j vertical_crosshair
	n3_crosshair:	
	
	#****using draw_pixel
	
	getCoordinates($t9, $t0, $t1)		# get coord
	getPixelAddress($t2, $t0, $t1)		# get pixel
	
	sw $t8, ($t2)		# make crosshair dot
	
	# HINT: Store the pixel color at $a0 before drawing the horizontal and 
	# vertical lines, then afterwards, restore the color of the pixel at $a0 to 
	# give the appearance of the center being transparent.
	
	# Note: Remember to use push and pop in this function to save your t-registers
	# before calling any of the above subroutines.  Otherwise your t-registers 
	# may be overwritten.  
	
	# YOUR CODE HERE, only use t0-t7 registers (and a, v where appropriate)

	

	# HINT: at this point, $ra has changed (and you're likely stuck in an infinite loop). 
	# Add a pop before the below jump return (and push somewhere above) to fix this.

	jr $ra
end:	
li $v0 10 
syscall
.data 