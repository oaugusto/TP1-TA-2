#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../include/clinic_list.h"

typedef struct {
    int vagas_totais;
    int vagas_restantes;
} posto;

typedef struct {
    double idade;
    int nb_aplicacoes;
} candidato;

int main(int argc, char** argv)
{
    int i, j, id, vagas;
    double idade;
    int nb_postos, nb_candidatos, nb_aplicacoes;

    /***************************
    * Leitura dos postos       *
    ****************************/

    scanf("%d", &nb_postos);
    posto postos[nb_postos];
    
    for (i = 0; i < nb_postos; i++) {
        scanf("%d", &vagas);
        postos[i].vagas_totais = vagas;
        postos[i].vagas_restantes = vagas;
    }

    /***************************
    * Leitura candidatos       *
    ****************************/

    scanf("%d", &nb_candidatos);
    candidato candidatos[nb_candidatos];

    // Array pra manter a lista de prioridade dos candidatos
    // Se encontrar -1 acabou a lista e pode retornar
    int *lista_preferencia[nb_candidatos];//;[nb_postos];

    for (i = 0; i < nb_candidatos; i++) {
        lista_preferencia[i] = (int *)malloc(nb_postos * sizeof(int)); 
        memset(lista_preferencia[i], -1, sizeof(int) * nb_postos);
    }

    // memset(lista_preferencia, -1, sizeof(int) * nb_candidatos * nb_postos);

    for (i = 0; i < nb_candidatos; i++) {
        scanf("%d %lf", &nb_aplicacoes, &idade);
        candidatos[i].idade = idade;
        candidatos[i].nb_aplicacoes = nb_aplicacoes;
        for (j = 0; j < nb_aplicacoes; j++) {
            scanf("%d", &id);
            lista_preferencia[i][j] = id-1;
        }
    }

    // Array para guardar quais candidatos estao sem vagas ou alocados a um posto
    // Ex: (-1 nao esta alocado 5 esta alocado no posto 5)
    int alocacoes[nb_candidatos];
    memset(alocacoes, -1, sizeof(int)*nb_candidatos);

    // Quantidade de candidatos que ainda nao estao alocados
    int nb_candidatos_livres = nb_candidatos;

    // Variavel para verificar se o estado mudou em um loop completo de candidatos, se nao mudou, nao ha mais vagas a serem alocadas e esta estavel
    int mudou_estado = 0, id_candidato;

    while(nb_candidatos_livres > 0) {
        mudou_estado = 0;
        
        // Percorra todos os candidatos
        for (id_candidato = 0; id_candidato < nb_candidatos; id_candidato++)
        {
            // Se ja esta alocado, ignore
            if (alocacoes[id_candidato] != -1)
                continue;

            // printf("Numero candidatos livres %d\n", nb_candidatos_livres);
        
            // Percorra a lista de preferencia do candidato
            for (i = 0; i < nb_postos; i++) {
                int id_posto_preferencia = lista_preferencia[id_candidato][i];

                // Se nao ha posto com alocacao dentro dos postos de preferencia, saia TODO
                if (id_posto_preferencia == -1)
                    break;

                // Se o postos tem vaga, faça o match
                if (postos[id_posto_preferencia].vagas_restantes > 0)
                {
                    
                    alocacoes[id_candidato] = id_posto_preferencia;
                    nb_candidatos_livres--;
                    postos[id_posto_preferencia].vagas_restantes--;
                    mudou_estado = 1;

                    // printf("Candidato %d %lf alocado no posto %d\n", id_candidato, candidatos[id_candidato].idade, id_posto_preferencia);
                    break;
                    
                // Se o post nao tem vaga verifique se o posto tem prioridade para aquele candidato
                } 
                else
                {
                    // Flag pra controlar se trocou com outro candidato, caso sim, saia do loop
                    int swapped = 0;
                    
                    // Verifica se tem algum candidato com match no posto que tenha a idade menor que o candidato atual
                    for (j = 0; j < nb_candidatos; j++)
                    {
                        // Se o aluno j esta alocado para a universidade
                        if (alocacoes[j] == id_posto_preferencia)
                        {
                            // NOTA: Aqui poderia ser mais otimizado se tivesse uma lista de prioridades
                            //       mas adicionaria uma complexidade bem maior
                            // Se a idade dele for menor que o atual OU se a idade for igual mas ele aplicou antes, desaloque-o e aloque o novo
                            if ( (candidatos[j].idade < candidatos[id_candidato].idade) || (candidatos[j].idade == candidatos[id_candidato].idade && j > id_candidato))
                            {
                                alocacoes[j] = -1;
                                alocacoes[id_candidato] = id_posto_preferencia;
                                mudou_estado = 1;

                                swapped = 1;
                                break;                                
                            }
                        }
                    }

                    // Se trocou de vaga com outro candidato, saia do loop
                    if (swapped)
                        break;
                }
            }
        }

        // Se nao mudou o estado no loop dos candidatos, nao ha mais vagas a serem alocadas
        if (mudou_estado == 0)
        {
            break;
        }

    }

    // Print final
    printf("Grupos com alocacao\n");
    for (i = 0; i < nb_candidatos; i++) {
        if (alocacoes[i] != -1) {
            printf("%d %d\n", i+1, alocacoes[i]+1);
        }
    }

    printf("nao alocados\n");
    for (i = 0; i < nb_candidatos; i++) {
        if (alocacoes[i] == -1) {
            printf("%d\n", i+1);
        }
    }

    // Free memory
    for (i = 0; i < nb_candidatos; i++) {
        free(lista_preferencia[i]);
    }

    return 0;
}