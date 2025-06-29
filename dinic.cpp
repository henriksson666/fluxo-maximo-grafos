#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

struct Dinic {
    struct Edge { int to, cap, rev; };
    vector<vector<Edge>> graph;
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
            for (auto &e : graph[u]) {
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
