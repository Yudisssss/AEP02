#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir estrutura para usuários
struct Usuario {
    char nome[50];
    char funcao[20];
    char senha[20];
};

// Função para criptografar a senha usando a tabela ASCII
void criptografarSenha(char senha[]) {
    for (int i = 0; i < strlen(senha); i++) {
        senha[i] += 3; // Deslocar 3 posições na tabela ASCII
    }
}

// Função para descriptografar a senha
void descriptografarSenha(char senha[]) {
    for (int i = 0; i < strlen(senha); i++) {
        senha[i] -= 3; // Deslocar de volta 3 posições
    }
}

// Função para adicionar um novo usuário
void adicionarUsuario() {
    struct Usuario user;
    FILE *file = fopen("usuarios.txt", "a");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o nome do usuario: \n");
    scanf("%s", user.nome);
    printf("Digite a funcao (diretor, supervisor, funcionario): \n");
    scanf("%s", user.funcao);
    printf("Digite a senha: \n");
    scanf("%s", user.senha);

    // Criptografar a senha antes de salvar
    criptografarSenha(user.senha);

    // Escrever os dados no arquivo
    fprintf(file, "%s %s %s\n", user.nome, user.funcao, user.senha);
    fclose(file);

    printf("Usuario adicionado com sucesso!\n");
}

// Função para listar todos os usuários
void listarUsuarios() {
    struct Usuario user;
    FILE *file = fopen("usuarios.txt", "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\n--- Lista de Usuarios ---\n");
    while (fscanf(file, "%s %s %s", user.nome, user.funcao, user.senha) != EOF) {
        // Descriptografar a senha para exibir
        descriptografarSenha(user.senha);
        printf("Nome: %s, Funcao: %s, Senha: %s\n", user.nome, user.funcao, user.senha);
    }
    fclose(file);
}

// Função para excluir um usuário
void excluirUsuario() {
    char nome[50];
    struct Usuario user;
    FILE *file = fopen("usuarios.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o nome do usuario a ser excluido: ");
    scanf("%s", nome);

    while (fscanf(file, "%s %s %s", user.nome, user.funcao, user.senha) != EOF) {
        if (strcmp(user.nome, nome) != 0) {
            fprintf(temp, "%s %s %s\n", user.nome, user.funcao, user.senha);
        }
    }

    fclose(file);
    fclose(temp);

    // Remover o arquivo original e renomear o temporário
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");

    printf("Usuario excluido com sucesso!\n");
}

// Função principal
int main() {
    int opcao;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Adicionar Usuario\n");
        printf("2. Listar Usuarios\n");
        printf("3. Excluir Usuario\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarUsuario();
                break;
            case 2:
                listarUsuarios();
                break;
            case 3:
                excluirUsuario();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}
