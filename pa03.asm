    .ORIG   x3000
        
; Store user database
DATABASE    .STRINGZ    "panteater"
            .STRINGZ    "qfufs" ; Encrypted "peter" (char +1)
            .STRINGZ    "qv"    
            .STRINGZ    "ifmmpuifsf" ; Encrypter "hellothere"
            .STRINGZ    "wilson"
            .STRINGZ    "qbttxpse" ; "password"
            .FILL       x0000   ; End of database
            
; Constants
MAX_ATTEMPTS    .FILL   #3 ; max login attempts
TEMP_BUFFER     .BLKW   #25 ; set aside 25 characters/memory space for user input

; Main
START       AND     R6, R6, #0      ; track login attempts

; prompt for username
USERLOOP    LEA     R0, USER_PROMPT
            TRAP    x22

; Get username input
            LEA     R1, TEMP_BUFFER ; R1 points to input buffer
USERINPUT   TRAP    x20         ; get character
            TRAP    x21         ; echo  
            ADD     R2, R0, #-10; check for "enter"
            BRz     FINDUSER    ; if "enter" key is pressed, check username database
            STR     R0, R1, #0  ; store char
            ADD     R1, R1, #1  ; move to next pos
            BR      USERINPUT   ; loop back
            
; Find username in database
FINDUSER    AND     R0, R0, #0      ; clear R0  
            STR     R0, R1, #0      ; stores 0 in R1 for null termination
            LEA     R1, DATABASE    ; R1 points to database
            LEA     R2, TEMP_BUFFER ; R2 points to input
            
; Check if inputted username is in database
CHECKUSER   LDR     R3, R1, #0      ; load database char
            BRz     USERNOTFOUND    ; branch if user not found (end of database)
            ADD     R4, R2, #0      ; reset input pointer
            ADD     R5, R1, #0      ; save database position
            
; Compare input username with stored username
COMPARE     LDR     R3, R5, #0      ; load database character
            LDR     R4, R4, #0      ; load input character
            BRz     USERMATCH       ; if both null, username matches
            NOT     R3, R3          ; flip bits for 2's comp
            ADD     R3, R3, #1      ; add 1 for 2's comp
            ADD     R3, R3, R4      ; add 2's complemented (R3) to R4
            BRnp    NEXTUSER        ; if not equal, try next user (if 0, chars match)
            ADD     R5, R5, #1      ; move to next character
            ADD     R4, R4, #1      ; move to next
            BR      COMPARE         ; loop back
            
; move to next stored user
NEXTUSER    ADD     R1, R1, #1      ; move to next char
            LDR     R3, R1, #0      ; load char into R3
            BRnp    NEXTUSER        ; load all characters until null
            ADD     R1, R1, #1      ; skip null
            BR      CHECKUSER
            
; username not found
USERNOTFOUND    ADD R6, R6, #1      ; increment attempt counter
                LD  R3, MAX_ATTEMPTS
                NOT R3, R3          ; 2's complement
                ADD R3, R3, #1
                ADD R3, R6, R3      ; check if max attempts reached
                BRzp    MAXATTEMPTS ; if max attempts, exit
                LEA R0, INVALID_USER
                TRAP    x22         ; outputs invalid user
                BR  USERLOOP        ; try again
                
; prompt password if user matched
USERMATCH   ADD     R5, R1, #0      ; save username position
            ADD     R1, R1, #1      ; moving to next character in username
            LDR     R3, R1, #0      ; load each character into R3
            BRnp    USERMATCH       ; if character isn't 0 (null terminator), keep going
            ADD     R1, R1, #1      ; R1 now points to start of stored password
            
; get password from database
PASSLOOP    LEA     R0, PASS_PROMPT ; display "Enter password:"
            TRAP    x22             ; take in input
            LEA     R2, TEMP_BUFFER ; R2 -> temp storage for inputted password
            AND     R6, R6, #0      ; reset attempt counter (R6 = 0)
            
; get password input
PASSINPUT   TRAP    x20             ; get inputted char
            TRAP    x21             ; echo character onto screen
            ADD     R3, R0, #-10    ; check for enter key
            BRz     CHECKPASS       ; if enter, check inputted password
            STR     R0, R2, #0      ; stores each character in R2
            ADD     R2, R2, #1      ; increments to next memory address
            BR      PASSINPUT       ; loop back
            
; check encrypted password
CHECKPASS   AND     R0, R0, #0
            STR     R0, R2, #0
            LEA     R2, TEMP_BUFFER ; reset to start of input
            ADD     R3, R1, #0      ; R3 points to stored password
            
; encrypt inputted password for checking
ENCRYPT     LDR     R4, R2, #0      ; load input char
            BRz     COMPAREPASS    ; if end of input (null term), compare passwords
            ADD     R4, R4, #1      ; add #1 to value
            STR     R4, R2, #0      ; store encrypter char in R2
            ADD     R2, R2, #1      ; increment to next memory address
            BR      ENCRYPT         ; loop back
            
COMPAREPASS LEA     R2, TEMP_BUFFER
PASSCHECK   LDR     R4, R2, #0      ; load input char
            LDR     R5, R3, #0      ; load stored char
            BRz     SUCCESS         ; if both null (reached end of password), success
            NOT     R5, R5          ; 2's complement to check
            ADD     R5, R5, #1
            ADD     R5, R5, R4
            BRnp    WRONG_PASS      ; if result is not 0, wrong password
            ADD     R2, R2, #1      ; continue to next char
            ADD     R3, R3, #1
            BR      PASSCHECK
            
; wrong password
WRONG_PASS  ADD     R6, R6, #1      ; increment attempt counter
            LD      R3, MAX_ATTEMPTS
            NOT     R3, R3
            ADD     R3, R3, #1
            ADD     R3, R6, R3      ; check if max attempts reached using 2's comp
            BRzp    MAXATTEMPTS     ; if max attempts, exit
            LEA     R0, INVALID_PASS
            TRAP    x22
            BR      PASSLOOP        ; try again
            
; max attempts reached
MAXATTEMPTS    LEA     R0, MAX_MSG     ; print "max attempts reached"
                TRAP    x22
                TRAP    x25             ; halt
            
; successful login
SUCCESS     LEA     R0, LOGIN_SUCCESS   ; print "login successful"
            TRAP    x22
            LEA     R0, HELLO           ; hello "user"
            TRAP    x22
            TRAP    x25                 ; halt program

; messages
USER_PROMPT     .STRINGZ    "Enter username: "
PASS_PROMPT     .STRINGZ    "\nEnter password: "
INVALID_USER    .STRINGZ    "\nInvalid username. Please try again.\n"
INVALID_PASS    .STRINGZ    "\nIncorrect password. Please try again.\n"
LOGIN_SUCCESS   .STRINGZ    "\nLogin successful!\n"
MAX_MSG         .STRINGZ   "\nMaximum attempts reached.\n"
HELLO           .STRINGZ    "Hello, "

.END