#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>
#include <fstream>
#include <random>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

// Edmonds-Karp implementation
int edmonds_karp(vvi &capacity, int s, int t) {
    int n = capacity.size();
    int flow = 0;
    while (true) {
        vi parent(n, -1);
        queue<int> q;
        q.push(s);
        parent[s] = s;
        while (!q.empty() && parent[t] == -1) {
            int u = q.front(); q.pop();
            for (int v = 0; v < n; v++) {
                if (parent[v] == -1 && capacity[u][v] > 0) {
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        if (parent[t] == -1) break;
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, capacity[u][v]);
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
        flow += path_flow;
    }
    return flow;
}

// Dinic implementation
struct Dinic {
    struct Edge { int to, cap, rev; };
    vector<vector<Edge> > graph;
    vi level, iter;

    Dinic(int n) : graph(n), level(n), iter(n) {}

    void add_edge(int from, int to, int cap) {
        graph[from].push_back({to, cap, (int)graph[to].size()});
        graph[to].push_back({from, 0, (int)graph[from].size()-1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (size_t i = 0; i < graph[u].size(); ++i) {
                Edge &e = graph[u][i];
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int t, int f) {
        if (u == t) return f;
        for (int &i = iter[u]; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            if (e.cap > 0 && level[u] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, INT_MAX)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    std::ofstream outfile("resultados_teste.txt");
    outfile << "Comparação de Algoritmos de Fluxo Máximo\n";
    outfile << "----------------------------------------\n";
    outfile << "Testes automáticos com diferentes grafos\n\n";
    std::mt19937 rng(42); // random seed for reproducibility
    std::uniform_int_distribution<int> cap_dist(1, 20);
    std::vector<int> sizes = {6, 10, 20, 50, 100}; // diferentes tamanhos de grafo
    for (int n : sizes) {
        int s = 0, t = n-1;
        // Grafo denso: cada par de vértices pode ter aresta
        vvi capacity(n, vi(n, 0));
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (u != v && rng()%3 == 0) // 1/3 chance de aresta
                    capacity[u][v] = cap_dist(rng);
            }
        }
        // Grafo para Dinic
        Dinic dinic(n);
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (capacity[u][v] > 0)
                    dinic.add_edge(u, v, capacity[u][v]);
            }
        }
        // Copiar capacidade para Edmonds-Karp
        vvi cap_copy = capacity;
        auto start1 = std::chrono::high_resolution_clock::now();
        int flow1 = edmonds_karp(cap_copy, s, t);
        auto end1 = std::chrono::high_resolution_clock::now();
        double time1 = std::chrono::duration<double, std::milli>(end1 - start1).count();
        auto start2 = std::chrono::high_resolution_clock::now();
        int flow2 = dinic.max_flow(s, t);
        auto end2 = std::chrono::high_resolution_clock::now();
        double time2 = std::chrono::duration<double, std::milli>(end2 - start2).count();
        // Contar arestas
        int m = 0;
        for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) if (capacity[u][v] > 0) ++m;
        outfile << "Grafo com " << n << " vértices e " << m << " arestas\n";
        outfile << "Fonte: " << s << ", Sorvedouro: " << t << "\n";
        outfile << "Edmonds-Karp: fluxo max = " << flow1 << ", tempo = " << time1 << " ms\n";
        outfile << "Dinic:        fluxo max = " << flow2 << ", tempo = " << time2 << " ms\n\n";
    }
    outfile.close();
    return 0;
}
