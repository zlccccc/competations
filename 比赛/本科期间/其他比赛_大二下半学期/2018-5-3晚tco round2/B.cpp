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

class StablePairsDiv1{
public:
    vector <int> findMaxStablePairs(int n, int c, int k){
        vector<int> ret;
        if (n>1&&k==1) return {n-1,n};
        if (n==1||c<4) return ret;
        int i,f1,f2;
        f1=n;f2=n-1;
        REP(i,k){
            if (f1<1||f2<1) return vector<int>();
            ret.push_back(f1);ret.push_back(f2);
            f1-=c/2;f2-=c/2;
            if ((i&1)&&(c&1)) f1--;
            else if (c&1) f2--;
        }reverse(ret.begin(),ret.end());
        return ret;
    }
}test;
int main() {
    vector<int> t;
    t=test.findMaxStablePairs(2,100,3);
//    printf("%d ",t.size());
    for (int v:t) printf("%d ",v);
    return 0;
}
/*
*/
