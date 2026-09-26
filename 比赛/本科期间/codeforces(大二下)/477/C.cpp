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

queue<LL> p[maxn];
int n,m;
vector<LL> ans;
LL all;
int main() {
    int i,j;
    scanf("%d",&n);
    REP(j,n){
        LL x;
        scanf("%I64d",&x);
        all^=x;
        rREP(i,60) if ((x>>i)&1) {
            p[i].push(x); break;
        }
    }while (all){
        REP(i,60) if (((all>>i)&1)&&p[i].size()){
            LL x=p[i].front();p[i].pop();
//            printf("%I64d %I64d\n",all,x);
            ans.push_back(x);all^=x;
            break;
        }if (i==60) break;
    }
    if (ans.size()!=n) return 0*puts("No");
    puts("Yes");
    reverse(ans.begin(),ans.end());
    for (auto now:ans) printf("%I64d ",now);
    return 0;
}
/*
*/
