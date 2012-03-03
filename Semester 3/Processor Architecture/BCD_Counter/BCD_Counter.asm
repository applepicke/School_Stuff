; BCD_Counter.asm
;
; Author: William Collins
; Student Number: 040652633
;
; Purpose: This program will count from 0 to 99 in BCD values, resetting
;          when it reaches 99. It will use Accumulator B as a display
;
        org     $1000   	;area to start storing data
TEMP:   ds      1       	;area to store temporary results

        org     $2000   	;start code here
START:  ldaa    #$0     	;load A with starting value
        ldab    #$0     	;load B with starting value
        
TEST1:  inca            	;A is incremented
        staa    TEMP:   	;store incremented value in memory
        anda    #%00001111      ;mask out lower nibble
        cmpa    #%00001010      ;test if value is too high
        bhs     TEST2:          ;if too high, go to second test
        ldab    TEMP:           ;store incremented value in B
        ldaa    TEMP:           ;return the original value of A
        bra     TEST1:          ;increment and test again
        
TEST2:  ldaa    TEMP:           ;load incremented value
        adda    #%00000110      ;skip invalid BCD digits
        staa    TEMP:
        anda    #%11110000      ;mask out upper nibble
        cmpa    #%10100000      ;test if upper nibble is too high
        bhs     START:          ;return to start if value too high
        ldab    TEMP:           ;store new proper result into B
        bra     TEST1:          ;increment and test again
        