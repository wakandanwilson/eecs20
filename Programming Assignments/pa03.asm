.ORIG   x3000

; store user and password database
DATABASE    .STRINGZ    "panteater"
            .STRINGZ    "qfufs"         ; Encrypted "peter" (char +1)
            .STRINGZ    "qv"    
            .STRINGZ    "ifmmpuifsf"    ; Encrypter "hellothere"
            .STRINGZ    "wilson"        ; User 1
            .STRINGZ    "qbtt234"       ; "pass123" encrypted
            .FILL       x0000           ; end of database

; constants
TEMP_BUFFER    .BLKW   #20              ; set aside 20 characters/memory space for usernames and passwords
MAX_ATTEMPTS    .FILL   #3              ; maxi login attempts

; main
START       AND     R6, R6, #0          ; track login attempts

; prompt for username
USER_LOOP   LEA     R0, USER_PROMPT
            TRAP    x22

; get username input
            LEA     R1, TEMP_BUFFER     ; R1 points to input buffer
INPUT_LOOP  TRAP    x20                 ; get character
            TRAP    x21                 ; echo 
            ADD     R2, R0, #-10        ; check for "enter"
            BRz     END_INPUT           ; If enter, end input
            STR     R0, R1, #0          ; store char
            ADD     R1, R1, #1          ; move to next pos
            BR      INPUT_LOOP          ; loop back

; end of input
END_INPUT   AND     R0, R0, #0          ; clear R0
            STR     R0, R1, #0          ; stores 0 in R1 for null termination
            LEA     R1, DATABASE        ; R1 points to database
            LEA     R2, TEMP_BUFFER     ; R2 points to input

; check if inputted username is in database
CHECK_USER  LDR     R3, R1, #0          ; load first char of database user
            BRz     NOT_FOUND           ; branch if user not found (end of database)

COMPARE     LDR     R3, R1, #0          ; load database char
            BRz     CHECK_END           ; if end of string (null), check if input also ended
            LDR     R4, R2, #0          ; load input char
            BRz     NEXT_USER           ; if input ended early, try next user
            NOT     R5, R3              ; compare characters using 2's comp
            ADD     R5, R5, #1
            ADD     R5, R5, R4
            BRnp    NEXT_USER           ; if result is not 0, try next user
            ADD     R1, R1, #1          ; move to next database char
            ADD     R2, R2, #1          ; move to next input char
            BR      COMPARE             ; loop back

; check if end of input is reached
CHECK_END   LDR     R4, R2, #0          ; load input char
            BRz     GET_PASS            ; if end of input, get password
            BR      NEXT_USER           ; if input longer, go to next user

; check next user in database
NEXT_USER   LEA     R2, TEMP_BUFFER     ; reset input pointer
            AND     R6, R6, #0  
SKIP_ENTRY  ADD     R1, R1, #1          ; increment through current entry
            LDR     R3, R1, #0
            BRnp    SKIP_ENTRY          ; go until null
            ADD     R1, R1, #1          ; skip null
            ADD     R1, R1, #1          ; skip to next username
            BR      CHECK_USER

; username not found
NOT_FOUND   ADD     R6, R6, #1          ; increment attempt counter
            LD      R5, MAX_ATTEMPTS
            NOT     R5, R5              ; 2's comp to check if max attempts reached
            ADD     R5, R5, #1
            ADD     R5, R6, R5          
            BRzp    MAX_REACHED         ; if 3 attempts, exit
            LEA     R0, NOT_FOUND_MSG   ; user not found
            TRAP    x22
            BR      USER_LOOP           ; loop back to beginning

; get password
GET_PASS    ADD     R5, R1, #1          ; save position after username
            LEA     R0, PASS_PROMPT     ; display "Enter password:"
            TRAP    x22                 ; take in input
            LEA     R2, TEMP_BUFFER     ; R2 -> temp storage for inputted password

; get password input
PASS_INPUT  TRAP    x20                 ; get inputted char
            TRAP    x21                 ; echo onto screen
            ADD     R3, R0, #-10        ; check for enter key
            BRz     END_PASS            ; if enter, branch to end pass input
            STR     R0, R2, #0          ; stores each char into memory in R2
            ADD     R2, R2, #1          ; increments to next memory address
            BR      PASS_INPUT

; end password input
END_PASS    AND     R0, R0, #0          ; clear R0
            STR     R0, R2, #0          ; Null terminate password

; encrypt input password
            LEA     R2, TEMP_BUFFER     ; reset to start of password (R2)
ENCRYPT     LDR     R3, R2, #0          ; load input char
            BRz     CHECK_PASS          ; if null term, check password
            ADD     R3, R3, #1          ; encrypt by adding #1
            STR     R3, R2, #0          ; store encrypted char in R2
            ADD     R2, R2, #1          ; increment to next mem address
            BR      ENCRYPT

; check password
CHECK_PASS  LEA     R2, TEMP_BUFFER     ; reset to start of password
            ADD     R1, R5, #0          ; point to stored password
PASS_CMP    LDR     R3, R1, #0          ; load stored password char
            LDR     R4, R2, #0          ; load input password char
            BRz     CHECK_PASS_END      ; if end of string, check if both null terms are hit
            NOT     R3, R3
            ADD     R3, R3, #1
            ADD     R3, R3, R4
            BRnp    WRONG_PASS          ; if not equal, wrong password
            ADD     R1, R1, #1          ; go next stored char
            ADD     R2, R2, #1          ; go next input char
            BR      PASS_CMP

; check if input and database PW ended
CHECK_PASS_END
            LDR     R4, R2, #0          ; check if input also ended
            BRz     SUCCESS             ; if both ended, successful login
            BR      WRONG_PASS          ; if not, wrong password

; wrong password
WRONG_PASS  ADD     R6, R6, #1          ; increment attempt counter
            LD      R5, MAX_ATTEMPTS
            NOT     R5, R5
            ADD     R5, R5, #1
            ADD     R5, R6, R5          ; check if max attempt is hit (2's comp)
            BRzp    MAX_REACHED         ; if max attempts, exit
            LEA     R0, WRONG_PASS_MSG  ; print wrong password
            TRAP    x22
            BR      GET_PASS            ; retry

; max attempts hit
MAX_REACHED LEA     R0, MAX_ATTEMPTS_MSG
            TRAP    x22
            BR      DONE

; successful login
SUCCESS     LEA     R0, SUCCESS_MSG
            TRAP    x22

; end
DONE        TRAP    x25

; messages
USER_PROMPT     .STRINGZ    "Enter username: "
PASS_PROMPT     .STRINGZ    "\nEnter password: "
NOT_FOUND_MSG   .STRINGZ    "\nUsername not found. Please try again.\n"
WRONG_PASS_MSG  .STRINGZ    "\nIncorrect password. Please try again.\n"
MAX_ATTEMPTS_MSG .STRINGZ   "\nMaximum attempts reached. Program terminating.\n"
SUCCESS_MSG     .STRINGZ    "\nLogin successful!\n"

            .END