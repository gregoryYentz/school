	.text
	ori	$s0,$0,36
	ori	$s1,$0,13
	sub	$s2,$s0,$s1
	sub	$s3,$s1,$s0
	halt
	.data
Data1:	.word	15
Data2:	.word	25
