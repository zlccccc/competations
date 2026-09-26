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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k;
bool mark[maxn];
int check(int i){
    int cnt=0,j=0,k=1;
    while (i){
        j=j+i%10*k;i/=10;k*=10;
        if (i<=j&&mark[i*j]) cnt++;
    }if (cnt>=2) return 1;
    return 0;
}
int main(){
    FOR(i,1,1000) mark[i*i]=1;
    FOR(i,1,100000) if (check(i)) printf("%d\n",i);
    scanf("%d",&n);
    if (n<=3) puts("-1");
    else{
        if (n%2==0){
            n-=4;
            printf("1625");
            REP(i,n) printf("0");
        }else{
            n-=5;
            printf("41369");
            REP(i,n) printf("0");
        }puts("");
    }
}
/*
这个spj是不是写挂了...
*/
