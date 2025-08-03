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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int T;
int n,m;
int i,j,k;
double a1,a2,a3,a5;
double A[2000];
int main(){
    A[0]=1;
    cin>>n>>a1>>a2>>a3>>a5;
    FOR(i,0,n){
        A[i+1]=max(A[i+1],A[i]*pow(1+a1,1));
        A[i+2]=max(A[i+2],A[i]*pow(1+a2,2));
        A[i+3]=max(A[i+3],A[i]*pow(1+a3,3));
        A[i+5]=max(A[i+5],A[i]*pow(1+a5,5));
    }
    cout<<fixed<<setprecision(5)<<A[n];
}
/*
*/
