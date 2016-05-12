READ BX				;Número que será fatorado
JZ zero				;Caso o valor entrado seja igual a zero
MOV AX, BX			;AX receberá o resultado.
loop: SUB BX, 0x1	;Decrementa o valor de BX
JZ exit				;Quando BX chegar a zero, desvia para o final
MUL BX        		;AX receberá o resultado da multiplicação AX x BX
JMP loop
zero: MOV AX, 0x1	;Fatorial de zero é um
exit: WRITE AX		;Escreve o resultado na tela
DUMP				;Imprime o valor dos registradores
HLT					;Finaliza a execução