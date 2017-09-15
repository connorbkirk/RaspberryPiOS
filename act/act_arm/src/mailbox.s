/*subroutines for mailbox communication between ARM and video core*/

/*Mailbox base address: 0x3f00b880
  Mailbox 1 read offset: 0x0
  Mailbox 1 status offset: 0x18
  Mailbox 1 write offset: 0x20

  Mailbox 1 full: 0x80000000
  Mailbox 1 empty: 0x40000000
*/

.section .text

/*Subroutine for writing a message to mailbox 1
  (ARM -> video core)
  Params:{
	r0 -> message address
	r1 -> channel
  }
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

/*subroutine for reading a message from mailbox 1
  (video core -> ARM)
  Params:{
	r0 -> channel
  }
  Return:{
	r0 -> response
  }
*/
.global MBRead
MBRead:
	channel	.req	r0	
	mailbox	.req	r1
	respons	.req	r2
	ldr	mailbox,=0x3f00b880
	
	wait_read$:
		status	.req	r3
		ldr	status, [mailbox, #0x18]
		tst	status, #0x40000000
		.unreq 	status
		bne	wait_read$

		ldr	respons, [mailbox]
		r_chan	.req	r3
		and	r_chan,	respons,#0b1111
		teq	r_chan,	channel
		.unreq	r_chan
		bne	wait_read$

	mov	r0, 	respons
	
	.unreq	respons
	.unreq	mailbox
	.unreq	channel

	mov	pc,	lr

