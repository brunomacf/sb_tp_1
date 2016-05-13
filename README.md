# Read Me

Para compilar é só rodar `make` e isso gera o executável `tp1` na raiz do projeto.

A execução começa no `src/main.cpp` onde simplesmente instanciamos uma máquina virtual (VM) de nome `vm` e chamamos o método `run` dessa máquina virual passando o arquivo executável da máquina.
A primeira coisa que esse método `run` faz é resetar todos os registradores/memória da máquina e em seguida carrega o arquivo binário para a memória chamando a função privada `load` da máquina virtual. 
Em seguida a máquina começa a sua operação: entra num loop infinito de execução das instruções e todo programa deve chamar a instrução hlt uma hora outra pra encerrar o programa; caso contrário o loop não termina.
Para a instrução corrente (IP) a máquina primeiro decodifica a instrução, obtendo o tipo da operação (opId), o tipo dos operandos (opsType) e os operandos propriamente ditos (op1, op2).
Além disso, o método decode retorna o número de operandos utilizados pela instrução decodificada que é utilizado para atualizar o valor de IP (determina o início da próxima instrução).
Em seguida, chamamos a função execute com os parâmetros decodificados da instrução que vai chamar a função apropriada que executa a instrução.
