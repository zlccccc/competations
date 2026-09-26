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
bool f[maxn];
int n;
int c[2],b[2];
int main() {
    int i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    int ans=0;
    FOR(i,1,n) {
        if (!f[i]&&((A[i]^i)&1)) {
            if (A[i]==i) continue;
            c[0]=c[1]=0;
            for (int v=i;!f[v];v=A[v])  f[v]=1,c[A[v]%2]++;
            ans+=c[0]+c[1]-1;
        }
    }
    FOR(i,1,n) {
        if (!f[i]) {
            if (A[i]==i) continue;
            c[0]=c[1]=0;
            for (int v=i;!f[v];v=A[v])  f[v]=1,c[A[v]%2]++;
            ans+=c[0]+c[1];
            if (c[0]&&!c[1]) b[0]++;
            if (!c[0]&&c[1]) b[1]++;
        }
    }
    ans+=abs(b[0]-b[1]);
    printf("%d\n",ans);
}
/*
3
3 2 1

4
3 4 1 2
*/ 