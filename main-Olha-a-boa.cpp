#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

#define linha 5
#define coluna 5

struct Celula {
    int numero;
    bool marcado;
};

struct Cartela {
    Celula celulas[linha][coluna];
};

// Função para gerar números aleatórios sem repetição na mesma cartela
int gerarAleatorio(set<int>& numerosGerados, int min, int max) {
    int numero;
    do {
        numero = min + (rand() % (max - min + 1));
    } while (numerosGerados.find(numero) != numerosGerados.end());
    numerosGerados.insert(numero);
    return numero;
}

// Função para gerar a cartela de bingo
void gerarCartelas(Cartela& c) {
    set<int> numerosCartela;
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            // Definindo a posição central como "FREE"
            if (i == 2 && j == 2) {
                c.celulas[i][j].numero = -1; // Valor especial para "FREE"
                c.celulas[i][j].marcado = true;
            } else {
                // Definindo o intervalo de números para cada coluna
                int min = j * 15 + 1;
                int max = (j + 1) * 15;
                c.celulas[i][j].numero = gerarAleatorio(numerosCartela, min, max);
                c.celulas[i][j].marcado = false;
            }
        }
    }
}

// Função para visualizar a cartela com o cabeçalho "BINGO"
void visualizarCartela(Cartela& c) {
    // Definindo o cabeçalho "BINGO" usando um array de string
    string cabecalho[] = {"B", "I", "N", "G", "O"};
    for (int i = 0; i < 5; i++) {
        cout << cabecalho[i] << "\t"; // Imprime cada letra em sua respectiva coluna
    }
    cout << endl;

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if (i == 2 && j == 2) { // Posição central
                cout << "FREE\t";
            } else {
                cout << c.celulas[i][j].numero << "\t";
            }
        }
        cout << endl;
    }
    
     cout << endl << endl<<endl;
}

// Função para marcar números chamados
void marcarNumero(Cartela& c, int numeroChamado[], int tamanho, int numeroCartela) {
    for (int k = 0; k < tamanho; k++) {
        bool encontrado = false;
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                if (c.celulas[i][j].numero == numeroChamado[k]) {
                    c.celulas[i][j].marcado = true;
                    encontrado = true;
                }
            }
        }
        if (encontrado) {
            cout << "Numero " << numeroChamado[k] << " marcado na Cartela " << numeroCartela << "!" << endl;
        } else {
            cout << "Numero " << numeroChamado[k] << " nao encontrado na Cartela " << numeroCartela << "..." << endl;
        }
    }
}

// Função para visualizar a cartela com números marcados e o cabeçalho "BINGO"
void visualizarCartelaMarcada(Cartela& c, int numeroCartela) {
    // Definindo o cabeçalho "BINGO" usando um array de string
    string cabecalho[] = {"B", "I", "N", "G", "O"};
    for (int i = 0; i < 5; i++) {
        cout << cabecalho[i] << "\t"; // Imprime cada letra em sua respectiva coluna
    }
    cout << endl;

    cout << "\nCartela " << numeroCartela << " marcada:\n";
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if (i == 2 && j == 2) { // Posição central
                cout << "[FREE]\t";
            } else if (c.celulas[i][j].marcado) {
                cout << "[" << c.celulas[i][j].numero << "]\t";
            } else {
                cout << c.celulas[i][j].numero << "\t";
            }
        }
        cout << endl;
    }
}

// Função para mostrar os números chamados
void mostrarNumerosChamados(int numeroChamado[], int tamanho) {
    if (tamanho == 0) {
        cout << "Nenhum número foi chamado." << endl;
        return;
    }

    cout << "Numeros chamados: ";
    for (int i = 0; i < tamanho; i++) {
        cout << numeroChamado[i] << " ";
    }
    cout << endl;
}

int main() {
    int resposta;
    int qtdCartelas;
    int tamanho = 0;
    int* numeroChamado = nullptr;

    cout << "Digite o numero de cartelas que deseja: ";
    cin >> qtdCartelas;
    cout << endl;

    Cartela* cartelas = new Cartela[qtdCartelas];

    do {
        cout << "+------------------ Menu ---------------+" << endl;
        cout << "| 1 - Gerar cartelas                    |" << endl;
        cout << "| 2 - Visualizar cartelas               |" << endl;
        cout << "| 3 - Marcar numeros chamados           |" << endl;
        cout << "| 4 - Mostrar numeros chamados          |" << endl;
        cout << "| 5 - Exibir cartelas e numeros chamados|" << endl;
        cout << "| 6 - Sair                              |" << endl;
        cout << "+---------------------------------------+" << endl;

        cout << "\nEscolha uma opcao: ";
        cin >> resposta;
        cout << endl;

        switch (resposta) {
            case 1: {
                cout << "Gerar cartelas: \n";
                for (int i = 0; i < qtdCartelas; i++) {
                    gerarCartelas(cartelas[i]);
                    cout << "Cartela " << i + 1 << " gerada com sucesso!" << endl;
                }
                break;
            }

            case 2: {
                cout << "Visualizar cartelas: \n";
                for (int i = 0; i < qtdCartelas; i++) {
                    visualizarCartela(cartelas[i]);
                }
                break;
            }

            case 3: {
                cout << "Marcar numeros chamados: \n";
                cout << "Quantos numero deseja marcar? R: ";
                cin >> tamanho;

                delete[] numeroChamado;
                numeroChamado = new int[tamanho];
                cout << "Digite os numeros chamados: ";
                for (int i = 0; i < tamanho; i++) {
                    cin >> numeroChamado[i];
                }

                for (int i = 0; i < qtdCartelas; i++) {
                    cout << "\nMarcando numeros na Cartela " << i + 1 << ":\n";
                    marcarNumero(cartelas[i], numeroChamado, tamanho, i + 1);
                }
                break;
            }

            case 4: {
                cout << "Mostrar numeros chamados: \n";
                mostrarNumerosChamados(numeroChamado, tamanho);
                break;
            }

            case 5: {
                cout << "Exibir cartelas e numeros chamados: \n";
                for (int i = 0; i < qtdCartelas; i++) {
                    visualizarCartelaMarcada(cartelas[i], i + 1);
                }
                break;
            }

            case 6: {
                cout << "Encerrando o programa, até a próxima!" << endl;
                break;
            }

            default: {
                cout << "Opção inválida, tente novamente!" << endl;
                break;
            }
        }

    } while (resposta != 6);

    delete[] cartelas;

    return 0;
}
