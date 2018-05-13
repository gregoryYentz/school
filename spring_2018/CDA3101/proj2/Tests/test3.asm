	.text
	ori	$s0,$0,68
	ori	$t4,$0,999
	lw	$t1,0($s0)
	lw	$t0,8($s0)
	lw	$t2,4($s0)
	ori	$s1,$0,1
	sub	$t0,$t0,$t1
	add	$t4,$t4,$s1
	noop
	sub	$t2,$t1,$t0
	noop
	add	$t3,$t1,$t2
	noop
	sw	$t3,8($s0)
	sw	$t2,12($s0)
	sll	$t0,$t1,1
	halt
	.data
Data1:	.word	12
Data2:	.word	25
Data3:	.word	19
