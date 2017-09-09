/*Procedures to set state of the ACT LED.
*/

.section .data
.align 4
PropertyInfo:
	/*Message header*/
	.int PropertyInfoEnd - PropertyInfo 	/*size of data */
	.int 0					/*requst code - process req*/
	/*Tag header*/
	.int 0x00038041				/*tag id*/
	.int 8					/*size of tag data*/
	.int 0					/*req/resp size*/
	/*Tag data*/
	.int 130				/*pin number*/
	.int 1					/*pin data - turn on*/
	.int 0					/*end tag*/
PropertyInfoEnd:

.section .text
.global SetACTState
/* this subroutine sets the state of the ACT LED. the state (1=on, 0=off) is expected to be passed in r0 */
SetACTState:
	push	{lr}
	state	.req	r2
	mov	state,	r0
	
	message	.req	r0
	ldr	message,=PropertyInfo

	mov	r3,	#0
	str	r3,	[message,#0x4] /*set req code*/
	str	r3,	[message,#0x10] /*set req/resp size*/
	mov	r3,	#130
	str	r3,	[message,#0x14] /*reset pin number*/

	str	state,	[message, #0x18] /*set state*/
	mov	r1,	#8

	.unreq	state
	.unreq	message

	bl	MBWrite

	mov	r0,	#8
	bl	MBRead
	
	pop	{pc}
