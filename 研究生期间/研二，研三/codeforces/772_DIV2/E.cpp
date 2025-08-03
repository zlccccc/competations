#include <bits/stdc++.h>
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
const LL M=998244353;
const LL maxn=1e6+107;

int n;
inline int lowbit(int x) {return x&-x;}
ll sum[maxn];
void add_(int x,ll value) {
    for (;x<=n;x+=lowbit(x)) sum[x]+=value;
}
void add_(int l,int r,ll value) {
    add_(l,value); add_(r+1,-value);
}
ll que_(int x) {
    ll ret=0;
    for (;x;x-=lowbit(x)) ret+=sum[x];
    return ret;
}
set<pair<pii,int> > POS;
ll VAL[maxn];
void UPD(int col,int l,int r,int action) {//action=1: add; action=-1: remove
    // printf("UPD col=%d %d->%d; action=%d\n",col,l,r,action);
    add_(l,r,-VAL[col]*action);
}
void update(int l,int r,int x){
    auto final=make_pair(make_pair(l,r),x);
    while (l<=r){
        auto it=POS.upper_bound(make_pair(make_pair(l,INF),0)); it--;
        // printf("%d ",it->second);
        auto now=*it; POS.erase(it);
        // printf("%d %d %d\n",now.first.first,now.first.second,now.second);
        int nxtl=now.first.second+1;
        if (now.first.first<l){
            pair<int,int> remain;
            remain.first=now.first.first;
            remain.second=l-1;
            if (remain.first<=remain.second)
                POS.insert(make_pair(remain,now.second));
        }
        if (now.first.second>r){
            pair<int,int> remain;
            remain.first=r+1;
            remain.second=now.first.second;
            if (remain.first<=remain.second)
                POS.insert(make_pair(remain,now.second));
            nxtl=r+1;
        }
        UPD(now.second,l,nxtl-1,-1); UPD(x,l,nxtl-1,1);
        l=nxtl;
    } POS.insert(final);
}
char op[10];
int main() {
    /*to solve the problem*/
    int q;
    scanf("%d%d",&n,&q);
    POS.insert(make_pair(make_pair(1,n),1));
    while (q--) {
        scanf("%s",op);
        if (op[0]=='C') {
            int l,r,c; scanf("%d%d%d",&l,&r,&c);
            update(l,r,c);
        } else if (op[0]=='A') {
            int c; ll v; scanf("%d%lld",&c,&v);
            VAL[c]+=v;
        } else {
            int p; scanf("%d",&p);
            auto it=POS.upper_bound(make_pair(make_pair(p,INF),0)); it--;
            auto now=*it;
            // printf("line %d %d %d\n",now.first.first,now.first.second,now.second);
            printf("%lld\n",VAL[now.second]+que_(p));
        }
    }
}
/*
2 7
Add 1 70000000000
Query 1
Add 2 4000000000
Query 2
Color 1 1 1
Add 1 1000000000
Query 2

*/