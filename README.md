# threads
Pi calculation using threads

For compiling, use this parameters (-lm if ld return error for pow)

# goal (PT_br)
Escolha duas séries quaisquer para aproximar o número pi do site Pi series 1 ou Pi series 2 ou outro
site qualquer. Veja exemplos sequenciais em Pi sequencial. Implemente a versão paralela dessas
séries, u

lizando pthreads, sequindo os seguintes requisitos:
Devem ser calculados pelo menos 1 bilhão (10^9) de termos de cada série.
Use variáveis reais de dupla precisão (double) nos cálculos;
O programa deve dividir o espaço de cálculo uniformemente entre as N threads
e.x. 1bilhão de termos com 2 threads = 500milhões de termos em cada thread;
cada thread efetua uma soma parcial de forma autônoma;
Para evitar o uso de mecanismos de sincronização, cada thread T[i] deve depositar seu
resultado parcial na posição result[i] de um vetor de resultados parciais.
Após o término das threads de cálculo, o programa principal soma os resultados parciais
ob
dos por elas e apresenta o resultado final na tela;
Execute as threads no seu computador pessoal e no servidor Orion
Acesso: faça login no linux de rede
Use ssh: ssh user@orion
user e pass são os mesmos do linux de rede
Em ambas as máquinas execute as soluções com N = {1, 2, 4, 8 e 16} threads
Marque o tempo necessário para calcular Pi para cada N em cada máquina e faça um gráfico
de linhas (NxTempo) apresentado os resultados ob

dos em ambas as máquinas
Compare o resultado das duas soluções (series) escolhidas, indicando qual série é mais
eficiente em termos de tempo e qualidade da solução (i.e. valor mais exato de pi)

# Future improvements:
Including graphs of CPU utilization:
https://github.com/rigel314/ttysys
