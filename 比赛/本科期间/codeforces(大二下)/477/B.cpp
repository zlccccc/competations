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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=6e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,x1,x2;
pair<int,int> A[maxn];
int s1;
int main() {
    int i,j;
    scanf("%d%d%d",&n,&x1,&x2);
    REP(i,n) scanf("%d",&A[i].first),A[i].second=i+1;
    sort(A,A+n);
    s1=n-1;
    while (s1&&(x1+(n-s1)-1)/(n-s1)>A[s1].first) s1--;
//    printf("s1=%d\n",s1);
    FOR(i,1,n){
        int s2=lower_bound(A,A+n,make_pair((x2+i-1)/i,0))-A;
        if (s2+i<=s1){
            puts("Yes");
            printf("%d %d\n",n-s1,i);
            rep(j,s1,n) printf("%d ",A[j].second);puts("");
            rep(j,s2,s2+i) printf("%d ",A[j].second);puts("");
            return 0;
        }
    }swap(x1,x2);
    s1=n-1;
    while (s1&&(x1+(n-s1)-1)/(n-s1)>A[s1].first) s1--;
    FOR(i,1,n){
        int s2=lower_bound(A,A+n,make_pair((x2+i-1)/i,0))-A;
        if (s2+i<=s1){
            puts("Yes");
            printf("%d %d\n",i,n-s1);
            rep(j,s2,s2+i) printf("%d ",A[j].second);puts("");
            rep(j,s1,n) printf("%d ",A[j].second);puts("");
            return 0;
        }
    }
    puts("No");
    return 0;
}
/*
*/
