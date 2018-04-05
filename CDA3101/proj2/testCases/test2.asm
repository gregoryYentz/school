	.text
	ori	$s0,$s0,40
	lw	$t0,0($s0)
loop:	sll	$t0,$t0,2
	sw	$t0,4($s0)
	andi	$t1,$t0,1
	sub	$t2,$t1,$t0
	add	$t1,$t1,$t2
	bne	$t1,$t0,loop
	noop
	halt
	.data
Data1:	.word	60


