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
#include <bitset>
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
char a[10][maxn];
int main(){
    scanf("%d",&n);
    REP(i,9) scanf("%s",a[i]);
    REP(i,n){
        if (a[0][i]=='|') {putchar('|');continue;}
        if (a[0][i]=='o') {putchar('F');continue;}
        if (a[1][i]=='o') {putchar('E');continue;}
        if (a[2][i]=='o') {putchar('D');continue;}
        if (a[3][i]=='o') {putchar('C');continue;}
        if (a[4][i]=='o') {putchar('B');continue;}
        if (a[5][i]=='o') {putchar('A');continue;}
        if (a[6][i]=='o') {putchar('G');continue;}
        if (a[7][i]=='o') {putchar('F');continue;}
        if (a[8][i]=='o') {putchar('E');continue;}
        if (a[9][i]=='o') {putchar('D');continue;}
    }
}
/*
*/
