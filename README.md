# C Generic List

Uma implementação de uma lista ligada genérica e de tipagem dinâmica em C, utilizando um estilo de programação orientado a objetos com ponteiros de função.

Esta biblioteca fornece uma estrutura de lista flexível que pode armazenar diferentes tipos de dados, incluindo inteiros, strings, floats, doubles e ponteiros genéricos (`void*`), cuidando da alocação e cópia de memória quando necessário.

## ✨ Funcionalidades

- **Tipagem Dinâmica**: Crie listas para armazenar `int`, `float`, `double`, `char*` (strings) ou ponteiros genéricos (`void*`).
- **Interface Orientada a Objetos**: Interaja com a lista usando "métodos" através de ponteiros de função (ex: `minhaLista->push(...)`).
- **Gerenciamento de Memória**: A biblioteca gerencia a alocação de memória para tipos primitivos e strings, copiando os valores em vez de apenas armazenar ponteiros.
- **Conjunto Completo de Operações**:
  - `push`: Adiciona um elemento ao final.
  - `pop`: Remove e retorna o primeiro elemento.
  - `insert`: Insere um elemento em um índice específico.
  - `remove`: Remove um elemento de um índice específico.
  - `pick`: Remove e retorna um elemento de um índice específico.
  - `get`: Obtém um ponteiro para o elemento em um índice.
  - `set`: Atualiza o valor em um índice.
  - `len`: Retorna o número de elementos.
  - `foreach`: Itera sobre a lista e aplica uma função a cada elemento.
  - `print`: Imprime o conteúdo da lista (para tipos básicos).
  - `free`: Libera toda a memória alocada pelos nós da lista.

## 🚀 Como Compilar e Executar

O projeto utiliza **CMake** para a compilação.

### Pré-requisitos
- CMake
- Um compilador C (como GCC/MinGW ou Clang)

### Passos para Compilação

1.  **Clone o repositório:**
    ```bash
    git clone https://github.com/Slot148/C-generic-list.git
    cd C-generic-list
    ```

2.  **Crie um diretório de build:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Execute o CMake e compile o projeto:**
    ```bash
    # Para MinGW no Windows
    cmake .. -G "MinGW Makefiles"
    cmake --build .

    # Para Makefiles no Linux/macOS
    cmake ..
    make
    ```

4.  **Execute o programa principal (que roda os testes):**
    ```bash
    ./meu_programa
    ```

## 📋 Exemplos de Uso

Abaixo estão alguns exemplos de como usar a biblioteca.

### Lista de Inteiros

```c
#include "Tlist.h"

int main() {
    // Cria uma nova lista para armazenar inteiros
    List intList = newList(INT);

    // Adiciona elementos
    intList->push(intList, 10);
    intList->push(intList, 20);
    intList->push(intList, 30);

    // Imprime a lista
    intList->print(intList); // Saída: [ 10, 20, 30 ]

    // Libera a memória da lista
    intList->free(intList);
    free(intList);

    return 0;
}
```

### Lista de Structs (Ponteiros Genéricos)

```c
#include "Tlist.h"
#include <stdio.h>

typedef struct {
    char* nome;
    int idade;
} Pessoa;

void printPessoa(void* data) {
    Pessoa* p = (Pessoa*)data;
    printf("Pessoa{ nome=%s, idade=%d }\n", p->nome, p->idade);
}

int main() {
    // Cria uma nova lista para armazenar ponteiros (tipo T)
    List pessoaList = newList(T);

    Pessoa p1 = {"Alice", 30};
    Pessoa p2 = {"Bob", 25};

    // Adiciona os ponteiros para as structs
    pessoaList->push(pessoaList, &p1);
    pessoaList->push(pessoaList, &p2);

    // Itera e imprime cada elemento usando uma função customizada
    pessoaList->foreach(pessoaList, printPessoa);

    // Libera a memória da lista
    pessoaList->free(pessoaList);
    free(pessoaList);

    return 0;
}
```

## 📚 Documentação

A documentação completa da API pode ser gerada usando **Doxygen**.

1.  Certifique-se de ter o Doxygen instalado.
2.  Na raiz do projeto, execute:
    ```bash
    doxygen Doxyfile
    ```
3.  Abra o arquivo `docs/html/index.html` em seu navegador para visualizar a documentação.
