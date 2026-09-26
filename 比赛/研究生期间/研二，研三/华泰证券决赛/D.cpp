#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(I,N) for (I=0;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
const int maxn=1e5+7;
const int M=1e9+7;
inline void add_(int &_x,int _y) {_x+=_y; if (_x>=M) _x-=M;}
typedef pair<int,int> pii;
pii MAX[maxn*4];
int A[maxn];
int n;
int op=0;
void build(int x,int l,int r) {
    // printf("build %d %d %d\n",x,l,r);
    if (!op) MAX[x]={A[l],l};
    else MAX[x]={-A[l],l};
    if (l==r) return;
    int mid=(l+r)/2;
    build(x<<1,l,mid); build(x<<1|1,mid+1,r);
    MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
}
inline pii query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return MAX[x];
    pii ret={-M,l}; int mid=(L+R)/2;
    if (l<=mid) ret=max(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=max(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
int ans;
void solve(int l,int r) {
    if (l>r) return;
    auto p=query(1,l,r,1,n);
    int v=p.first,x=p.second;
    if (op) v=-v;
    int now=v*((ll)(x-l+1)*(x+l)/2)%M*((ll)(r-x+1)*(2*n+2-r-x)/2)%M;
    // printf("solve %d %d: v=%d; x=%d; now=%d\n",l,r,v,x,now);
    if (!op) add_(ans,now);
    else add_(ans,M-now);
    solve(l,x-1); solve(x+1,r);
}
int main() {
    int i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    op=0; build(1,1,n); solve(1,n);
    op=1; build(1,1,n); solve(1,n);
    printf("%d\n",ans);
}
/*
3
1 4 2
*/ 