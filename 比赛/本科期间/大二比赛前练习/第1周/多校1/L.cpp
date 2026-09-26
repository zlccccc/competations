#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <cmath>
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e6+7;
const LL M=1e9+7;
const double eps=0.0000001;
const LL gcd(LL a,LL b){return b?gcd(b,a%b):a;};
using namespace std;

namespace fastIO {
    #define BUF_SIZE 100000
    //fread -> read
    bool IOerror = 0;
    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if(p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if(pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    inline void read(int &x) {
        char ch;
        while(blank(ch = nc()));
        if(IOerror)
            return;
        for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
    }
    #undef BUF_SIZE
};
using namespace fastIO;

LL fac[maxn];
LL inv[maxn];
void init(){
    int i;
    fac[0]=1; 
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;
}
LL C(int m,int n){
    return fac[n]*inv[m]%M*inv[n-m]%M; 
}
struct node{
    int to,next;
}edge[maxn];
int cnt=0;
int head[maxn];
void addedge(int u,int v){
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
int num[maxn];
LL dfs(int u,int fa){
    LL ret=1;
    for (int i=head[u];i!=-1;i=edge[i].next) if (edge[i].to!=fa){
        int v=edge[i].to;
        ret=ret*dfs(v,u);
        ret=ret*C(num[u],num[u]+num[v])%M;
        num[u]+=num[v];
    }
    num[u]++;
    return ret;
}
int n;
int l[maxn];
int r[maxn];
int last;
stack<int> S;
int popnum[maxn],insnum[maxn];
int nxt[maxn];//judge
LL solve(int n){
    int i,j;
    FOR(i,1,n) read(l[i]);
    FOR(i,1,n) read(r[i]);
    FOR(i,1,n) nxt[i]=0;
    FOR(i,1,n) nxt[l[i]]=max(nxt[l[i]],r[i]);
    last=0;
    FOR(i,1,n) if (l[i]>r[i]) return 0;
    FOR(i,1,n){
        if (i<=last&&nxt[i]>last) return 0;//not available
        last=max(last,nxt[i]);
    }
    FOR(i,1,n) insnum[i]=popnum[i]=0;
    FOR(i,1,n) insnum[l[i]]++,popnum[r[i]]++;
    while (S.size()) S.pop();
    int tot=1;cnt=0;
    FOR(i,1,n+1) head[i]=-1;
    FOR(i,1,n){
        REP(j,insnum[i]){
            tot++;
            if (S.size()) addedge(S.top(),tot);
            else addedge(1,tot);
            S.push(tot);
        }
        REP(j,popnum[i]) S.pop();
    }
    FOR(i,1,n+1) num[i]=0;
    LL ans;
    ans=dfs(1,0);
    return ans;
}
int main(){
    init();
    int x=0;
    while (read(n), !fastIO::IOerror){
        printf("Case #%d: %lld\n",++x,solve(n));
    }
}
/*
*/