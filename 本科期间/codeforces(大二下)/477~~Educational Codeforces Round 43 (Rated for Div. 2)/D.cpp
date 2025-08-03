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
const LL maxn=1e5+7;
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

typedef pair<int,int> pii;
int n;
int A[maxn],B[maxn];
vector<pii> ans;
int main() {
    int i,j,k;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    sort(A+1,A+1+n);
    FOR(i,1,n) B[i]=A[i];
    int s=1,t=A[n]+1;j=1;i=n;
    while (1){
        if (A[j]==0) {
            j++;i--;
            if (i<j) break;
            while (t-s>A[i]) s++;
        }
//        printf("%d %d %d %d, A[i]=%d\n",s,t,j,i,A[i]);
        FOR(k,s,t-1) ans.push_back(make_pair(k,t));
        FOR(k,j,i) A[k]--; t--;
    }printf("%d\n",(int)ans.size());
    for (auto now:ans) printf("%d %d\n",now.first,now.second);
    return 0;
}
/*
*/
