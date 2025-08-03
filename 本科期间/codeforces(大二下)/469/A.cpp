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
#include <cassert>
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

int n,m;
int i,j,k;
char a[maxn];
int suf[maxn];
bool mark[maxn];
stack<int> S0,S1;
vector<int> ans[maxn];
int main(){
    scanf("%s",a+1);
    n=strlen(a+1);
    rFOR(i,1,n){
        if (a[i]=='1'){
            if (!S0.size()) return 0*puts("-1");
            suf[i]=S0.top();S0.pop();
            S1.push(i);
        }else {
            S0.push(i);
            if (!S1.size()) continue;
            suf[i]=S1.top();S1.pop();
        }
    }
    if (S1.size()) return 0*puts("-1");
    int Ans=0;
    FOR(i,1,n) if (!mark[i]){
        for (j=i;j;j=suf[j]) ans[i].push_back(j),mark[j]=1;
        Ans++;
    }printf("%d\n",Ans);
    FOR(i,1,n) if (ans[i].size()){
        printf("%d",ans[i].size());
        for (int v:ans[i]) printf(" %d",v);
        puts("");
    }
}
/*
*/
