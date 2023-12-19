#include <iostream>
#include <cstring>

using namespace std;

const int m = 10;

struct Posicao {
    int linha;
    int coluna;
    string direcao;
};

// Função que verifica se dois caracteres são iguais, considerando maiúsculas e minúsculas
bool caracteresIguais(char c1, char c2) {
    if (c1 == c2) {
        return true;
    } else if ((c1 >= 'a' && c1 <= 'z') && (c2 >= 'A' && c2 <= 'Z') && (c1 - 'a' == c2 - 'A')) {
        return true;
    } else if ((c1 >= 'A' && c1 <= 'Z') && (c2 >= 'a' && c2 <= 'z') && (c1 - 'A' == c2 - 'a')) {
        return true;
    }
    return false;
}

bool verificaPalavra(char grade[m][m], char palavra[], int tamanho, int linha, int coluna, int dirLinha, int dirColuna) {
    for (int i = 0; i < tamanho; i++) {
        if (linha < 0 || linha >= m || coluna < 0 || coluna >= m || !caracteresIguais(grade[linha][coluna], palavra[i])) {
            return false;
        }
        linha += dirLinha;
        coluna += dirColuna;
    }
    return true;
}

Posicao procurarPalavra(char grade[m][m], char palavra[], int tamanho) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            // Vertical
            if (i + tamanho <= m && verificaPalavra(grade, palavra, tamanho, i, j, 1, 0)) {
                return {i, j, "verticalmente"};
            }
            // Horizontal
            if (j + tamanho <= m && verificaPalavra(grade, palavra, tamanho, i, j, 0, 1)) {
                return {i, j, "horizontalmente"};
            }
            // Diagonal
            if (i + tamanho <= m && j + tamanho <= m && verificaPalavra(grade, palavra, tamanho, i, j, 1, 1)) {
                return {i, j, "diagonalmente"};
            }
        }
    }
    return {-1, -1, ""};
}

int main() {
    int n, linhas, colunas;
    cin >> n >> linhas >> colunas;

    char palavras[n][100]; // Alterado para aceitar palavras de até 100 caracteres
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cin.getline(palavras[i], 100);
    }

    char grade[m][m];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grade[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        int tamanho = strlen(palavras[i]);
        Posicao pos = procurarPalavra(grade, palavras[i], tamanho);

        if (pos.linha != -1 && pos.coluna != -1) {
            cout << "A palavra " << palavras[i] << "foi localizada " << pos.direcao
                 << " a partir de posição (" << pos.linha << "," << pos.coluna << ")." << endl;
        } else {
            cout << "A palavra " << palavras[i] << " não foi localizada." << endl;
        }
    }

    return 0;
}
