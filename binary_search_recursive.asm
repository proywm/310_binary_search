; addtwo.asm
; MASM 32-bit, Visual Studio 2022

.386
.model flat, stdcall
.stack 4096

ExitProcess PROTO, dwExitCode:DWORD

.data
    arr DWORD 5, 12, 18, 25, 33, 41, 56, 72, 89, 100
    target DWORD 89
    low_var DWORD 0
    high_var DWORD ?
    mid DWORD ?
    result DWORD -1
    ;iter DWORD 0
.code
binary_search PROC

    ; creating binary_search scope
    push ebp
    mov ebp, esp

    ; create local variable int mid
    mov eax, 0DEADh
    push eax

    mov ecx, [ebp - 4] ; reading mid 
    mov edx, [ebp + 8] ; reading parameter
    mov ebx, [ebp + 12] ; reading returned value


    ; Step 1: Initialize the search range.
    mov eax, LENGTHOF arr
    sub eax, 1
    mov high_var, eax

    ; Step 2: This label marks the TOP of our search loop.
    
search_loop_start:
    ;CHECK THE LOOP CONDITION: is low <= high?
    ;if (low > high)
    ;    goto search_done;

    mov eax, low_var
    cmp eax, high_var
    JG search_done

    ; Step 3: Calculate the middle index.
    ; mid = (low + high) / 2;
    add eax , high_var
    shr eax, 1
    mov [ebp - 4], eax

    ;  Step 4: Compare arr[mid] with target.
    ; if (arr[mid] == target)
    ;    goto found_it;

    mov esi , eax
    shl esi, 2
    mov ebx, [arr + esi]
    cmp ebx, [ebp + 8]
    JE found_it

    ; if (target < arr[mid])
    ;    goto search_left;
    cmp [ebp + 8], ebx
    JL search_left


    ; goto search_right;
    JMP search_right




found_it:
     ; get the index in the result
     ; result = mid;
     ; goto search_done;

     mov eax, [ebp - 4]
     mov [ebp + 12], eax
     JMP search_done


search_left:
    ;high = mid - 1;
    ;goto search_loop_start;   /* Jump back to loop top */
    mov eax, [ebp - 4]
    mov high_var, eax
    sub high_var, 1
    JMP search_loop_start

search_right:
    ;low = mid + 1;
    ;goto search_loop_start;   /* Jump back to loop top */
    mov eax, [ebp - 4]
    mov low_var, eax
    add low_var, 1
    JMP search_loop_start


search_done:

    ; terminating the binary_search scope
    mov esp, ebp
    pop ebp

    ret
binary_search ENDP



binary_search_recursive PROC

    ; creating binary_search scope
    push ebp
    mov ebp, esp

    ; create local variable int mid
    ; mov eax, 0DEADh
    ; push eax

    ;mov ecx, [ebp - 4] ; reading mid 
    ;mov edx, [ebp + 8] ; reading parameter target
    ;mov ebx, [ebp + 12] ; reading returned value; result


    ; Step 1: Initialize the search range.
    mov eax, LENGTHOF arr
    sub eax, 1
    mov high_var, eax

    ; Step 2: This label marks the TOP of our search loop.
    
search_loop_start:
    ;CHECK THE LOOP CONDITION: is low <= high?
    ;if (low > high)
    ;    goto search_done;

    mov eax, low_var
    cmp eax, high_var
    JG search_done

    ; Step 3: Calculate the middle index.
    ; mid = (low + high) / 2;
    add eax , high_var
    shr eax, 1
    mov mid, eax

    ;  Step 4: Compare arr[mid] with target.
    ; if (arr[mid] == target)
    ;    goto found_it;

    mov esi , eax
    shl esi, 2
    mov ebx, [arr + esi]
    cmp ebx, target
    JE found_it

    ; if (target < arr[mid])
    ;    goto search_left;
    cmp target, ebx
    JL search_left


    ; goto search_right;
    JMP search_right




found_it:
     ; get the index in the result
     ; result = mid;
     ; goto search_done;

     mov eax, mid
     mov result, eax
     JMP search_done


search_left:
    ;high = mid - 1;
    ;goto search_loop_start;   /* Jump back to loop top */
    mov eax, mid
    mov high_var, eax
    sub high_var, 1
    ;JMP search_loop_start
    call binary_search_recursive

search_right:
    ;low = mid + 1;
    ;goto search_loop_start;   /* Jump back to loop top */
    mov eax, mid
    mov low_var, eax
    add low_var, 1
    ;JMP search_loop_start
    call binary_search_recursive


search_done:

    ; terminating the binary_search scope
    mov esp, ebp
    pop ebp

    ret
binary_search_recursive ENDP


binary_search_recursive_local PROC

    ; creating binary_search scope
    push ebp
    mov ebp, esp

    ; create local variable int mid
    mov eax, 0DEADh
    push eax

    ;mov ecx, [ebp - 4] ; reading mid 
    ;mov edx, [ebp + 8] ; reading parameter target
    ;mov ebx, [ebp + 12] ; reading returned value; result


    ; Step 1: Initialize the search range.
    mov eax, LENGTHOF arr
    sub eax, 1
    mov high_var, eax

    ; Step 2: This label marks the TOP of our search loop.
    
search_loop_start:
    ;CHECK THE LOOP CONDITION: is low <= high?
    ;if (low > high)
    ;    goto search_done;

    mov eax, low_var
    cmp eax, high_var
    JG search_done

    ; Step 3: Calculate the middle index.
    ; mid = (low + high) / 2;
    add eax , high_var
    shr eax, 1
    mov [ebp - 4], eax

    ;  Step 4: Compare arr[mid] with target.
    ; if (arr[mid] == target)
    ;    goto found_it;

    mov esi , eax
    shl esi, 2
    mov ebx, [arr + esi]
    cmp ebx, [ebp + 8]
    JE found_it

    ; if (target < arr[mid])
    ;    goto search_left;
    cmp [ebp + 8], ebx
    JL search_left


    ; goto search_right;
    JMP search_right




found_it:
     ; get the index in the result
     ; result = mid;
     ; goto search_done;

     mov eax, [ebp - 4]
     mov [ebp + 12], eax
     JMP search_done


search_left:
    ;high = mid - 1;
    ;goto search_loop_start;   /* Jump back to loop top */
    mov eax, mid
    mov high_var, eax
    sub high_var, 1
    ;JMP search_loop_start

    ;create a space to hold return value
     mov eax, -1
     push eax

    ; parameter target 101
    mov eax, 89
    push eax

    call binary_search_recursive_local

    pop eax
    pop eax
    mov [ebp + 12], eax
    jmp search_done

search_right:
    ;low = mid + 1;
    ;goto search_loop_start;   /* Jump back to loop top */
    mov eax, [ebp - 4]
    mov low_var, eax
    add low_var, 1
    ;JMP search_loop_start

    ;create a space to hold return value
     mov eax, -1
     push eax

    ; parameter target 101
    mov eax, 89
    push eax

    call binary_search_recursive_local

    pop eax
    pop eax
    mov [ebp + 12], eax


search_done:

    ; terminating the binary_search scope
    mov esp, ebp
    pop ebp

    ret
binary_search_recursive_local ENDP


main PROC

     ;create a space to hold return value
     mov eax, -1
     push eax

    ; parameter target 101
    mov eax, 89
    push eax

    ;call binary_search 
    call binary_search_recursive_local


    pop eax
    pop eax

    INVOKE ExitProcess, eax
main ENDP

END main
