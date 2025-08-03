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

int n,k;
char a[maxn];
int change(int id){
    while (id<n&&!(a[id]=='4'&&a[id+1]=='7')) id++;
    if (id<n){
        if (id&1) a[id]=a[id+1]='7';
        else a[id]=a[id+1]='4';
    }return id;
}
int i,pre,T;
int tnow[maxn];
int main(){
    scanf("%d%d%s",&n,&k,a);
    pre=0;
    while (k){
        k--;T++;
        int now=change(pre);
//        printf("%d %d\n",now,pre);
//        puts(a);
        if (now==n) break;
        if (T>=n*10&&tnow[now]) k%=(tnow[i]-k);
        tnow[now]=k;pre=now-1;
        if (pre<0) pre=0;
    }puts(a);
}
/*
4 2000
4478
*/
