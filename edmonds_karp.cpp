#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

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
