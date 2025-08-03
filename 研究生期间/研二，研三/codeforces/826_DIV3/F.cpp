#include <sstream>
#include <fstream>
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

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

set<pair<int,int> > S;
vector<pair<pii,int> > P[maxn];
int dis(int l,int r,int L,int R) {
    if (l>L) swap(l,L),swap(r,R);
    if (L<=r) return 0;
    return L-r;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,i;
        scanf("%d",&n);
        vector<int> ans(n+1,INF);
        FOR(i,1,n) P[i].clear();
        FOR(i,1,n) {
            int l,r,c;
            scanf("%d%d%d",&l,&r,&c);
            P[c].push_back({{l,r},i});
        }
        S.clear();
        FOR(i,1,n) {
            for (auto now:P[i]) {
                int l=now.first.first,r=now.first.second,c=now.second;
                auto it=S.lower_bound({l,0});
                if (it!=S.end()) min_(ans[c],dis((*it).first,(*it).second,l,r));
                if (it!=S.begin()) it--,min_(ans[c],dis((*it).first,(*it).second,l,r));
            }
            for (auto now:P[i]) {
                int l=now.first.first,r=now.first.second,c=now.second;
                while(1) {
                    bool mark=0;
                    auto it=S.lower_bound({l,0});
                    if (it!=S.end()) {
                        auto p=*it;
                        int d=dis((*it).first,(*it).second,l,r);
                        if (d==0) {S.erase(it); l=min(p.first,l),r=max(p.second,r); mark=1;}
                    }
                    it=S.lower_bound({l,0});
                    if (it!=S.begin()) {
                        it--; auto p=*it;
                        int d=dis((*it).first,(*it).second,l,r);
                        if (d==0) {S.erase(it); l=min(p.first,l),r=max(p.second,r); mark=1;}
                    }
                    if (!mark) break;
                }
                S.insert({l,r});
            }
        }
        S.clear();
        rFOR(i,1,n) {
            for (auto now:P[i]) {
                int l=now.first.first,r=now.first.second,c=now.second;
                auto it=S.lower_bound({l,0});
                if (it!=S.end()) min_(ans[c],dis((*it).first,(*it).second,l,r));
                if (it!=S.begin()) it--,min_(ans[c],dis((*it).first,(*it).second,l,r));
            }
            for (auto now:P[i]) {
                int l=now.first.first,r=now.first.second,c=now.second;
                while(1) {
                    bool mark=0;
                    auto it=S.lower_bound({l,0});
                    if (it!=S.end()) {
                        auto p=*it;
                        int d=dis((*it).first,(*it).second,l,r);
                        if (d==0) {S.erase(it); l=min(p.first,l),r=max(p.second,r); mark=1;}
                    }
                    it=S.lower_bound({l,0});
                    if (it!=S.begin()) {
                        it--; auto p=*it;
                        int d=dis((*it).first,(*it).second,l,r);
                        if (d==0) {S.erase(it); l=min(p.first,l),r=max(p.second,r); mark=1;}
                    }
                    if (!mark) break;
                }
                S.insert({l,r});
            }
        }
        FOR(i,1,n) printf("%d ",ans[i]); puts("");
    }
}
/*
C(16,8)=12870 * n=1
10 8
5000 8
*/