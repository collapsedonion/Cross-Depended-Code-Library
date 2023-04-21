
.global _cdc_invoke
_cdc_invoke:
	str x9, [sp, #-16]!
	str x10, [sp, #-16]!
	str x11, [sp, #-16]!
	str x19, [sp, #-16]!
	str x13, [sp, #-16]!
	str x14, [sp, #-16]!
	str x15, [sp, #-16]!
	str x12, [sp, #-16]!
	str lr, [sp, #-16]!
	str fp, [sp, #-16]!
	sub sp, sp, #16

	mov x9, x0
	mov x10, x1
	mov x11, x2

	_if:
	cmp x10, #0
	b.ls _endif
	ldr x0, [x11]
	sub x10, x10, #1
	
	cmp x10, #0
	b.ls _endif
	add x11, x11, #8
	ldr x1, [x11]
	sub x10, x10, #1

	cmp x10, #0
	b.ls _endif
	add x11, x11, #8
	ldr x2, [x11]
	sub x10, x10, #1

	cmp x10, #0
	b.ls _endif
	add x11, x11, #8
	ldr x3, [x11]
	sub x10, x10, #1

	cmp x10, #0
	b.ls _endif
	add x11, x11, #8
	ldr x4, [x11]
	sub x10, x10, #1

	cmp x10, #0
	b.ls _endif
	add x11, x11, #8
	ldr x5, [x11]
	sub x10, x10, #1

	cmp x10, #0
	b.ls _endif
	add x11, x11, #8
	ldr x6, [x11]
	sub x10, x10, #1

	cmp x10, #0
	b.ls _endif
	add x11, x11, #8
	ldr x7, [x11]
	sub x10, x10, #1

	_endif:
	
	mov x19, sp

	blr x9

	mov sp, x19

	add sp, sp, #16
	ldr fp, [sp], #16
	ldr lr, [sp], #16
	ldr x12, [sp], #16
	ldr x15, [sp], #16	
	ldr x14, [sp], #16
	ldr x13, [sp], #16
	ldr x19, [sp], #16
	ldr x11, [sp], #16
	ldr x10, [sp], #16
	ldr x9, [sp], #16
	ret
	
