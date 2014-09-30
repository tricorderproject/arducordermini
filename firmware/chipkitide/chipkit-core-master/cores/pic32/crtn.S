	.section .init,"ax",@progbits
	lw	$31,20($sp)
	addu	$sp,$sp,32
	j	$31

	.section .fini,"ax",@progbits
	lw	$31,20($sp)
	addu	$sp,$sp,32
	j	$31

