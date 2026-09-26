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
int ans;
int cnt[maxn],tot[maxn];
double A[maxn],B[255];
int main(){
    scanf("%s",a);
    n=strlen(a);
    REP(i,n) a[i+n]=a[i];
    FOR(i,1,n-1){
        int all=0;
        REP(j,800) tot[j]=cnt[j]=A[j]=0;
        REP(j,n){
            int ID=(a[j]-'a')*26+a[i+j]-'a';
            cnt[ID]++;tot[a[j]]++;
        }REP(j,n){
            int ID=(a[j]-'a')*26+a[i+j]-'a';
            if (cnt[ID]==1) A[a[j]]+=1.0/tot[a[j]];
        }REP(j,255) B[j]=max(B[j],A[j]);
    }double ans=0;
    REP(i,n) ans+=B[a[i]]/n;
    printf("%.15f\n",ans);
}
/*
*/
