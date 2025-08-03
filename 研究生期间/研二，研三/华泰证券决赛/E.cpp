#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(I,N) for (I=0;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
const int maxn=1e5+7;
const int M=1e9+7;
inline void add_(int &_x,int _y) {_x+=_y; if (_x>=M) _x-=M;}
typedef pair<int,int> pii;

int n;
inline int lowbit(int x) {return x&-x;}
int sum[maxn];
inline void update(int x,int val ){
    for (;x<=n;x+=lowbit(x)) sum[x]+=val;
}
inline int query(int x) {
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=sum[x];
    return ret;
}
// need: bfs序
vector<int> edge[maxn];
int id[maxn];
int opt[maxn],qry[maxn],fa[maxn];
int pos[maxn];
int main() {
    int i;
    scanf("%d",&n);
    int pid=0;
    FOR(i,1,n) {
        scanf("%d",&opt[i]);
        if (opt[i]==1) {
            scanf("%d",&fa[i]);
            qry[i]=++pid;
            pos[qry[i]]=i;
            edge[qry[fa[i]]].push_back(i);
        } else if (opt[i]==2) {
            scanf("%d%d",&qry[i],&fa[i]);
            pos[qry[i]]=i;
            edge[pos[fa[i]]].push_back(i);
        } else {
            scanf("%d",&qry[i]);
        }
    }
    int tot=0;
    queue<int> Q; Q.push(0);
    while (Q.size()) { // bfs序
        int x=Q.front(); Q.pop();
        id[x]=++tot;
        for (int v:edge[x]) Q.push(v);
    }
    FOR(i,1,n) printf("%d ",id[i]); puts("<- id");
    FOR(i,1,n) {
        if (opt[i]==1) {
            pos[qry[i]]=i;
            printf("update %d 1\n",id[pos[qry[i]]]);
            update(id[pos[qry[i]]],1);
        } else if (opt[i]==2) {
            printf("i=%d; del %d -1\n",i,id[pos[qry[i]]]);
            update(id[pos[qry[i]]],-1);
            pos[qry[i]]=i;
            printf("update %d 1\n",id[pos[qry[i]]]);
            update(id[pos[qry[i]]],1);
        } else {
            printf("query %d (%d)\n",pos[qry[i]],id[pos[qry[i]]]);
            printf("%d\n",query(id[pos[qry[i]]]));
        }
    }
}
/*
9
1 0
1 1
1 2
1 3
3 4
2 3 1
3 4
2 3 2
3 4
*/ 