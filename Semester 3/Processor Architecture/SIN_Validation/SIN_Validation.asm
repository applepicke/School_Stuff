; SIN_Validation.asm
; Authors:      William Collins & Nicolas Castilloux
; Purpose:      Social Insurance Number Validation


; EQUATE statements: constants to be used throughout the program
;*****************************************************************************
FINALRESULTS    equ     $1030                   ; Final numbers of valid and invalid SINs
SUMS            equ        $1050            ; Area to store the sums
NUMBEROFSINS    equ     6                       ; Six SINs to process
PROGRAMSTART    equ     $2000                   ; Executable code starts here
STORAGE1        equ     $1000                   ; Storage starts here for original SINs
THIRTY          equ     $30                     ; Value to be subtracted to convert to integer
ZERO            equ     0                       ; the end of SIN
LENOFSIN        equ     7                       ; Length of the SINs
;******************************************************************************
SINs            org     STORAGE1
#include MONDAY_LAB_GROUP.txt                   ; Text file with social insurance numbers

; STORAGE AREAS
;******************************************************************************
                org     SUMS
ODDSUM          ds      1                       ; Storage for the sum of odd numbers
EVENSUM         ds      1                       ; Storage for the sum of even numbers
SINCOUNT        ds      1                       ; Storage for loop control

                org     FINALRESULTS
InvalidResult   ds      1                       ; Count of Invalid SINs processed
ValidResult     ds      1                       ; Count of Valid SINs processed
;******************************************************************************


; The main program
;**********************************************************************
                org     ProgramStart
                lds     #ProgramStart
                clra
                staa    InvalidResult           ; Initialize invalid result memory
                staa    ValidResult             ; Initialize valid result memory
                ldx     #STORAGE1               ; Loop will count form this starting point
                staa    SINCOUNT                ; Initialize the count of SINS to zero
GetNext         tfr     x, y                    ; Backup copy of index
                bsr     ToDigit                 ; Convert char to a digit
                tfr     y, x                    ; Restore the copy of index to beginning of current SIN
                bsr     ConvertOdd              ; Adjust and convert the odd numbers in the SIN
                tfr     y, x                    ; Restore copy of index
                bsr     AddOdd                  ; Add the odd numbers in the SIN
                staa    ODDSUM                  ; store the sum of the odd values
                tfr     y, x                    ; Restore copy of index
                bsr     AddEven                 ; Add the even numbers in the SIN
                staa    EVENSUM                 ; store the sum of the even values
                bsr     Validate                ; Add and divide to find out whether it is valid
ContinueGet     ldab    #LENOFSIN               ; Prepare to center index on next SIN
                tfr     y, x                    ; Restore copy of index
                abx                             ; Center index on next SIN
                ldaa    SINCOUNT                ; Retrieve number of SINs validated
                inca                            ; Add another SIN to the list of validated
                staa    SINCOUNT                ; Save the value for the beginning of the loop
                cmpa    #NUMBEROFSINS           ; Are we done?
                blo     GetNext                 ; No, loop again
                bra     Done                    ; Yes, finish program
;******************************************************************************


; Simple Functions That add or subtract to values in memory
;******************************************************************************
AddValidResult  ldaa    ValidResult             ; How many sins are already valid?
                inca                            ; Add another one to the list
                staa    ValidResult             ; Store the list
                bra     ContinueGet             ; Go back
                
AddInvalid      ldaa    InvalidResult           ; How many sins are already invalid?
                inca                            ; Add another one to the list
                staa    InvalidResult           ; Store the list
                bra     ContinueGet             ; Go Back
                
Add6            adda    #$6                     ; BCD adjusting
                bra     AfterAdd6               ; Go back
;******************************************************************************


; ToDigit: converts the char values into numbers
;******************************************************************************
ToDigit         ldab    #LENOFSIN               ; Sets the loop counter
Convert         ldaa    0,x                     ; Loads next number to convert
                suba    #THIRTY                 ; Converts number
                staa    0,x                     ; Stores the converted value
                inx                             ; Next value
                decb                            ; Loop is decremented
                cmpb    #ZERO                   ; Is it time to leave?
                bne     Convert                 ; No, do it all again
                rts                             ; Yes, get out of here
;******************************************************************************

; AddEven: Adds the even numbers in a single SIN
;******************************************************************************
AddEven         ldab    #2
                clra
ContAddEven     inx                             ;Move to the next digit of the SIN
                adda    0,x                     ;Add the curent SIN digit
                inx                             ;Move to the next digit of the SIN
                incb                                        
                incb        
                cmpb    #LENOFSIN               ;Compare the length Of a SIN number
                                                ;with Current Position
                bls     ContAddEven             ;Continue going through the SIN Number
                rts        
;******************************************************************************

;Adjust: takes the upper nibble of a value and adds it to the lower nibble
;******************************************************************************
Adjust          tab                             ;Make a copy of A
                anda    #%00001111              ;keep lower nibble
                andb    #%11110000              ;keep upper nibble
                lsrb                            ;Shift the high nibble of B to match A
                lsrb
                lsrb
                lsrb
                aba                             ;Add the first nibble to second nibble
                rts
;******************************************************************************

; ConvertOdd: Gets the odd numbers ready to be added together
;******************************************************************************
ConvertOdd      ldab    #LENOFSIN                ;Load the Length of the SIN number into b
ContConvertOdd  ldaa    0,x                      ;Load the current SIN digit into a
                adda    0,x                      ;Add the current SIN digit to itself
                cmpa    #10                      ;Check if number is BCD
                bhs     Add6                     ;If number is not BCD add 6
AfterAdd6       pshb                                
                bsr     Adjust                   ;add upper nibble with lower nibble
                pulb
                staa    0,x                      ;Store current SIN number
                inx                              ;Move to the next digit of the SIN
                inx                              ;Move to the next digit of the SIN
                decb
                decb
                cmpb    #LENOFSIN                ;Compare the length with Current Position
                bls     ContConvertOdd           ;Continue going through the SIN Number
                rts
;******************************************************************************

; AddOdd: adds the odd values together
;******************************************************************************
AddOdd          ldab    #LENOFSIN                ;Load the Length of the SIN number into b
                    clra
ContAddOdd      adda    0,x                      ;Add the Current SIN digit
                inx                              ;Move to the next digit of the SIN
                inx                              ;Move to the next digit of the SIN
                decb                
                decb
                cmpb    #LENOFSIN                ;Compare the length with Current Position
                bls     ContAddOdd               ;Continue going through the SIN Number
                rts

;******************************************************************************

; Validate: Do the finishing touches on the validation algorithm
;******************************************************************************
Validate        clra
                clrb
                ldab    ODDSUM                    ;Load the odd sum into b
                addb    EVENSUM                   ;Add the Even sum to the odd sum
                ldx     #10                       ;Divide by 10
                idiv                              ;Divide
                tfr     d,a                       ;Store result
                cmpa    #0                        ;If result is 0, SIN IS VALID
                beq     AddValidResult            ;Add 1 to Valid SINs
                bra     AddInvalid                ;Add 1 to invalid SINs
;******************************************************************************

; All Finished!

DONE            swi
                end