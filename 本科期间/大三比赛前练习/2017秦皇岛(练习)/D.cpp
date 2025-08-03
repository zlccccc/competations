#include <bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
using namespace std;
const int maxn=1e5+7;
vector<int> now[maxn];
set<int> edge[maxn];
void merge(vector<int> &A,vector<int> &B){
    if (A.size()<B.size()) swap(A,B);
    for (auto now:B) A.push_back(now);
    vector<int>().swap(B);
}
int fa[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
vector<int> ans[maxn];
int d[maxn],id[maxn];
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,m,i;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) {//init
            fa[i]=i; d[i]=0;
            vector<int>().swap(now[i]);
            vector<int>().swap(ans[i]);
            now[i].push_back(i);
            edge[i].clear();
        }
        FOR(i,1,m){
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].insert(v);
            edge[v].insert(u);
            d[u]++; d[v]++;
        } FOR(i,1,n) id[i]=i;
        sort(id+1,id+1+n,[&](int i,int j){
            return d[i]<d[j];
        });
        bool okay=1;
//        puts("??1");
        FOR(i,1,n) {
            int x=id[i]; d[x]=0;
            while (edge[x].size()){
                int y=*edge[x].begin();
                if (d[y]) {
                    edge[x].erase(y);
                    continue;
                }//after
//                printf("%d->%d\n",x,y);
                int fy=getfa(y),fx=getfa(x);
                ans[x].push_back(y);
                for (int v:now[fy]){
                    auto it=edge[x].find(v);
                    if (it==edge[x].end()) okay=0;
                    else edge[x].erase(it);
                }
                fa[fx]=fy; merge(now[fy],now[fx]);
//                printf("fa[%d] - %d\n",x,y);
            }
        }
        if (!okay) puts("No");
        else {
            puts("Yes");
            FOR(i,1,n){
                int x=id[i];
                printf("%d ",x);
                printf("%d",(int)ans[x].size());
                for (auto now:ans[x]) printf(" %d",now);
                puts("");
            }
        }
//        puts("??");
    }
    return 0;
}
/*
3
3 0

4 4
1 2
2 3
3 4
2 4

5 5
1 2
2 3
3 4
4 5
2 4
*/
