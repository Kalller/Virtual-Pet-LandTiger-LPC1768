				AREA asm_functions, CODE, READONLY				
                EXPORT  nome_funzione
nome_funzione
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				PUSH {r4-r8,r10-r11,lr}

				; restore volatile registers
				POP {r4-r8,r10-r11,pc}				
                END