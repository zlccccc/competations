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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int T;
int nxt[20000007][2];
int tot,ans;
void insert(char a[]){
    int now=0,i,len=strlen(a);
    REP(i,1000){
        int c=a[i%len]-'0';
        if (nxt[now][c]) ans=max(ans,i+1);
        else nxt[now][c]=++tot;
        now=nxt[now][c];
    }
}int n;
int i,j,k;
char a[507];
int main(){
    while (~scanf("%lld",&n)){
        REP(i,n){
            scanf("%s",a);
            insert(a);
        }FOR(i,0,tot) nxt[i][0]=nxt[i][1]=0;
        printf("%d\n",ans);
        ans=tot=0;
    }
}
/*
5 001 1000 0100 010 100
6 010 011 001 0010011 101 110
*/
