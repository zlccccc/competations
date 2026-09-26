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
const LL maxn=1e6+7;
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

int n,m;
vector<int> V;
struct node{
    int time,len;
}A[maxn],B[maxn];
bool cmp(node &A,node &B){
    return A.time<B.time;
}LL ans;
int main() {
    int i,j,k;
    int T,cnt=0;
    scanf("%d%d%d",&n,&m,&T);
    V.push_back(0);
    V.push_back(T);
    int a,b;
    FOR(i,1,n) scanf("%d%d",&A[i].time,&A[i].len),V.push_back(A[i].time);
    FOR(i,1,m) scanf("%d%d",&B[i].time,&B[i].len),V.push_back(B[i].time);
    sort(A+1,A+1+n,cmp);
    sort(B+1,B+1+m,cmp);
    A[n+1].time=B[m+1].time=T;
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    a=b=1;
    REP(i,V.size()-1){
        if (V[i]==T) break;
        while (A[a+1].time<=V[i]&&a+1<=n) a++;
        while (B[b+1].time<=V[i]&&b+1<=m) b++;
        ans+=(LL)max(0,max(A[a].len,B[b].len))*(V[i+1]-V[i]);
//        printf("%d-%d : %d(%d %d) %d(%d %d)\n",V[i],V[i+1],a,A[a].time,A[a].len,b,B[b].time,B[b].len);
    }printf("%lld\n",ans);
    return 0;
}
/*
2 2 5
2 3
0 2
0 3
3 1

3 4 17
8 3
0 10
9 10
7 15
0 6
16 9
14 8
*/
