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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
struct LCT{
	struct node{
		int son[2],val,size;
		LL sum,add;//max
		bool rev;
		void init(int _val){
			son[0]=son[1]=rev=add=0;
			sum=val=_val;
			size=1;
		}
	}T[maxn];
	bool root[maxn];
	int fa[maxn];
	void Reverse(int x){
		T[x].rev^=1;
		swap(T[x].son[0],T[x].son[1]);
	}
	void Add(int x,int val){
		T[x].add+=val;
		T[x].val+=val;
		T[x].sum+=1ll*T[x].size*val;
	}
	void pushup(int x){
		T[x].size=1;
		T[x].sum=T[x].val;
		if (T[x].son[0]){
            Add(T[x].son[0],T[x].add);
            T[x].sum+=T[T[x].son[0]].sum;
			T[x].size+=T[T[x].son[0]].size;
		}
		if (T[x].son[1]){
            Add(T[x].son[1],T[x].add);
            T[x].sum+=T[T[x].son[1]].sum;
			T[x].size+=T[T[x].son[1]].size;
		}
		T[x].add=0;
	}
	void pushdown(int x){
		if (T[x].rev){
			if (T[x].son[0]) Reverse(T[x].son[0]);
			if (T[x].son[1]) Reverse(T[x].son[1]);
			T[x].rev=0;
		}
		if (T[x].add){
			if (T[x].son[0]) Add(T[x].son[0],T[x].add);
			if (T[x].son[1]) Add(T[x].son[1],T[x].add);
			T[x].add=0;
		}
	}
	void rotate(int x,int kind){
		int y=fa[x],z=fa[y];
		T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
		T[x].son[kind]=y,fa[y]=x;
		if (root[y]) {root[x]=true;root[y]=false;}
		else T[z].son[T[z].son[1]==y]=x;
		fa[x]=z;
		pushup(y);
	}
	void Prechange(int x){
		if (!root[x]) Prechange(fa[x]);
		pushdown(x);
	}
	void splay(int x){//to root
		Prechange(x);
		while (!root[x]){
			int y=fa[x],z=fa[y];
			int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
			if (root[y]) rotate(x,rx);
			else{
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		}
		pushup(x);
	}
	int access(int x){//只有这条链上的是mark的
		int y=0;
		for (;x;x=fa[x]){
			splay(x);
			root[T[x].son[1]]=true;
			T[x].son[1]=y;
			root[y]=false;
			y=x;
			pushup(x);
		}
		return y;
	}
	bool judge(int u,int v){
		while (fa[u]) u=fa[u];
		while (fa[v]) v=fa[v];
		return u==v;
	}
	void makeroot(int x){
		access(x);
		splay(x);
		Reverse(x);
	}
	bool add(int u,int v,int val){
		makeroot(u);
		access(v);
		splay(v);
		Add(v,val);
		return 0;
	}
	bool change(int u,int v,int val){
		makeroot(u);
		access(v);
		splay(v);
		Add(v,val);
		return 0;
	}
}T;
vector<int> edge[maxn];
void dfs(int x,int fa){
	T.fa[x]=fa;
	for (int v:edge[x]) if (v!=fa) dfs(v,x);
}
int root;
int n,m;
int a[maxn];
int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&a[i]);
    FOR(i,1,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }dfs(1,0,0);
    FOR(i,1,n) update(1,in[i],in[i],a[i],1,n);
//    FOR(i,1,n) printf("in,out= %d %d\n",in[i],out[i]);
    root=1;
    while (m--){
        int op,u,v,x;
        scanf("%d",&op);
        if (op==1){
            int root;
            scanf("%d",&root);
            T.makeroot(root);
        }else if (op==2){
            scanf("%d%d%d",&u,&v,&x);
            int f=lca(u,v)^lca(v,root)^lca(u,root);
            if (f==root) update(1,1,n,x,1,n);
            else if (lca(f,root)==f){
                int t=getnthfa(root,dep[root]-dep[f]-1);
                update(1,1,in[t]-1,x,1,n);
                update(1,out[t]+1,n,x,1,n);
            }else update(1,in[f],out[f],x,1,n);
        }else if (op==3){
            int x;
            scanf("%d",&x);

        }
    }
}
/*
*/
