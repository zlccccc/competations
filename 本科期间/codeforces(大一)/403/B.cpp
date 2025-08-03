#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL N=1e6+7;
const double eps=1e-7;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

LL n,m;
double a[N],v[N];
LL i,j,k;
LL ans;
double l,r,mid;
bool judge(double x){
    double left,right;
    LL i;
    left=a[1]-v[1]*x;
    right=a[1]+v[1]*x;
    REP(i,n){
        if (left<a[i]-v[i]*x) left=a[i]-v[i]*x;
        if (right>a[i]+v[i]*x) right=a[i]+v[i]*x;
    }
    return right>left;
}
int main(){
	scanf("%I64d",&n);
	REP(i,n) scanf("%lf",&a[i]);
	REP(i,n) scanf("%lf",&v[i]);
    l=0;r=1e9;
//    while (abs(r-l)>eps)
    REP(i,100) {
        mid=(l+r)/2;
        if (judge(mid)) r=mid;
        else l=mid;
    }
    printf("%lf",l);
}
/*
*/
