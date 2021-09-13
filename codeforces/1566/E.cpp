#include <bits/stdc++.h>
using namespace std;
void main_() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int _tests = 1;
    cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        int n;
        cin >> n;
        vector<vector<int>> g(n);
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int total = 0;
        vector<int> marked(n);
        auto dfs = [&](const auto &self, int u, int p) -> void {
            int children = (int)g[u].size() - 1;
            for (auto v : g[u]) {
                if (v == p) continue;
                self(self, v, u);
                if (marked[v]) {
                    --children;
                }
            }
            if (children > 0) {
                total += children - 1;
                marked[u] = true;
            }
        };
        for (auto u : g[0]) {
            dfs(dfs, u, 0);
        }
        int cnt = 0;
        for (auto u : g[0]) {
            if (!marked[u]) {
                cnt++;
            }
        }
        cnt = max(1, cnt);
        cout << total + cnt << '\n';
    }
}
static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
        "mov %%rsp, (%0)\n"
        "mov %0, %%rsp\n"
        :
        : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}
int main() {
    run_with_stack_size(main_, 1024 * 1024 * 100);
    return 0;
}
