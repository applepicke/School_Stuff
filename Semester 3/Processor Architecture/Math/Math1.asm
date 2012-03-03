; Math1.asm
;
; Author:         Willy Collins
; Student No:   040652633
;
; Purpose:      Add three values from even numbered memory, and subtract two
;               values from odd numbered memory, storing the result in memory.
;
        org     $1000           ; Set starting area to store memory
        db      $F2,$15,$37     ; An array of numbers to be added or subtracted
        fill    $22,$2          ; Numbers that will be added or subtracted
        org     $1020           ; Area where the result will be stored
        ds      1               ; Low order byte of result
        ds      1               ; High order byte of result
        org     $2000           ; Program to be stored in this area
        ldaa    $1000           ; First number loaded into A
        adca    $1002           ; Add first value to A
        ldab    #$0             ; Load B so that it is ready to store overflow
        adcb    #$0             ; Add the carry from the first addition
        stab    $1020           ; Store high order byte of result
        adda    $1004           ; Add next value to A
        suba    $1001           ; Subtract next value from A
        suba    $1003           ; Subtract next value from A
        staa    $1021           ; Store low order byte of result
        end                     ; END