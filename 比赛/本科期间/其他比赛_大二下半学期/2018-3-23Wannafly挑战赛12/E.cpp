#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cstdlib>
#include <iomanip>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node {
    int n,d,c,pre;
    node(){}
    node(int _n,int _d,int _c,int _pre):n(_n),d(_d),c(_c),pre(_pre){};
    const bool operator <(const node &A)const {
        if (d!=A.d) return d>A.d;
        if (c!=A.c) return c>A.c;
        return n>A.n;
    }
};
int T;
int a,b,n,m;
int i,j,k;
int u,v;
int A[10],V[10];
int dis[maxn];
int pre[maxn],val[maxn];
int S[maxn],top;
priority_queue<node> Q;
int main(){
    scanf("%d%d%d",&a,&b,&n);
    m=gcd(a,b);
    REP(i,n) scanf("%d",&A[i]);int v;
    REP(i,n) scanf("%d",&v),V[A[i]]=v;
    scanf("%d%d",&u,&v);
    REP(i,m) dis[i]=INF,pre[i]=-1;
    Q.push(node(u%m,0,u,-233));
    while (Q.size()) {
        node x=Q.top();Q.pop();
        if (pre[x.n]!=-1) continue;//!
//        printf("Q: %d : %d, pre=%d\n",x.n,x.c,x.pre);
        pre[x.n]=x.pre;
        val[x.n]=x.c;
        if ((x.n*10+v)%m==0){
            S[++top]=v;
            for (int i=x.n;i!=-233;i=pre[i]) S[++top]=val[i];
            while (top) printf("%d",S[top--]);
            return 0;
        }
        REP(i,10) if (V[i]){
            int y=(x.n*10+i)%m;
            if (dis[y]>x.d+V[i]) {
                dis[y]=x.d+V[i];
                Q.push(node(y,dis[y],i,x.n));
            }
        }
    }
    puts("-1");
}
/*
*/
