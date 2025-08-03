#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
 
#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=2e5+107;

char str[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        /*to solve the problem*/
        int n,m,i,j;
        scanf("%d%d",&n,&m);
        if (m==1) {
            puts("YES");
            FOR(i,1,n) printf("%d\n",i);
        } else {
            if (n&1) puts("NO");
            else {
                puts("YES");
                FOR(i,1,n/2) {
                    FOR(j,1,m) printf("%d%c",(i-1)*2*m+j*2-1," \n"[j==m]);
                    FOR(j,1,m) printf("%d%c",(i-1)*2*m+j*2," \n"[j==m]);
                }
            }
        }
    }
}
/*
*/