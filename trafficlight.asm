.eqv EXT_INTTIME 0x0400 #mask for timer interrupt (external), bit 10
.eqv CLEAR_TIME 0xFFFFFBFF #mask for clearing timer interrupt, bit 10
.eqv EXT_INTBUTTON 0x0800 #mask for button interrupt (external), bit 11
.eqv CLEAR_BUTTON 0xFFFFF7FF #mask for clearing button interrupt, bit 11
.eqv CLEAR_TB 0xFFFFF3FF #mask for clearing time and button interrupts, bits 10-11
.eqv EXCHMASK 0x007C #mask for exceptions (internal), bits 2-6

.eqv ENABLE_TIMER_ADR 0xFFFF0012 #I/O enabling timer
	.eqv ENABLE_TIMER 0x01 	#mask for enabling timer
.eqv BUTTONADDR 0xFFFF0013 #I/O button address
.eqv WALKLIGHT 0xFFFF0010 #I/O walk light address
.eqv DRIVLIGHT 0xFFFF0011 #I/O driver light address

.eqv WALK_BUTTON 0x01 #mask for pedestrian button
.eqv DRIV_BUTTON 0x02 #mask for car button
.eqv PRED_CGREEN 0x01 #state value
.eqv PGREEN_CRED 0x02 #state value
.eqv PRED_CORG	 0x03 #orange state
.eqv DARK 0x00 #traffic lights
.eqv STOP 0x01 #traffic lights (ped), bit 0
.eqv WALK 0x02 #traffic lights (ped), bit 1
.eqv RED 0x01 #traffic lights (car), bit 0
.eqv ORANGE 0x02 #traffic lights (car), bit 1
.eqv GREEN 0x04 #traffic lights (car), bit 2
.eqv RESET_BUTTON 0x00	# reset button after WALK_BUTTON
	.data
state: .space 1
button: .space 1	# 1 byte	walk: 0x01 , car: 0x02
    .ktext 0x80000180     # interrup starter
    la $k0, int_routine
    jr $k0
    nop
    
	.text
.globl main
main:
    mfc0 $t0, $12 #prepare status register for timer and button interrupt
    ori $t0, $t0, EXT_INTTIME
    ori $t0, $t0, EXT_INTBUTTON
    ori $t0, $t0, 1
    mtc0 $t0, $12

    li $t0, PRED_CGREEN #initialize state (red for ped and green for car)
    sb $t0, state
    li $t0, STOP #put traffic lights on (red for ped)
    sb $t0, WALKLIGHT
    li $t0, GREEN #put traffic lights on (green for car)
    sb $t0, DRIVLIGHT
    
	li $t0, ENABLE_TIMER #enable the timer (t0 > 0)
    sb $t0, ENABLE_TIMER_ADR

loop: #infinite loop, waiting for interrupts
    nop
    b loop
    li $v0, 10 #exit
    syscall
    
.globl int_routine
int_routine:
    subu $sp, $sp, 24 # save registers used (not k0, k1)
    sw $at, 16($sp) 
    sw $t0, 12($sp)
    sw $t1, 8($sp)
    sw $s0, 4($sp)
    sw $s1, 0($sp)

    mfc0 $k1, $13 #extract EXCCODE field from Cause register
    andi $k0, $k1, EXCHMASK #extract EXCCODE (bits 2-6)
    bne $k0, $zero, restore #check EXCCODE (if nonzero leave)

    andi $k0, $k1, EXT_INTTIME #extract bit 10 (timer) from Cause register
	bne $k0, $zero, timer #if timer interrupt check timer
    andi $k0, $k1, EXT_INTBUTTON #extract bit 11 (button) from Cause register
    beq $k0, $zero, restore #if no button interrupt leave
    lb $t0, BUTTONADDR #check which button    
    sb $t0, button		# save pressed button into button variable
    andi $t1, $t0, WALK_BUTTON
    bne $t1, $zero, timer
    andi $t1, $t0, DRIV_BUTTON
    bne $t1, $zero, timer    

    b restore

timer:
	addi $s0, $s0, 1	# Time counter
	lb $t0, state		# if ped state and timer greatter than 7 => go to car
	beq $t0, PRED_CORG, ped	        # state 3: orange
	beq $t0, PGREEN_CRED, check_car	# state 2: PG_CR
	beq $t0, PRED_CGREEN, check_ped	# state 1: PR_CG
	b restore

check_ped:	
	blt $s0, 10, restore    # if (timer >= 10) : ped ? restore
	lb $t0, button		# it should be reseted after states 1 and 2
	beq $t0, WALK_BUTTON, ped	
	b restore
ped:
    lb $t0, state #handling pedestrian button
    beq $t0, PGREEN_CRED, restore
    li $t0, ORANGE #switch traffic lights to ORANGE
    sb $t0, DRIVLIGHT
    
    li $t0, PRED_CORG   # orange state 0x03
    sb $t0, state
	addi $s1, $s1, 1	# orange timer
	blt $s1, 4, restore # if (orange_timer < 4): restore 
	
    li $t0, RED #switch traffic lights to RED
    sb $t0, DRIVLIGHT
    li $t0, WALK 
    sb $t0, WALKLIGHT #switch walk lights to GREEN
    li $t0, PGREEN_CRED
    sb $t0, state
    li $t0, RESET_BUTTON	# to stop the rotational WALK and TRAFFIC LIGHT
    sb $t0, button
    li $s0, 0	# reset overall timer
    li $s1, 0	# reset orange timer
    b restore
    
check_car:
	bge $s0, 7, car		# if (timer >= 7): car ? restore
	b restore
car:
    lb $t0, state #handling car button
    beq $t0, PRED_CGREEN, restore
    bge $s1, 4, orange_light # 3-4 time unit flashing red, then orange 
flashing:
    li $t0, STOP # flashing WALKLIGHT  
    sb $t0, WALKLIGHT
    li $t0, DARK
    sb $t0, WALKLIGHT
    li $t0, STOP #switch traffic lights and state
    sb $t0, WALKLIGHT
    addi $s1, $s1, 1
    blt $s1, 4, restore
orange_light:
	li $t0, ORANGE #switch traffic lights to ORANGE
    sb $t0, DRIVLIGHT
    
    addi $s1, $s1, 1
    blt $s1, 8, restore	# 3-4 time unit orange, then green    
green:    
    li $t0, GREEN	# green car
    sb $t0, DRIVLIGHT
    li $t0, PRED_CGREEN
    sb $t0, state
    li $t0, RESET_BUTTON	# to prevent the rotational WALK and TRAFFIC LIGHT
    sb $t0, button
    li $s0, 0	# reset overall timer
    li $s1, 0	# reset orange timer

restore: 
    lw $at, 16($sp) # restore registers before leaving
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    lw $s0, 4($sp)
    lw $s1, 0($sp)
    addiu $sp, $sp, 24

    andi $k1, $k1, CLEAR_TB # clear bit 10 and 11 (button and timer) in Cause reg., set to 0    
    mtc0 $k1, $13 #clear Cause
    eret #return using EPC
