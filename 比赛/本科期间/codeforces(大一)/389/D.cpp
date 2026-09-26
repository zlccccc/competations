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
const LL maxn=1e5+7;
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

typedef pair<ULL,ULL> pii;
int k,n;
char A[maxn];
int MAX=0;LL ans;
map<pii,priority_queue<int> > MP;
vector<pii> Q;
int main() {
    int n,m,i,j,k;
    scanf("%d%d",&n,&k);
    while(n--){
        scanf("%s%d",A,&m);
        int len=strlen(A);
        assert(k==len);
        ULL p1=0,p2=0;
        REP(i,len) p1=(p1*347+A[i])%M;
        rREP(i,len) p2=(p2*347+A[i])%M;
        MP[make_pair(p1,p2)].push(m);
        Q.push_back(make_pair(p1,p2));
    }for (auto now:Q) {
        while (MP[now].size()){
            int nowmax=MP[now].top();
            MP[now].pop();
            swap(now.first,now.second);
            if (MP[now].size()){
                int nxtmax=MP[now].top();
                if (nxtmax+nowmax>0){
                    if (now.first==now.second){
                        MAX=max(MAX,-nowmax);
                        MAX=max(MAX,-nxtmax);
                    }ans+=nxtmax+nowmax;
                    MP[now].pop();
                }else {
                    if (now.first==now.second)
                        MAX=max(MAX,nowmax);
                    break;
                }
            }else {
                if (now.first==now.second)
                    MAX=max(MAX,nowmax);
                break;
            }
        }
    }printf("%I64d\n",MAX+ans);
//    printf("%d %I64d\n",MAX,ans);
    return 0;
}
/*
*/
