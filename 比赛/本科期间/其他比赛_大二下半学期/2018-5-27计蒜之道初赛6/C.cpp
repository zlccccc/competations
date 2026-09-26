#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
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

char buffer[36000000],*buf=buffer;
void read(int &x){
    for(x=0;*buf<48;++buf);
    while(*buf>=48)x=x*10+*buf-48,++buf;
}
int n,m;
int A[maxn];
int L[maxn],R[maxn],H[maxn];//H:higher
set<pair<int,int> > Q;
set<int> remain;
set<int>::iterator it;
int T;
void solve(){
    int i,j,_k,n,m,k;
    m=0;
    read(n);read(_k);
    FOR(i,1,n) read(A[i]);
    int MIN=0;
    FOR(i,1,n){
        if (A[i-1]<=A[i]&&A[i]>A[i+1]){
            L[++m]=MIN;
            H[m]=A[i];
            MIN=INF*2;
        }MIN=min(MIN,A[i]);
    }k=m;MIN=0;
    rFOR(i,1,n){
        if (A[i-1]<=A[i]&&A[i]>A[i+1]){
            R[m--]=MIN;
            MIN=INF*2;
        }MIN=min(MIN,A[i]);
    }n=k;H[0]=H[n+1]=INF*2;
    LL ans=0;
    Q.clear();remain.clear();
    FOR(i,0,n+1) Q.insert(make_pair(H[i]-max(L[i],R[i]),i)),remain.insert(i);
//    FOR(i,0,n+1) printf("%d - %d %d  %d %d\n",H[i],L[i],R[i],Q.size(),_k);
    while (Q.size()>_k+2){
        auto now=*Q.begin();
        Q.erase(now);
        it=lower_bound(remain.begin(),remain.end(),now.second);
        ans+=now.first;
        it--;int _L=*it;
        it++;it++;int _R=*it;
//        printf("%d %d %d\n",now.first,_L,_R);
        Q.erase(make_pair(H[_L]-max(L[_L],R[_L]),_L));
        Q.erase(make_pair(H[_R]-max(L[_R],R[_R]),_R));
        R[_L]=min(R[_L],R[now.second]);
        L[_R]=min(L[_R],L[now.second]);
        Q.insert(make_pair(H[_L]-max(L[_L],R[_L]),_L));
        Q.insert(make_pair(H[_R]-max(L[_R],R[_R]),_R));
        remain.erase(now.second);
    }
    printf("%lld\n",ans);
}
int main() {
    int i,j;
    fread(buffer,1,36000000,stdin);
    read(T);
    while(T--) solve();
    return 0;
}
/*
10
5 0
1 3 1 2 1
0 2
5 1
1 3 1 2 1
0 0
0 1
5 2
1 3 1 2 1
*/
