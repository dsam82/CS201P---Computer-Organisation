;
;       Objective: calculate maximum marks obtained in each subject
;       Input: Request N students and M subject and their marks in each subject.
;       Output: Display the roll no of student who got max marks in each subject.
%include "io.mac"

.DATA
MAX_SIZE      EQU   800
prompt_msg1   db    "Please input the no. of students : ",0
prompt_msg2   db    "Please input the no. of subjects : ",0
prompt_msg3   db    "Enter roll no. of student : ",0
prompt_msg4   db    "Enter marks of student in subjects : ",0
out_msg       db    "Students with Max. marks",0
out_msg1      db    "Subject ",0
str1          db    " : ",0

.UDATA
n             resw  1               ; Variable to initialise no. of students
m             resw  1               ; Variable to initialise no. of subjects
tempRno       resb  7               ; Variable to take temp roll no
tempMarks     resw  1               ; Variable to take temp Marks
array         resb  MAX_SIZE

.CODE
      .STARTUP
      PutStr  prompt_msg1
      GetInt  [n]                   ; read input N
      PutStr  prompt_msg2
      GetInt  [m]                   ; read input M

      PutStr  prompt_msg3
      GetStr  tempRno,7             ; take input first roll no
      sub     EDX,EDX               ; initialise k to 0
      cmp     DX,[n]                ; exit the program if no students are in any sub
      je      done
      PutStr  prompt_msg4
  nwln
      sub     ESI,ESI               ; initialise i to 0
loop1:                              ; for (i=0 ; i<m ; i++)
      sub     EDI,EDI               ; initialise j to 0
  loop2:                            ; while (j=0 ; j<6 ; j++)
      mov     CX,[tempRno+EDI]      ; move value of tempRno to CX
      mov     [array+ESI*8+EDI],CX  ; copy Rno from tempRno to Array
      inc     EDI                   ; j++
      cmp     EDI,6                 ; if (j<6)
      jl      loop2                 ; move the Rno to array bytewise

      GetInt  [tempMarks]           ; take input of marks of every subject
      mov     AX,[tempMarks]
      mov     [array+ESI*8+EDI],AX
      inc     ESI                   ; i++
      cmp     SI,[m]                ; if (i<m)
      jl      loop1                 ; move marks of every subject to the array
      cmp     WORD [n],1            ; print the result if (n == 1)
      je      print_Result

      inc     EDX                   ; increment k as marks of first student is taken

loop3:
      sub     ESI,ESI               ; initialise i to 0
      PutStr  prompt_msg3
      GetStr  tempRno,7             ; take roll no of student
      PutStr  prompt_msg4
  nwln
  loop4:
      GetInt  [tempMarks]           ; take marks of student in every subject
      mov     AX,[tempMarks]        ; move marks of current student to AX
      mov     BX,[array+ESI*8+6]    ; move marks of previous student to BX
      cmp     AX,BX                 ; if (current_marks > previous_marks)
      jg      max_marks_changed     ; change the marks in the array

    loop5:
      inc     ESI                   ; i++
      cmp     SI,[m]                ; if (i<m)
      jl      loop4

      inc     EDX                   ; k++
      cmp     DX,[n]                ; if (k<n)
      jl      loop3

      jmp     print_Result          ; print max roll no and marks

max_marks_changed:
      sub     EDI,EDI               ; initialise j to 0
  loop6:
      mov     CX,[tempRno+EDI]
      mov     [array+ESI*8+EDI],CX  ; overWrite Rno from tempRno to Array
      inc     EDI                   ; j++
      cmp     EDI,6                 ; if (j<6)
      jl      loop6                 ; move the Rno to array bytewise

      mov     AX,[tempMarks]        ; overwrite previous marks in the array
      mov     [array+ESI*8+EDI],AX
      jmp     loop5

print_Result:
      PutStr  out_msg
      sub     ESI,ESI
  print:
    nwln
      sub     EDI,EDI
      PutStr  out_msg1
      PutLInt  ESI
      PutStr  str1

    printRollNo:
      PutCh   [array+ESI*8+EDI]
      inc     EDI
      cmp     EDI,6
      jl      printRollNo

      PutStr  str1
      PutInt  [array+ESI*8+6]
      inc     ESI
      cmp     SI,[m]
      jl      print

done:
      .EXIT

