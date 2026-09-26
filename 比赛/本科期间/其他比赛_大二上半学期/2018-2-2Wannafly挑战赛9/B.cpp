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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
int i,j,k;
string a[maxn],s;
int nxt[maxn];
LL ans=1;
int main(){
    cin>>n;
    FOR(i,1,n){
        cin>>a[i];
        if (s==""||a[i].length()<s.length()) s=a[i];
    }FOR(i,1,n)
        if (a[i].length()==s.length()&&a[i]!=s){
        FOR(j,1,n) puts("0");
        return 0;
    }nxt[0]=-1;
    rep(i,1,s.length()){
        j=nxt[i-1];
        while (j>=0&&s[j+1]!=s[i]) j=nxt[j];
        if (s[i]==s[j+1]) nxt[i]=j+1;
        else nxt[i]=-1;
    }
    FOR(k,1,n){
        j=-1;int now=0;
        REP(i,a[k].length()){
            while (j>=0&&s[j+1]!=a[k][i]) j=nxt[j];
            if (a[k][i]==s[j+1]) j++;
            if (j==s.length()-1) now++,j=nxt[j];
        }
        ans=ans*now%M;
    }
    FOR(i,1,n){
        if (a[i]==s) cout<<ans<<"\n";
        else cout<<0<<"\n";
    }
}
/*
5
iiiiiiii
iiiiiiiiiii
iiiiiiiiiii
iiiiiiiiiii
iiiiiiiiiii

2
BALDRSKYKirishimaRain
i
*/
