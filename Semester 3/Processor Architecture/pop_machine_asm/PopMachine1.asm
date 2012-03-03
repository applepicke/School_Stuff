; PopMachine1.asm
;
;Authors:               Curtis Collins & Nicolas Castilloux
;Student Number         000000000 & 040600517
;Date                   29 Nov 2010
;Purpose:               Dispense fizzy drinks which cost 3 coins each!


COST    equ     3                       ; Cost of pop in coins
NUMPOP  equ     15                      ; Maximum number of pop in pop machine
ZERO    equ     0                       ; Initial number of coins inserted
ON      equ     1                       ; System Status Indicator ON
OFF     equ     0                       ; System Status Indicator OFF

        org     $1000
PopLeft ds      1                       ; Number of units of pop left in machine
CoinsIn ds      1                       ; Number of coins inserted so far
OK      ds      1                       ; System Status Indicator: OK
OffLine ds      1                       ; System Status Indicator: off line

        org     $2000

; *********************************************
; Initialize the System for Correct Operation *
; *********************************************

; Fill Pop Machine

        ldaa    #NUMPOP                 ; Acc A is the Number of Pop remaining
        adda    #6                      ; Show correct BCD value
        staa    PopLeft                 ; Running total for pop left

; Set Coins Inserted = 0

        ldab    #ZERO                   ; Acc B is the Number of Coins display
        stab    CoinsIn                 ; Running total for #coins inserted

; Turn on OK

        ldaa    #ON
        staa    OK                      ;Okay light is now on
        bra     Next

; Turn off OffLIne

offl    ldaa    #ON
        staa    OffLine                 ; Offline light is now on
        ldaa    #OFF
        staa    OK                      ; OK light is now off
        bra     Empty                   ; Pop machine is now empty
; ***************************
; Is the pop machine empty? *
; ***************************

Next    ldaa    PopLeft                 ;Load Pop remaining into accumulator a
        cmpa    #$0                     ;Check to see if any pop is remaining
        beq     Offl                    ;If no pop left, Turn machine off



; ***************
; Get the coins *
; ***************
InsCoin incb                           	;insert coin
        stab 	CoinsIn                 ;Store inserted coins into CoinsIn
        cmpb	#COST                   ;Check to see if right amount of coins
        beq  	Dispnse                 ;Dispense pop and reset coins
        bra 	InsCoin


; *******************************************
; Dispense the pop and reset coins inserted *
; *******************************************

Dispnse cmpa 	#$10			;Check for invalid BCD digit
	beq     AdjustA                 ;Adjust the display to reflect BCD
	deca                            ;Dispense one pop
Cont	staa 	PopLeft                 ;Store remaining pop into PopLeft
        ldab 	#ZERO                   ;Reset coins to 0
        stab 	CoinsIn                 ;Store amount of coins into CoinsIn
        bra  	Next                    ;Continue

AdjustA suba 	#7                      ;Subtract 6 for BCD, and 1 for pop dispensed
        bra     Cont

; **********************
; Pop Machine is empty *
; **********************
Empty   rti


        end