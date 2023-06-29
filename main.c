#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

// Estruturas de dados

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[20];
    char dataNascimento[20];
} Cliente;

typedef struct {
    int codigo;
    char nome[50];
    char telefone[20];
} Fornecedor;

typedef struct {
    int codigo;
    int quantidadeConvidados;
    char data[20];
    char diaSemana[20];
    char horarioInicio[20];
    char horarioFim[20];
    char tema[50];
    int codigoCliente;
    int codigoFornecedor;
} Festa;

typedef struct {
    int numeroContrato;
    float valorTotal;
    float desconto;
    float valorFinal;
    char formaPagamento[50];
    char status[20];
    int codigoFesta;
} Contrato;

// Constantes e arquivos

#define MAX_CLIENTES 100
#define MAX_FORNECEDORES 100
#define MAX_FESTAS 100
#define MAX_CONTRATOS 100

const char* CLIENTES_FILE = "clientes.txt";
const char* FORNECEDORES_FILE = "fornecedores.txt";
const char* FESTAS_FILE = "festas.txt";
const char* CONTRATOS_FILE = "contratos.txt";

// Funções auxiliares

void clear_input_buffer() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funções de cadastro

unsigned int gerarCodigo(unsigned int max) {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    // Gera um código aleatório único entre 1 e max
    return (unsigned int)rand() % max + 1;
}

int gerarCodigoCliente() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    return gerarCodigo(MAX_CLIENTES);
}

int gerarCodigoFornecedor() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    return gerarCodigo(MAX_FORNECEDORES);
}

bool verificarCodigoClienteExistente(int codigo) {
    FILE* file = fopen(CLIENTES_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return false;
    }

    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.codigo == codigo) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool verificarNumeroContratoExistente(int numeroContrato) {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    FILE* file = fopen(CONTRATOS_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de contratos.\n");
        return false;
    }

    Contrato contrato;
    while (fread(&contrato, sizeof(Contrato), 1, file)) {
        if (contrato.numeroContrato == numeroContrato) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

void cadastrarCliente() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    FILE* file = fopen(CLIENTES_FILE, "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    Cliente cliente;
    printf("Nome: ");
    clear_input_buffer();
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    printf("Endereço: ");
    fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
    printf("Telefone: ");
    fgets(cliente.telefone, sizeof(cliente.telefone), stdin);
    printf("Data de Nascimento (dd/mm/aaaa): ");
    fgets(cliente.dataNascimento, sizeof(cliente.dataNascimento), stdin);

    // Gerar código automaticamente
    cliente.codigo = gerarCodigoCliente();

    // Verificar se já existe um cliente com o mesmo código
    if (verificarCodigoClienteExistente(cliente.codigo)) {
        printf("Erro: Já existe um cliente com o código especificado.\n");
        fclose(file);
        return;
    }

    // Escrever os dados no arquivo
    fwrite(&cliente, sizeof(Cliente), 1, file);
    fclose(file);

    printf("Cliente cadastrado com sucesso.\n");
}

void cadastrarFornecedor() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    FILE* file = fopen(FORNECEDORES_FILE, "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de fornecedores.\n");
        return;
    }

    Fornecedor fornecedor;
    printf("Nome: ");
    clear_input_buffer();
    fgets(fornecedor.nome, sizeof(fornecedor.nome), stdin);
    printf("Telefone: ");
    fgets(fornecedor.telefone, sizeof(fornecedor.telefone), stdin);

    // Gerar código automaticamente
    fornecedor.codigo = gerarCodigoFornecedor();

    // Escrever os dados no arquivo
    fwrite(&fornecedor, sizeof(Fornecedor), 1, file);
    fclose(file);

    printf("Fornecedor cadastrado com sucesso.\n");
}

void cadastrarFesta() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    FILE* file = fopen(FESTAS_FILE, "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de festas.\n");
        return;
    }

    Festa festa;
    printf("Quantidade de convidados: ");
    scanf("%d", &festa.quantidadeConvidados);
    clear_input_buffer();
    printf("Data (dd/mm/aaaa): ");
    fgets(festa.data, sizeof(festa.data), stdin);
    printf("Dia da semana: ");
    fgets(festa.diaSemana, sizeof(festa.diaSemana), stdin);
    printf("Horário de início: ");
    fgets(festa.horarioInicio, sizeof(festa.horarioInicio), stdin);
    printf("Horário de fim: ");
    fgets(festa.horarioFim, sizeof(festa.horarioFim), stdin);
    printf("Tema: ");
    fgets(festa.tema, sizeof(festa.tema), stdin);
    printf("Código do cliente: ");
    scanf("%d", &festa.codigoCliente);
    printf("Código do fornecedor: ");
    scanf("%d", &festa.codigoFornecedor);

    // Escrever os dados no arquivo
    fwrite(&festa, sizeof(Festa), 1, file);
    fclose(file);

    printf("Festa cadastrada com sucesso.\n");
}

void atualizarStatusContrato() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    FILE* file = fopen(CONTRATOS_FILE, "r+b");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de contratos.\n");
        return;
    }

    int numeroContrato;
    printf("Número do contrato: ");
    scanf("%d", &numeroContrato);

    Contrato contrato;
    bool encontrado = false;

    // Procurar o contrato com o número especificado
    while (fread(&contrato, sizeof(Contrato), 1, file)) {
        if (contrato.numeroContrato == numeroContrato) {
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        printf("Contrato não encontrado.\n");
        fclose(file);
        return;
    }

    printf("Novo status (pago/pendente/cancelado): ");
    clear_input_buffer();
    fgets(contrato.status, sizeof(contrato.status), stdin);

    // Voltar para a posição correta no arquivo
    fseek(file, -sizeof(Contrato), SEEK_CUR);

    // Atualizar o status do contrato
    fwrite(&contrato, sizeof(Contrato), 1, file);
    fclose(file);

    printf("Status do contrato atualizado com sucesso.\n");
}

// Funções de exibição

void exibirClientes() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    FILE* file = fopen(CLIENTES_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    Cliente cliente;
    printf("Clientes cadastrados:\n");

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        printf("Código: %d\n", cliente.codigo);
        printf("Nome: %s", cliente.nome);
        printf("Endereço: %s", cliente.endereco);
        printf("Telefone: %s", cliente.telefone);
        printf("Data de Nascimento: %s\n", cliente.dataNascimento);
        printf("---------------------------\n");
    }

    fclose(file);
}

void exibirFornecedores() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    FILE* file = fopen(FORNECEDORES_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de fornecedores.\n");
        return;
    }

    Fornecedor fornecedor;
    printf("Fornecedores cadastrados:\n");

    while (fread(&fornecedor, sizeof(Fornecedor), 1, file)) {
        printf("Código: %d\n", fornecedor.codigo);
        printf("Nome: %s", fornecedor.nome);
        printf("Telefone: %s", fornecedor.telefone);
        printf("---------------------------\n");
    }

    fclose(file);
}

void exibirFestas() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    FILE* file = fopen(FESTAS_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de festas.\n");
        return;
    }

    Festa festa;
    printf("Festas cadastradas:\n");

    while (fread(&festa, sizeof(Festa), 1, file)) {
        printf("Código: %d\n", festa.codigo);
        printf("Quantidade de convidados: %d\n", festa.quantidadeConvidados);
        printf("Data: %s", festa.data);
        printf("Dia da semana: %s", festa.diaSemana);
        printf("Horário de início: %s", festa.horarioInicio);
        printf("Horário de fim: %s", festa.horarioFim);
        printf("Tema: %s", festa.tema);
        printf("Código do cliente: %d\n", festa.codigoCliente);
        printf("Código do fornecedor: %d\n", festa.codigoFornecedor);
        printf("---------------------------\n");
    }

    fclose(file);
}

void exibirContratos() {
setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos
    FILE* file = fopen(CONTRATOS_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de contratos.\n");
        return;
    }

    Contrato contrato;
    printf("Contratos cadastrados:\n");

    while (fread(&contrato, sizeof(Contrato), 1, file)) {
        printf("Número do contrato: %d\n", contrato.numeroContrato);
        printf("Valor total: R$ %.2f\n", contrato.valorTotal);
        printf("Desconto: R$ %.2f\n", contrato.desconto);
        printf("Valor final: R$ %.2f\n", contrato.valorFinal);
        printf("Forma de pagamento: %s", contrato.formaPagamento);
        printf("Status: %s", contrato.status);
        printf("Código da festa: %d\n", contrato.codigoFesta);
        printf("---------------------------\n");
    }

    fclose(file);
}

// Função principal

int main() {
    setlocale(LC_ALL, "Portuguese"); // Configurar localização para permitir acentos

    int opcao;

    while (true) {
        printf("----- Menu -----\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar fornecedor\n");
        printf("3. Cadastrar festa\n");
        printf("4. Atualizar status do contrato\n");
        printf("5. Exibir clientes\n");
        printf("6. Exibir fornecedores\n");
        printf("7. Exibir festas\n");
        printf("8. Exibir contratos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                cadastrarFornecedor();
                break;
            case 3:
                cadastrarFesta();
                break;
            case 4:
                atualizarStatusContrato();
                break;
            case 5:
                exibirClientes();
                break;
            case 6:
                exibirFornecedores();
                break;
            case 7:
                exibirFestas();
                break;
            case 8:
                exibirContratos();
                break;
            case 0:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }

        printf("\n");
    }

    return 0;
}

