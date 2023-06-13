#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int id;
    char nome[50];
} TabelaAluno;

typedef struct {
    int id;
    char nome[50];
} TabelaDisciplina;

typedef struct {
    int id;
    int idAluno;
    int idDisciplina;
    float nota;
} TabelaNota;

typedef enum {
    ALUNO,
    DISCIPLINA,
    NOTA,
} tabelas;

void limparTela() {
    printf("pressione enter para continuar...");
    fflush(stdin);
    getchar();
    system("clear || cls");
}

void cadastrar(int tabela) {
    TabelaAluno tabAluno;
    TabelaDisciplina tabDisciplina;
    TabelaNota tabNota;
    int id;

    switch(tabela) {
        case ALUNO:
            printf("entre com o id: ");
            scanf("%d", &tabAluno.id);
            printf("entre com o nome do aluno: ");
            fflush(stdin);
            fgets(tabAluno.nome, 50, stdin);
            FILE *arquivoAluno = fopen("aluno.txt", "r");
            if(arquivoAluno == NULL) {
                printf("ERRO! nao foi possivel abrir aluno.txt\n");
                limparTela();
                return;
            }
            while(fscanf(arquivoAluno, "%d;%*[^\n]", &id) != EOF) {
                if(id == tabAluno.id) {
                    printf("ERRO! id ja existente\n");
                    fclose(arquivoAluno);
                    limparTela();
                    return;
                }
            }
            fclose(arquivoAluno);
            arquivoAluno = fopen("aluno.txt", "a");
            fprintf(arquivoAluno, "%d;%s", tabAluno.id, tabAluno.nome);
            fclose(arquivoAluno);
            printf("aluno cadastrado com sucesso!\n");
            limparTela();
            break;

        case DISCIPLINA:
            printf("entre com o id da disciplina: ");
            scanf("%d", &tabDisciplina.id);
            printf("entre com o nome da disciplina: ");
            fflush(stdin);
            fgets(tabDisciplina.nome, 50, stdin);
            FILE *arquivoDisciplina = fopen("disciplina.txt", "r");
            if(arquivoDisciplina == NULL) {
                printf("ERRO! nao foi possivel abrir disciplina.txt\n");
                limparTela();
                return;
            }
            while(fscanf(arquivoDisciplina, "%d;%*[^\n]", &id) != EOF) {
                if(id == tabDisciplina.id) {
                    printf("ERRO! id ja existente\n");
                    fclose(arquivoDisciplina);
                    limparTela();
                    return;
                }
            }
            fclose(arquivoDisciplina);
            arquivoDisciplina = fopen("disciplina.txt", "a");
            fprintf(arquivoDisciplina, "%d;%s", tabDisciplina.id, tabDisciplina.nome);
            fclose(arquivoDisciplina);
            printf("disciplina cadastrada com sucesso!\n");
            limparTela();
            break;

        case NOTA:
            printf("entre com o id da nota: ");
            scanf("%d", &tabNota.id);
            printf("entre com o id do aluno: ");
            scanf("%d", &tabNota.idAluno);
            printf("entre com o id da disciplina: ");
            scanf("%d", &tabNota.idDisciplina);
            printf("entre com a nota: ");
            scanf("%f", &tabNota.nota);
            FILE *arquivoNota = fopen("nota.txt", "r");
            if(arquivoNota == NULL) {
                printf("ERRO! nao foi possivel abrir nota.txt\n");
                limparTela();
                return;
            }
            while(fscanf(arquivoNota, "%d;%*[^\n]", &id) != EOF) {
                if(id == tabNota.id) {
                    printf("ERRO! id ja existente\n");
                    fclose(arquivoNota);
                    limparTela();
                    return;
                }
            }
            fclose(arquivoNota);
            arquivoDisciplina = fopen("nota.txt", "a");
            fprintf(arquivoNota, "%d;%d;%d;%.1f\n", tabNota.id, tabNota.idAluno, tabNota.idDisciplina, tabNota.nota);
            fclose(arquivoNota);
            printf("nota cadastrada com sucesso!\n");
            limparTela();
            break;
    }
}

void ler(int tabela) {
    TabelaAluno tabAluno;
    TabelaDisciplina tabDisciplina;
    TabelaNota tabNota;
    FILE *arquivoAluno = fopen("aluno.txt", "r");
    FILE *arquivoDisciplina = fopen("disciplina.txt", "r");
    FILE *arquivoNota = fopen("nota.txt", "r");

    switch(tabela) {
        case ALUNO:  
            if(arquivoAluno == NULL) {
                printf("ERRO! nao foi possivel abrir aluno.txt\n");
                limparTela();
                return;
            }
            printf("ID:\tNOME:\n");
            while(fscanf(arquivoAluno, "%d;%[^\n]", &tabAluno.id, tabAluno.nome) != EOF) {
                printf("%d\t%s\n", tabAluno.id, tabAluno.nome);
            }
            break;

        case DISCIPLINA:
            if(arquivoDisciplina == NULL) {
                printf("ERRO! nao foi possivel abrir disciplina.txt");
                limparTela();
                return;
            }
            printf("ID:\tNOME:\n");
            while(fscanf(arquivoDisciplina, "%d;%[^\n]", &tabDisciplina.id, tabDisciplina.nome) != EOF) {
                printf("%d\t%s\n", tabDisciplina.id, tabDisciplina.nome);
            }
            break;

        case NOTA:
            if(arquivoAluno == NULL || arquivoDisciplina == NULL || arquivoNota == NULL) {
                printf("ERRO! arquivos inacessiveis\n");
                limparTela();
                return;
            }
            printf("ALUNO:\tDISCIPLINA:\tNOTA:\n");
            while(fscanf(arquivoNota, "%d;%d;%d;%f", &tabNota.id, &tabNota.idAluno, &tabNota.idDisciplina, &tabNota.nota) != EOF) {
                while(fscanf(arquivoAluno, "%d;%[^\n]", &tabAluno.id, tabAluno.nome) != EOF) {
                    if(tabNota.idAluno == tabAluno.id) {
                        printf("%s\t", tabAluno.nome);
                        break;
                    }
                }
                rewind(arquivoAluno);
                while(fscanf(arquivoDisciplina, "%d;%[^\n]", &tabDisciplina.id, tabDisciplina.nome) != EOF) {
                    if(tabNota.idDisciplina == tabDisciplina.id) {
                        printf("%s\t\t", tabDisciplina.nome);
                        break;
                    }
                }
                rewind(arquivoDisciplina);
                printf("%.1f\n", tabNota.nota);
            }
    }
    fclose(arquivoAluno);
    fclose(arquivoDisciplina);
    fclose(arquivoNota);
    limparTela();
}

void excluir(int tabela) {
    TabelaAluno aluno;
    TabelaDisciplina tabDisciplina;
    TabelaNota tabNota;
    int encontrado = 0;
    int id;

    switch(tabela) {
        case ALUNO:    
            printf("entre com o id a ser excluido: ");
            scanf("%d", &id);
            FILE *arquivo = fopen("aluno.txt", "r");
            FILE *novoArquivo = fopen("aluno_temp.txt", "w");
            if(arquivo == NULL || novoArquivo == NULL) {
                printf("ERRO! nao foi possivel abrir aluno.txt\n");
                limparTela();
                return;
            }
            while(fscanf(arquivo, "%d;%[^\n]\n", &aluno.id, aluno.nome) != EOF) {
                if(aluno.id != id) {
                    fprintf(novoArquivo, "%d;%s\n", aluno.id, aluno.nome);
                }else {
                    encontrado++;
                }
            }
            fclose(arquivo);
            fclose(novoArquivo);
            remove("aluno.txt");
            rename("aluno_temp.txt", "aluno.txt");
            if(encontrado) {
                printf("aluno excluido com sucesso!\n");
                limparTela();
            }else {
                printf("nenhum aluno com esse id encontrado\n");
                limparTela();
            }
            break;

        case DISCIPLINA:
            printf("entre com o id da disciplina a ser excluida: ");
            scanf("%d", &id);
            FILE *arquivoDisciplina = fopen("disciplina.txt", "r");
            FILE *novoArquivoDisciplina = fopen("disciplina_temp.txt", "w");
            if(arquivoDisciplina == NULL || novoArquivoDisciplina == NULL) {
                printf("ERRO! nao foi possivel abrir disciplina.txt\n");
                limparTela();
                return;
            }
            while(fscanf(arquivoDisciplina, "%d;%[^\n]\n", &tabDisciplina.id, tabDisciplina.nome) != EOF) {
                if(tabDisciplina.id != id) {
                    fprintf(novoArquivoDisciplina, "%d;%s", tabDisciplina.id, tabDisciplina.nome);
                }else {
                    encontrado++;
                }
            }
            fclose(arquivoDisciplina);
            fclose(novoArquivoDisciplina);
            remove("disciplina.txt");
            rename("disciplina_temp.txt", "disciplina.txt");
            if(encontrado) {
                printf("disciplina excluida com sucesso!\n");
                limparTela();
            }else {
                printf("nenhuma disciplina com esse id encontrado\n");
                limparTela();
            }
            break;

        case NOTA:
            printf("entre com o id da nota a ser excluida: ");
            scanf("%d", &id);
            FILE *arquivoNota = fopen("nota.txt", "r");
            FILE *novoArquivoNota = fopen("nota_temp.txt", "w");
            if(arquivoNota == NULL || novoArquivoNota == NULL) {
                printf("ERRO! nao foi possivel abrir nota.txt");
                return;
            }
            while(fscanf(arquivoNota, "%d;%d;%d;%f", &tabNota.id, &tabNota.idAluno, &tabNota.idDisciplina, &tabNota.nota) != EOF) {
                if(tabNota.id != id) {
                    fprintf(novoArquivoNota, "%d;%d;%d;%.1f\n", tabNota.id, tabNota.idAluno, tabNota.idDisciplina, tabNota.nota);
                }else {
                    encontrado++;
                }
            } 
            fclose(arquivoNota);
            fclose(novoArquivoNota);
            remove("nota.txt");
            rename("nota_temp.txt", "nota.txt");
            if(encontrado) {
                printf("nota excluida com sucesso!\n");
                limparTela();
            }else {
                printf("nenhuma nota com esse id encontrada\n");
                limparTela();
            }
            break;
    
    }
}

void atualizar(int tabela) {
    TabelaAluno tabAluno;
    TabelaDisciplina tabDisciplina;
    TabelaNota tabNota;
    int encontrado = 0;
    int id;

    switch(tabela) {
        case ALUNO:
            printf("entre com o id a ser atualizado: ");
            scanf("%d", &id);
            FILE *arquivo = fopen("aluno.txt", "r");
            FILE *novoArquivo = fopen("aluno_temp.txt", "w");
            if(arquivo == NULL || novoArquivo == NULL) {
                printf("nao foi possivel abrir aluno.txt\n");
                limparTela();
                return;
            }
            while(fscanf(arquivo, "%d;%[^\n]", &tabAluno.id, tabAluno.nome) != EOF) {
                if(tabAluno.id == id) {
                    encontrado++;
                    printf("entre com o novo nome: ");
                    fflush(stdin);
                    fgets(tabAluno.nome, 50, stdin);
                    tabAluno.nome[strcspn(tabAluno.nome, "\n")] = '\0';
                }
                fprintf(novoArquivo, "%d;%s\n", tabAluno.id, tabAluno.nome);
            }
            fclose(arquivo);
            fclose(novoArquivo);
            remove("aluno.txt");
            rename("aluno_temp.txt", "aluno.txt");
            if(encontrado) {
                printf("aluno atualizado com sucesso!\n");
                limparTela();
            }else {
                printf("nenhum aluno com esse id encontrado\n");
                limparTela();
            }
            break;

        case DISCIPLINA:
            printf("entre com o id da disciplina a ser atualizada: ");
            scanf("%d", &id);
            FILE *arquivoDisciplina = fopen("disciplina.txt", "r");
            FILE *novoArquivoDisciplina = fopen("disciplina_temp.txt", "w");
            if(arquivoDisciplina == NULL || novoArquivoDisciplina == NULL) {
                printf("ERRO! nao foi possivel abrir disciplina.txt\n");
                limparTela();
                return;
            }
            while(fscanf(arquivoDisciplina, "%d;%[^\n]", &tabDisciplina.id, tabDisciplina.nome) != EOF) {
                if(tabDisciplina.id == id) {
                    encontrado++;
                    printf("entre com o novo nome para a disciplina: ");
                    fflush(stdin);
                    fgets(tabDisciplina.nome, 50, stdin);
                }
                fprintf(novoArquivoDisciplina, "%d;%s", tabDisciplina.id, tabDisciplina.nome);
            }
            fclose(arquivoDisciplina);
            fclose(novoArquivoDisciplina);
            remove("disciplina.txt");
            rename("disciplina_temp.txt", "disciplina.txt");
            if(encontrado) {
                printf("disciplina atualizada com sucesso!\n");
                limparTela();
            }else {
                printf("nehuma disciplina com esse id encontrada\n");
                limparTela();
            }
            break;

        case NOTA:
            printf("entre com o id da nota a ser atualizada: ");
            scanf("%d", &id);
            FILE *arquivoNota = fopen("nota.txt", "r");
            FILE *novoArquivoNota = fopen("nota_temp.txt", "w");
            if(arquivoNota == NULL || novoArquivoNota == NULL) {
                printf("ERRO! nao foi possivel abrir nota.txt\n");
                limparTela();
                return;
            }
            while(fscanf(arquivoNota, "%d;%d;%d;%f", &tabNota.id, &tabNota.idAluno, &tabNota.idDisciplina, &tabNota.nota) != EOF) {
                if(tabNota.id == id) {
                    encontrado++;
                    printf("entre com o novo id do aluno: ");
                    scanf("%d", &tabNota.idAluno);
                    printf("entre com o novo id da disciplina: ");
                    scanf("%d", &tabNota.idDisciplina);
                    printf("entre com o novo valor para a nota: ");
                    scanf("%f", &tabNota.nota);
                }
                fprintf(novoArquivoNota, "%d;%d;%d;%.1f\n", tabNota.id, tabNota.idAluno, tabNota.idDisciplina, tabNota.nota);
            }
            fclose(arquivoNota);
            fclose(novoArquivoNota);
            remove("nota.txt");
            rename("nota_temp.txt", "nota.txt");
            if(encontrado) {
                printf("nota atualizada com sucesso!\n");
                limparTela();
            }else {
                printf("nenhuma nota com esse id encontrada");
            }
    }
}

void menu() {
    int opcao;
    int sair = 0;

    system("clear || cls");
    while(sair == 0) {
        printf("MENU PRINCIPAL:\n");
        printf("1- menu de cadastro\n");
        printf("2- menu de leitura\n");
        printf("3- menu de exclusao\n");
        printf("4- menu de atualizacao\n");
        printf("0- sair\n");
        printf("opcao: ");
        scanf("%d", &opcao);
        system("clear || cls");
        switch(opcao) {
            case 1:
                printf("MENU DE CADASTRO:\n");
                printf("1- aluno\n");
                printf("2- disciplina\n");
                printf("3- nota\n");
                printf("opcao: ");
                scanf("%d", &opcao);
                system("clear || cls");
                switch(opcao) {
                    case 1:
                        cadastrar(ALUNO);
                        break;

                    case 2:
                        cadastrar(DISCIPLINA);
                        break;

                    case 3:
                        cadastrar(NOTA);
                        break;
                    
                    default:
                        printf("opcao invalida\n");
                        limparTela();
                }
                break;

            case 2:
                printf("MENU DE LEITURA:\n");
                printf("1- aluno\n");
                printf("2- disciplina\n");
                printf("3- nota\n");
                printf("opcao: ");
                scanf("%d", &opcao);
                system("clear || cls");
                switch(opcao) {
                    case 1:
                        ler(ALUNO);
                        break;

                    case 2:
                        ler(DISCIPLINA);
                        break;

                    case 3:
                        ler(NOTA);
                        break;

                    default:
                        printf("opcao invalida\n");
                        limparTela();
                }
                break;

            case 3:
                printf("MENU DE EXCLUSAO:\n");
                printf("1- aluno\n");
                printf("2- disciplina\n");
                printf("3- nota\n");
                printf("opcao: ");
                scanf("%d", &opcao);
                system("clear || cls");
                switch(opcao) {
                    case 1:
                        excluir(ALUNO);
                        break;
                
                    case 2:
                        excluir(DISCIPLINA);
                        break;

                    case 3:
                        excluir(NOTA);
                        break;

                    default:
                        printf("opcao invalida\n");
                        limparTela();
                }
                break;

            case 4:
                printf("MENU DE ATUALIZACAO:\n");
                printf("1- aluno\n");
                printf("2- disciplina\n");
                printf("3- nota\n");
                printf("opcao: ");
                scanf("%d", &opcao);
                system("clear || cls");
                switch(opcao) {
                    case 1:
                        atualizar(ALUNO);
                        break;

                    case 2: 
                        atualizar(DISCIPLINA);
                        break;

                    case 3:
                        atualizar(NOT1A);
                        break;

                    default:
                        printf("opcao invalida\n");
                        limparTela();
                }

                break;

            case 0:
                printf("saindo...\n");
                sair++;
                break;

            default:
                printf("opcao invalida\n");
                limparTela();
        }
    }
}

int main(void) {
    menu();
}