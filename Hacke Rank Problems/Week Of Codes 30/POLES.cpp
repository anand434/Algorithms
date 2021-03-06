#include <cstdio>
#include <deque>
using namespace std;
typedef long long i64;
typedef long double real;
const int MAXN = 5e3;
int weight[MAXN + 5], pos[MAXN + 5];
i64 A[MAXN + 5], B[MAXN + 5], F[MAXN + 5];
struct line {
    i64 slope, xterm;
    inline i64 get(const int x) const {
        return slope * x + xterm;
    }
};
deque<line> lines;
inline real area(const line& a, const line& b, const line& c) {
    real ax = (b.slope - a.slope);
    real bx = (c.xterm - a.xterm);
    real ay = (c.slope - a.slope);
    real by = (b.xterm - a.xterm);
    return ax * bx - ay * by;
}
inline bool cw(const line& a, const line& b, const line& c) {
    return area(a, b, c) < 0;
}
void insert(const line& l) {
    while (lines.size() > 1 && cw(lines[lines.size() - 2], lines[lines.size() - 1], l))
        lines.pop_back();
    if (lines.size() == 1) {
        if (lines.front().xterm > l.xterm)
            lines.push_back(l);
    } else lines.push_back(l);
}
i64 query(int x) {
    if (lines.empty())
        return 0;
    while (lines.size() > 1 && lines[0].get(x) > lines[1].get(x))
        lines.pop_front();
    return lines[0].get(x);
}
i64 dp[MAXN][2];
int main() {

    register int N, K, x, k;

    scanf("%d%d", &N, &K);
    for (x = N - 1; x >= 0; --x)
        scanf("%d%d", pos + x, weight + x);

    for (x = 0; x < N; ++x) {
        A[x] = weight[x] + (x ? A[x - 1] : 0);
        B[x] = pos[x] * (i64) weight[x] + (x ? B[x - 1] : 0);

        F[x] = dp[x][1] = B[x] - pos[x] * A[x];
    }

    for (k = 2; k <= K; ++k) {
        lines.clear();
        insert((line) {A[k - 2], dp[k - 2][(k - 1) & 1] - B[k - 2]});
        for (x = k - 1; x < N; ++x) {
            if (k == x + 1)
                dp[x][k & 1] = 0;
            else
                dp[x][k & 1] = F[x] + query(pos[x]);
            insert((line) {A[x], dp[x][(k - 1) & 1] - B[x]});
        }
    }

    printf("%lld\n", dp[N - 1][K & 1]);
    return 0;
}