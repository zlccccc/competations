#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <string>
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const int maxn=1e5+7;

int n,t;
double MIN[maxn<<2];
inline void update(int x,int pos,double val,int l,int r){
    MIN[x]=min(MIN[x],val);
    if (l==r) return;
    int mid=(l+r)/2;
    if (pos<=mid) update(x<<1,pos,val,l,mid);
    else update(x<<1|1,pos,val,mid+1,r);
}
inline double query(int x,int l,int r,int L,int R){
    if (l<=L&&R<=r) return MIN[x];
    double ret=INF;int mid=(L+R)/2;
    if (l<=mid) ret=min(ret,query(x<<1,l,r,L,mid));
    if (mid<r) ret=min(ret,query(x<<1|1,l,r,mid+1,R));
    return ret;
}
struct node{
    int S,A,B;
};
vector<node> have[maxn];
bool check(double x){
    int i;
    FOR(i,1,t*4) MIN[i]=INF;
    update(1,1,0,1,t);
    FOR(i,1,t)
        for (auto &v:have[i]){
//            printf("upd:%d %lf\n",i+1,query(1,v.S,t,1,t)+v.A-v.B*x);
            update(1,i+1,query(1,v.S,t,1,t)+v.A-v.B*x,1,t);
        }
//    printf("%lf:%lf\n",x,query(1,t,t,1,t));
    return query(1,t,t,1,t)<=0;
}
int main(){
	int i,j,m,x,T;
	scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&t);
        FOR(i,1,t) have[i].clear();
        FOR(i,1,n){
            int T;node now;
            scanf("%d%d%d%d",&now.S,&T,&now.A,&now.B);
            have[T].emplace_back(now);
        }t++;
        double l=0,r=1000;
        while (r-l>0.0005){
            double mid=(l+r)/2;
            if (check(mid)) r=mid;
            else l=mid;
        }
        printf("%.3lf\n",(l+r)/2);
    }
	return 0;
}
/*
*/
