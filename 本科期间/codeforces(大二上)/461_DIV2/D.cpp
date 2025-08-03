#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
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

int n,m;
int i,j;
LL a[maxn],b[maxn];
int id[maxn];
LL ans,AA;
bool cmp(int i,int j){
    return a[i]*b[j]>a[j]*b[i];
}
char s[maxn];
int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%s",s);id[i]=i;
        int len=strlen(s);;
        REP(j,len){
            if (s[j]=='s')  a[i]++;
            else ans+=a[i],b[i]++;
        }
    }sort(id+1,id+n+1,cmp);
    FOR(i,1,n){
        ans+=AA*b[id[i]];
        AA+=a[id[i]];
    }printf("%I64d\n",ans);
}
/*
*/
