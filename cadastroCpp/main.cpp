#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Adicionei uma função de importar/exportar a lista de produtos para arquivo de planilha (CSV) para enriquecer as funções do código.
// Usei também um método eficiente de ordenação (Shell Sort).
// Essa implementação é baseada em um trabalho préviamente feito por mim na Universidade Federal de Lavras.

struct info {
    char nome[50];
    char desc[300];
    float preco;
    bool estaDisponivel;
};

void importCSV(ifstream &arqInCSV, info *&produtos, int cap, int &numProdutos) {
    string lixo;
    getline(arqInCSV, lixo);

    if (!arqInCSV.is_open()) {
        cerr << "Erro: Não foi possível abrir o arquivo CSV." << endl;
        return;
    }

    for (int i = 0; i < cap; i++) {
        arqInCSV.getline(produtos[i].nome, 50, ';');
        arqInCSV >> produtos[i].preco;
        arqInCSV.ignore();
        arqInCSV.getline(produtos[i].desc, 300, ';');
        int disponivel;
        arqInCSV >> disponivel;
        produtos[i].estaDisponivel = (disponivel == 1);
        arqInCSV.ignore();
        if(produtos[i].preco!=0){
        numProdutos++;
        }
    }
    cout << "Importação do arquivo \"produtos.csv\" para o programa concluída." << endl;
}

void exportCSV(ofstream &arqOutCSV, info *&produtos, int cap) {
    if (!arqOutCSV.is_open()) {
        cerr << "Erro: Não foi possível escrever no arquivo de saída." << endl;
        return;
    }

    arqOutCSV << "Nome;Preco;Descricao;Disponivel" << endl;
    for (int i = 0; i < cap; i++) {
        arqOutCSV << produtos[i].nome << ";" << produtos[i].preco << ";" << produtos[i].desc << ";"
                  << (produtos[i].estaDisponivel ? 1 : 0) << endl;
    }
    cout << "Exportação para o arquivo \"produtos_out.csv\" concluída." << endl;
}

void shellSortPreco(info *&produtos, int cap) {
    const int ciuraGaps[] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int pos_gap = 8;

    while (ciuraGaps[pos_gap] > cap) {
        pos_gap--;
    }

    while (pos_gap >= 0) {
        int gap = ciuraGaps[pos_gap];

        for (int i = gap; i < cap; i++) {
            info temp = produtos[i];
            int j = i;
            while (j >= gap && produtos[j - gap].preco > temp.preco) {
                produtos[j] = produtos[j - gap];
                j -= gap;
            }
            produtos[j] = temp;
        }

        pos_gap--;
    }

    cout << "Ordenação eficiente por preço concluída." << endl;
}

void checarDisponibilidade(info *produtos, int cap) {
    for (int i = 0; i < cap; ++i) {
        if (produtos[i].estaDisponivel) {
            cout << "Disponível" << endl;
        } else {
            cout << "Indisponível" << endl;
        }
    }
}

void buscaPorNome(info *produtos, int cap, const char *nomeProcurado) {
    bool encontrado = false;

    for (int i = 0; i < cap; ++i) {
        if (strcmp(produtos[i].nome, nomeProcurado) == 0 && !encontrado) {
            cout << "Nome: " << produtos[i].nome << endl
                 << "Preço: " << produtos[i].preco << endl
                 << "Descrição: " << produtos[i].desc << endl
                 << "Disponibilidade: ";
            checarDisponibilidade(produtos, cap);
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "Produto não encontrado." << endl;
    }
}

void cadastrarProduto(info *&produtos, int &capacidade, int &numProdutos) {
    if (numProdutos < capacidade) {
        cout << "Nome do produto: ";
        cin.ignore();
        cin.getline(produtos[numProdutos].nome, sizeof(produtos[numProdutos].nome));

        cout << "Descrição do produto: ";
        cin.getline(produtos[numProdutos].desc, sizeof(produtos[numProdutos].desc));

        // Loop para garantir que o preço seja válido
        do {
            cout << "Preço do produto: ";
            cin >> produtos[numProdutos].preco;
            cin.ignore(); // Limpar o buffer do teclado

            if (produtos[numProdutos].preco <= 0) {
                cout << "Erro: O preço do produto deve ser maior que zero. Tente novamente." << endl;
            }
        } while (produtos[numProdutos].preco <= 0);

        cout << "Disponível para venda (1 para Sim / 0 para Não): ";
        cin >> produtos[numProdutos].estaDisponivel;

        numProdutos++;
        cout << "Produto cadastrado com sucesso!" << endl;
    } else {
        cout << "Limite de produtos atingido!" << endl;
    }
}

int main() {
    int capacidade = 100;
    info *produtos = new info[capacidade];
    int numProdutos = 0;

    ifstream arqInCSV("produtos_in.csv");
    if (!arqInCSV.is_open()) {
        cout << "Erro: Não foi possível abrir o arquivo CSV." << endl;
        return 1;
    } else {
        cout << "Arquivo de entrada CSV aberto com sucesso." << endl;
    }

    importCSV(arqInCSV, produtos, capacidade, numProdutos);
    arqInCSV.close();

    int opcao;
    do {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Listar produtos" << endl;
        cout << "2. Ordenar produtos por preço" << endl;
        cout << "3. Buscar produto por nome" << endl;
        cout << "4. Exportar lista de produtos" << endl;
        cout << "5. Cadastrar novo produto" << endl;
        cout << "6. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                if (numProdutos > 0) {
                    cout << "=== Lista de Produtos ===" << endl;
                    for (int i = 0; i < numProdutos; ++i) {
                        cout << "Nome: " << produtos[i].nome << endl
                             << "Preço: " << produtos[i].preco << endl
                             << "Descrição: " << produtos[i].desc << endl
                             << "Disponibilidade: " << (produtos[i].estaDisponivel ? "Sim" : "Não") << endl;
                    }
                } else {
                    cout << "Nenhum produto cadastrado ainda." << endl;
                }
                break;
            case 2:
                if (numProdutos > 0) {
                    shellSortPreco(produtos, numProdutos);
                } else {
                    cout << "Nenhum produto cadastrado ainda." << endl;
                }
                break;
            case 3: {
                char nomeProcurado[50];
                cout << "Digite o nome do produto a ser buscado: ";
                cin.ignore(); // Limpa o buffer do teclado
                cin.getline(nomeProcurado, sizeof(nomeProcurado));
                buscaPorNome(produtos, numProdutos, nomeProcurado);
                break;
            }
            case 4: {
                ofstream arqOutCSV("produtos_out.csv");
                exportCSV(arqOutCSV, produtos, numProdutos);
                arqOutCSV.close();
                break;
            }
            case 5:
                cadastrarProduto(produtos, capacidade, numProdutos);
                break;
            case 6:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
                break;
        }
    } while (opcao != 6);

    delete[] produtos;

    return 0;
}