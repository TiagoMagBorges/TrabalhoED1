--- Alunos ---

Tiago Magela Borges
Herbert Maia Tolentino

--- Trabalho de Estrutura de Dados 1 ----

Esse trabalho tinha como objetivo implementar as estruturas de dados pilha, fila e lista, afim de exercitar nos alunos a prática de uso das mesmas, que foram amplamente discutidas dentro da sala de aula durante o semestre. Nesse sentido, buscamos usar principalmente o material disponibilizado durante o semestre para o desenvolvimento do código.

Já o exercício em si, pedia a criação de um sistema que simulasse um restaurante, onde os clientes adicionados poderiam visualizar o cardápio e escolher quantos itens quisessem. Quando fossem embora, formariam uma fila e cada cliente mostraria a comanda com a lista de itens consumidos e total gasto. Além disso, receberiam um chocolate de brinde, armazenado em um pilha de chocolates.

Primeiro, começamos estruturando o corpo inicial do código, separado em bibliotecas, structs, assinaturas das funções, função main e, por fim, o desenvolvimento das funções declaradas. Além disso, os comentários foram essenciais para manter a organização do programa, sendo usado para resumir o que cada função faz, destacar mudanças recentes e fazer anotações que, com o tempo, se tornaram novas funções e novas structs usadas para a finalização do programa.

Depois de estruturar o corpo do código, começamos a analisar e testar maneiras de resolver o exercício. Então, ficou decidido que implementariamos pilhas e listas através de listas encadeadas dinâmicamente:
        Assim, criamos uma fila (fila de clientes) que possui como nó uma struct do tipo Cliente com um vetor para o nome do cliente, um ponteiro para a pilha de id's (itens do cardápio escolhidos pelo cliente) e um ponteiro para o próximo cliente. E criamos separadamente uma pilha para armazenar os chocolates, de onde é retirado o chocolate do topo e passado como brinde para cada cliente atraves da função "imprimeF".
        
Entre outras decisões que tomamos, decidimos não utilizar arquivos para a leitura dos dados durante a execução e criar uma nova opção para o menu do programa: gerar clientes aleatórios. Pensamos nessa funcionalidade durante a criação do código para facilitar a testagem de vários clientes sem a necessidade de criá-los manualmente.

Por fim, aquilo que projetamos para o código foi alcançado, criando 5 opções no menu do restaurante: sair, mostrar o cardápio, adicionar um cliente, fazer checkout dos clientes adicionados e gerar clientes automaticamente. Todo o processo de criação do programa serviu para reforçar o conhecimento adquirido durante o semestre. As chamadas de áudio e vídeo para discussão e desenvolvimento do código, as pesquisas feitas utilizando os slides e códigos disponibilizados no moodle da disciplina, todas essas atividades foram essenciais para compreender como o sistema funcionaria.
