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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a; }
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int A[maxn],B[maxn];
int mark[maxn];
vector<pair<int,int> > ans;
int main() {
    int n,t,k,i,j;
    scanf("%d%d%d",&n,&t,&k);k=n-k-t;
    if (k<0) return 0*puts("-1");
    FOR(i,1,t) scanf("%d",&A[i]);
    A[0]=B[0]=1;
    FOR(i,1,n) mark[i]=1;mark[1]=0;
    FOR(i,1,t) B[i]=B[i-1]+A[i-1],mark[B[i]]=0;//start
//    printf("k=%d\n",k);
    FOR(i,1,t){
        REP(j,A[i]){
            if (k){
                int fa=min(j+B[i-1],B[i]-1);
//                printf("fa=%d; f=%d",fa,j+B[i-1]);
                k-=mark[fa]; mark[fa]=0;
                ans.push_back(make_pair(j+B[i],fa));
            }else{
                ans.push_back(make_pair(j+B[i],B[i-1]));
            }
        }
    }if (k) return 0*puts("-1");
    printf("%d\n",n);
    for (auto now:ans) printf("%d %d\n",now.second,now.first);
    return 0;
}
/*
8 8
1 3 5 7 9 11 13 15
*/
