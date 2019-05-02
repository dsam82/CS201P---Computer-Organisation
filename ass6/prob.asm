; Write a complete assembly language program to read two
; matrices A and B and display the result matrix C, which is the
; product of A and B. Your program should consist of a main
; procedure that calls the read_matrix procedure twice to read
; data for A and B. It should then call the matrix_add procedure,
; which receives pointers to A, B, C, and the size of the matrices.
; Note that both A and B should have the same size. The main
; procedure calls another procedure to display matrix (A B and C)

%include "io.mac"

%macro moveMatrix 1
mov BX,DX
sub BX,1
%%loopmm1:
    mov DI,CX
    sub DI,1
    %%loopmm2:
        mov AX,BX
        mul CX
        add AX,DI
        mov SI,2
        mul SI
        mov SI,AX
        pop AX
        mov [%1+ESI],AX
        sub DI,1
        cmp DI,0
        jge %%loopmm2
    sub BX,1
    cmp BX,0
    jge %%loopmm1
%endmacro

.DATA
msg_dim1     db  'Enter dimensions of matrix 1: ',0
msg_dim2     db  'Enter dimensions of matrix 2: ',0
msg_1       db  'Enter first matrix: ',0
msg_2       db  'Enter second matrix : ',0
msg_3       db  ' ',0
msg_4       db  'Resultant Matrix is:',0
incc db "Incorrect Matrix Sizes",0
matrix1     TIMES   100   dw 0
matrix2     TIMES   100   dw 0
matrix3     TIMES   100   dw 0

.UDATA
nA resw 1
mA resw 1
nB resw 1
mB resw 1
num resw 1
tempn resw 1
tempm resw 1
tempp resw 1
address resd 1
tempA resd 1
tempB resd 1
tempC resd 1
tempIndexi resw 1
tempIndexj resw 1

.CODE
    .STARTUP
    PutStr  msg_dim1
    nwln
    GetInt [mA]         ; Get row of matrix 1
    GetInt [nA]         ; Get column of matrix 1

    mov CX,[mA]
    mov DX,[nA]
    call readMatrix     ; read the matrix 1 values
    moveMatrix matrix1

    PutStr  msg_dim2
    nwln
    GetInt [mB]         ; Get row of matrix 2
    GetInt [nB]         ; Get column of matrix 2

    mov CX,[mB]
    mov DX,[nB]
    call readMatrix     ; read the matrix 2 values
    moveMatrix matrix2

    mov AX,[mB]
    cmp WORD [nA],AX    ; if (nA != mB)
    jne notequal        ; Error in multiplication

    push WORD [mA]      ; push rows of first matix in stack
    push WORD [nA]      ; push rows/column of second/first matix in stack
    push WORD [nB]      ; push column of second matix in stack
    mov EAX,matrix1     ; push address of first matrix
    push EAX
    mov EAX,matrix2
    push EAX            ; push address of second matrix
    mov EAX,matrix3
    push EAX            ; push address of result matrix
    call multiplyMatrix ; call Multiply matrix

    mov EAX,matrix3
    mov CX,[mA]
    mov DX,[nB]
    PutStr  msg_4
    nwln
    call printMatrix    ; print Matrix 3
    jmp done

    notequal:
    PutStr incc
    nwln

    done:
.EXIT

readMatrix:
pop EBX
mov [address],EBX
sub EDI,EDI
looprm1:
    sub ESI,ESI
    looprm2:
        GetInt [num]
        push WORD [num]     ; push number onto the stack
        add SI,1
        cmp SI,DX
        jl looprm2
    add DI,1
    cmp DI,CX
    jl looprm1
mov EBX,[address]
push EBX
ret

printMatrix:
pop EBX
mov [address],EBX
mov [tempm],CX
mov [tempn],DX
sub CX,CX
looppm1:
    sub DX,DX
    looppm2:
        mov WORD BX,[EAX]
        PutInt BX
        PutCh " "
        add EAX,2
        add DX,1
        cmp DX,[tempn]
        jl looppm2
    nwln
    add CX,1
    cmp CX,[tempm]
    jl looppm1
mov EBX,[address]
push EBX
ret

multiplyMatrix:
pop EBX
mov [address],EBX
pop EBX
mov [tempC],EBX
pop EBX
mov [tempB],EBX
pop EBX
mov [tempA],EBX
pop BX
mov [tempn],BX
pop BX
mov [tempp],BX
pop BX
mov [tempm],BX
sub ECX,ECX
loopmm1:
    mov [tempIndexi],CX
    sub EDX,EDX
    loopmm2:
        mov [tempIndexj],DX
        sub EDI,EDI
        sub CX,CX
        loopmm3:
            mov AX,[tempIndexi]
            mul WORD [tempp]
            add AX,DI
            mov SI,2
            mul SI
            mov SI,AX
            mov EDX,[tempA]
            mov BX,[EDX+ESI]

            mov AX,DI
            mul WORD [tempn]
            add AX,[tempIndexj]
            mov SI,2
            mul SI
            mov SI,AX
            mov EDX,[tempB]
            mov AX,[EDX+ESI]

            mul BX

            add CX,AX

            add DI,1
            cmp DI,[tempp]
            jl loopmm3
        mov AX,[tempIndexi]
        mul WORD [tempn]
        add AX,[tempIndexj]
        mov SI,2
        mul SI
        mov SI,AX
        mov EDX,[tempC]
        mov [EDX+ESI],CX

        mov DX,[tempIndexj]
        add DX,1
        cmp DX,[tempn]
        jl loopmm2
    mov CX,[tempIndexi]
    add CX,1
    cmp CX,[tempm]
    jl loopmm1
mov EBX,[address]
push EBX
ret