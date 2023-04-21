
.intel_syntax noprefix

.text

.global cdc_invoke
cdc_invoke:
	push r10
	push r11
	push r12
	push r13

	mov r10, rcx
	mov r11, rdx 
	mov r12, r8

	mov r13, r11

	._if_:
	
	cmp r13, 0
	je ._end_if_
	mov rcx, [r12]
	sub r13, 1

	cmp r13, 0
	je ._end_if_
	add r12, 8
	mov rdx, [r12]
	sub r13, 1

	cmp r13, 0
	je ._end_if_
	add r12, 8
	mov r8, [r12]
	sub r13, 1

	cmp r13, 0
	je ._end_if_
	add r12, 8
	mov r9, [r12]
	sub r13, 1


	._end_if_:

	call r10

	pop r13
	pop r12
	pop r11
	pop r10
	ret
