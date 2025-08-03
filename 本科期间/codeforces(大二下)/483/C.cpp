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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5000+7;
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

inline int getstatus(vector<int> &V){
    int ret=0;
    sort(V.begin(),V.end());
    for (int v:V) ret=ret*10+v;
    return ret;
}inline vector<int> getvec(int x){
    vector<int> ret;
    for (;x;x/=10) ret.push_back(x%10);
    return ret;
}inline vector<int> update(vector<int> &ini,int l,int r){
    if (l>r) swap(l,r);
    vector<int> ret;
    for (int v:ini) if (v<l||v>r) ret.push_back(v);
    return ret;
}
int f[2007][10007];
int A[2007],p[2007];
int main() {
    int i,j,k,T;
    int n;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&p[i],&A[i]);
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;p[0]=1;
    FOR(k,1,n){
        int status;
        FOR(status,0,10000) if (f[k-1][status]!=INF){
//            printf("%d(%d) ",status,f[k-1][status]);
            vector<int> now=getvec(status);
            int con=0;
            FOR(i,1,10){
                con=abs(i-p[k-1])+abs(i-p[k]);
                vector<int> nxt=now;
                nxt=update(nxt,i,p[k-1]);
                nxt=update(nxt,i,p[k]);
                if (nxt.size()==4) continue;
                nxt.push_back(A[k]);
                int nxtstatus=getstatus(nxt);
                f[k][nxtstatus]=min(f[k][nxtstatus],f[k-1][status]+con);
            }
        }puts("");
    }int status,ans=INF;
//    puts("okay_1");
    FOR(status,0,10000) if (f[n][status]!=INF){
        vector<int> now=getvec(status);
        int MAX=0,MIN=10;
        for (int v:now) MIN=min(MIN,v),MAX=max(MAX,v);//must have
        int con=min(abs(p[n]-MAX),abs(p[n]-MIN))+MAX-MIN;
        ans=min(ans,con+f[n][status]);
    }ans+=n*2;
    printf("%d\n",ans);
}
/*
9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 1

*/
