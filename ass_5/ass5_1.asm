;
;       Objective: encrypt a string changing only numeric digits
;       Input: Request a string from the user.
;       Output: Display the encrypted string.
%include "io.mac"

.DATA
prompt_msg1   db    "Please input the string (< 16 characters) : ", 0
prompt_msg2   db    "Do you want to terminate program (y/Y) : ", 0
out_msg       db    "Encrypted string : ", 0

.UDATA
in_str        resb   16
in_ch         resb   1

.CODE
start:
      .STARTUP
      PutStr  prompt_msg1           ; request input string
      GetStr  in_str,16             ; read input string

      PutStr  out_msg
      mov     EBX,in_str            ; EBX = pointer to in_str

encryption:
      cmp     BYTE  [EBX],0         ; if it is the null character
      je      terminate             ; request another string from user
      cmp     BYTE  [EBX],'0'       ; if (char < '0')
      jl      not_numeric           ; not a numeric character
      cmp     BYTE  [EBX],'9'       ; if (char > '9')
      jg      not_numeric           ; not a numeric character
      cmp     BYTE  [EBX],'9'       ; if (char == '9')
      je      enc_9                 ; convert 9 to 0
      cmp     BYTE  [EBX],'3'       ; if (char >= '0' && char < '3')
      jl      enc_0to2
      cmp     BYTE  [EBX],'9'       ; if (char > 2 && char < 9)
      jl      enc_3to8
enc_9:
      sub     BYTE  [EBX],9         ; convert 9 to 0
      jmp     not_numeric
enc_0to2:
      add     BYTE  [EBX],'X'-'0'   ; convert 0 - X, 1 - Y, 2 - Z
      jmp     not_numeric
enc_3to8:
      add     BYTE  [EBX],'A'-'3'   ; convert 3 - A, ... , 8 - F
      jmp     not_numeric
not_numeric:
      inc     EBX                   ; point EBX to next char in string
      jmp     encryption            ; go back to encryption
terminate:
      PutStr  in_str                ; output the encrypted string
    nwln
      PutStr  prompt_msg2           ; request another string
      GetCh   [in_ch]               ; get input from user to terminate the program
      cmp     BYTE  [in_ch],'y'     ; if (char == 'y')
      je      done                  ; exit the program
      cmp     BYTE  [in_ch],'Y'     ; if (char == 'Y')
      je      done                  ; exit the program
      jmp     start                 ; jump to start of the program
done:
      .EXIT
