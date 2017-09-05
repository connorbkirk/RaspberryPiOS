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

	str	state,	[message, #0x18] /*set state*/

	.unreq	state
	.unreq	message

	bl	MBWrite
	
	pop	{pc}
