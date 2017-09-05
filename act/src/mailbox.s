/*subroutines for mailbox communication between ARM and video core*/

/*Mailbox base address: 0x3f00b880
  Mailbox 1 read offset: 0x0
  Mailbox 1 status offset: 0x18
  Mailbox 1 write offset: 0x20
*/

.section .text

/*Subroutine for writing a message to mailbox 1
  (ARM -> video core)
*/
.global MBWrite
MBWrite:
	message	.req	r0
	add	message,r1
	mailbox	.req	r2
	ldr	mailbox,=0x3f00b880
	
	wait_write$:
		status	.req	r3
		ldr	status,	[mailbox, #0x18]
		tst	status, #0x80000000
		.unreq	status
		bne	wait_write$

	str	message,[mailbox,#0x20]
	.unreq	mailbox
	.unreq	message
	
	mov	pc,	lr
