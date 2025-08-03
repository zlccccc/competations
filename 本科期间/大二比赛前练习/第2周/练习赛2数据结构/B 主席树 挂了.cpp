#include <cstdio>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

const LL MAX=5000007;
struct node{
	int l,r,min;//无区间查询，不用中间lazy 
}T[MAX];
int cnt;
void build(int &x,int l,int r){
	if (!x) x=++cnt;T[x].min=INF;
	if (l==r) return;
	int mid=(l+r)/2;
	build(T[x].l,l,mid);
	build(T[x].r,mid+1,r);
}
void pushdown(int x){
	T[T[x].l].min=min(T[T[x].l].min,T[x].min);
	T[T[x].r].min=min(T[T[x].r].min,T[x].min);
}
void update(int &x,int y,int val,int l,int r,int L,int R){
//	if (cnt==MAX) cnt=0;//等会加吧。。
//	if (T[y].min<=val) {x=y;return;}//剪枝 
//	printf("update: %d %d %d %d %d %d %d\n",x,y,val,l,r,L,R);
	T[++cnt]=T[y];x=cnt;
	if (l<=L&&R<=r) {T[x].min=min(T[x].min,val);return;}
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=l) update(T[x].l,T[y].l,val,l,r,L,mid);
	if (r>mid) update(T[x].r,T[y].r,val,l,r,mid+1,R);
}
int query(int x,int pos,int l,int r){
//	printf("query: %d %d %d %d\n",x,pos,l,r);
	if (l==r) return T[x].min;
	int mid=(l+r)/2;
	pushdown(x);
	if (mid>=pos) return query(T[x].l,pos,l,mid);
	return query(T[x].r,pos,mid+1,r);
}
int n,m;
int i;
char a[5];
int S[maxn],pos;
int l,r,val;
int main()
{
	freopen("invazia.in","r",stdin);
	freopen("invazia.out","w",stdout);
	scanf("%d%d",&n,&m);
	build(S[0],1,n);
	pos=0;
	REP(i,m){
		scanf("%s",a);
		if (a[0]=='I'){
			scanf("%d%d%d",&l,&r,&val);
			pos++;
			update(S[pos],S[pos-1],val,l,r,1,n);
		}else if (a[0]=='E') pos--;
		else if (a[0]=='R'){
			scanf("%d",&l);
			int t=query(S[pos],l,1,n);
			if (t==INF) puts("GUITZZZ!");
			else printf("%d\n",t);
		}
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
/*
*/
