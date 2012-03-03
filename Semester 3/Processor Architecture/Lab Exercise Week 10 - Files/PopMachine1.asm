; PopMachine1.asm

; Program equates (equ), which are equal to #define in C
; These act as CONSTANTs in ASM

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
        staa    PopLeft                 ; Running total for pop left

; Set Coins Inserted = 0

        ldab    #ZERO                   ; Acc B is the Number of Coins display
        stab    CoinsIn                 ; Running total for #coins inserted

; Turn on OK

        ldaa    #ON                     ; OK is on once the pop machine is filled
        staa    OK

; Turn off OffLIne

        ldaa    #OFF                    ; OffLine is only on when pop machine empty
        staa    OffLine

; ***************************
; Is the pop machine empty? *
; ***************************


; ***************
; Get the coins *
; ***************


; *******************************************
; Dispense the pop and reset coins inserted *
; *******************************************


Empty   rti
        end