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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,q,i,j,k;
int T,len;
bool mark[507][255];
char s[maxn];
int f[507],g[507];
int main(){
    scanf("%d%d%d",&n,&m,&q);
    REP(i,n){
        scanf("%s",s);
        len=strlen(s);
        REP(j,len) mark[i][s[j]]=1;
    }while(q--){
        scanf("%s",s);
        len=strlen(s);
        if (len>n) puts("NO");
        else{
            REP(i,len+1) f[i]=g[i]=0;f[0]=1;
            REP(i,n){
//                REP(j,len+1) printf("%d",f[j]);puts("");
                REP(j,len+1) g[j]=0;
                if (mark[i]['#']) REP(j,len+1) g[j]|=f[j];
                REP(j,len) if (mark[i][s[j]]) g[j+1]|=f[j];
                REP(j,len+1) f[j]=g[j];
            }if (f[len]) puts("YES");
            else puts("NO");
        }
    }
}
/*
3 2 100
a#
ab
b#

aaaa
aaaaaa
aab
bb
ba
abc
bc
c
b
*/
