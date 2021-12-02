	.arch msp430g2553
	.p2align 1,0
	.text

	.global dimBoth50
	.extern P1OUT

dimBoth50:
	cmp #1, r12
	jne caseTwo
	bis #64, &P1OUT
	and #~65, &P1OUT
	pop r0
	
caseTwo:
	cmp #2, r12
	jne caseThree
	bis #64, &P1OUT
	and #~65, &P1OUT
	pop r0

caseThree:
	cmp #3, r12
	jne caseFour
	bis #65, &P1OUT
	and #~64, &P1OUT
	pop r0

caseFour:
	cmp #4, r12
	jne default
	bis #65, &P1OUT
	and #~64, &P1OUT
	pop r0

default:
	pop r0

	
