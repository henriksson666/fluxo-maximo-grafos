# Fluxo Máximo em Grafos

Este projeto implementa dois algoritmos clássicos para o problema de fluxo máximo em grafos:

- **Edmonds-Karp**: Algoritmo baseado em busca em largura (BFS) para encontrar caminhos aumentantes.
- **Dinic**: Algoritmo eficiente que utiliza níveis e busca em profundidade (DFS) para encontrar múltiplos caminhos aumentantes por iteração.

## Estrutura

- `edmonds_karp.cpp`: Implementação do algoritmo de Edmonds-Karp.
- `dinic.cpp`: Implementação do algoritmo de Dinic.
- `main_test.cpp`: Script de teste automatizado que executa ambos algoritmos em vários grafos e salva os resultados.
- `resultados_teste.txt`: Arquivo gerado automaticamente com as estatísticas dos testes (fluxo máximo e tempo de execução para cada algoritmo e grafo).
- `exemplos/`: Exemplos de instâncias de entrada para testar os algoritmos manualmente.

## Como usar

1. Compile o arquivo de teste automatizado:

   ```sh
   g++ -O2 -std=c++17 main_test.cpp -o main_test
   ```

2. Execute o teste:

   ```sh
   ./main_test
   ```

3. Consulte o arquivo `resultados_teste.txt` para ver uma tabela comparativa dos algoritmos em diferentes grafos.

O arquivo `resultados_teste.txt` pode ser utilizado diretamente em artigos acadêmicos para análise de desempenho dos algoritmos.
