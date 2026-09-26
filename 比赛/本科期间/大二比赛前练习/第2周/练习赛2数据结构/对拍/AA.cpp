#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e4+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
//暴力动态开点主席树 
int lastAC[maxn];
struct f{
	bool operator()(const int &x,const int &y)const{
		if (lastAC[x]==INF&&lastAC[y]==INF) return x<y;
		return lastAC[x]<lastAC[y];
	} 
};
struct node{
	set<int> val;
	int num;
	int l,r,last;
	node(){l=r=0;set<int>().swap(val);}
}T[maxn*50];
const int MID=1000000,MAX=1500000;
int cnt;
void pushup(int x){
	T[x].num=T[T[x].l].num+T[T[x].r].num;
}
void update(int &x,int l,int r,int pos,int val,int k){//ins==1:ins,-1:erase
	if (x==0) x=++cnt;
	if (l==r){
//		printf("presize:%d  %d\n",T[x].val.size(),val);
//		for(set<int>::iterator it=T[x].val.begin();it!=T[x].val.end();it++) printf("%d ",*it);puts(""); 
		if (k==1) T[x].val.insert(val);
		else T[x].val.erase(val);
//		for(set<int,f>::iterator it=T[x].val.begin();it!=T[x].val.end();it++) printf("%d ",*it);puts(""); 
//		printf("OKsize:%d:\n",T[x].val.size());
		T[x].num=T[x].val.size();
		return;
	}
	int mid=(l+r)/2;
	if (mid>=pos) update(T[x].l,l,mid,pos,val,k);
	else update(T[x].r,mid+1,r,pos,val,k);
	pushup(x);
	printf("%d %d->%d  %d %d %d  num=%d\n",x,l,r,pos,val,k,T[x].num);
}
int querysum(int x,int l,int r,int L,int R){
//	printf("Q SUM: %d %d->%d  %d %d   num=%d\n",x,l,r,L,R,T[x].num);
	if (x==0) return 0;
	if (l<=L&&R<=r) return T[x].num;
	int ret=0,mid=(L+R)/2;
	if (mid>=l) ret+=querysum(T[x].l,l,r,L,mid);
	if (r>mid) ret+=querysum(T[x].r,l,r,mid+1,R);
	return ret;
}
int querykth(int x,int l,int r,int k){
	if (l==r){
		if (k==1) return *T[x].val.begin();
		return -1;
	}
	int mid=(l+r)/2;
	if (T[T[x].l].num>=k) return querykth(T[x].l,l,mid,k);
	else return querykth(T[x].r,mid+1,r,k-T[T[x].l].num);
}
int n,m,k;
int i,j;
int time[maxn][17];//== -1 -> AC
int last[maxn];
int alltime[maxn];
char a[maxn];
int root;
int main()
{
	while (~scanf("%d%d",&n,&m)){
		cnt=0;root=0;
		REP(i,n) lastAC[i]=INF,alltime[i]=0,last[i]=-INF;
		REP(i,n) REP(j,m) time[i][j]=0;
		REP(i,n) update(root,1,MAX,MID,i,1);
		REP(i,n) printf("Update:%d [%d] %d\n",MID,i,1);
		while (~scanf("%s",a)){
			if (a[0]=='C'){
				scanf("%s",a);
				break;
			}else if (a[0]=='S'){
				int minute,no,res;
				char id;
				scanf("%d:%d:%c:%d",&minute,&no,&id,&res);
				id-='A';
//				printf("--%d:%d:%c:%d--\n",minute,no,id+'A',res);
				if (time[no][id]==-1||minute-last[no]<5) continue;
				last[no]=minute;
				if (res==0){
					time[no][id]+=20;
				}else{
					printf("[%d][%c]\n",no,id+'A');
					update(root,1,MAX,alltime[no]+MID,no,-1);
					printf("Update:%d [%d] %d\n",alltime[no]+MID,no,-1);
					alltime[no]+=time[no][id]+minute-100000;
					update(root,1,MAX,alltime[no]+MID,no,1);
					printf("Update:%d [%d] %d\n",alltime[no]+MID,no,1);
					time[no][id]=-1;
					lastAC[no]=minute;
				}
			}else if (a[0]=='R'){
				scanf("%d",&k);
				printf("%d\n",querysum(root,1,alltime[k]+MID-1,1,MAX)+1);
				printf("Q : %d->%d\n",1,alltime[k]+MID-1);
			}else if (a[0]=='T'){
				scanf("%d",&k);
				printf("%d\n",querykth(root,1,MAX,k));
			}
		}
		FOR(i,1,cnt) T[i]=node();
		puts("");
	}
	return 0;
}
/*
10 10
S 3:0:I:1
S 9:7:C:1
S 13:9:J:1
S 13:1:F:1
S 20:8:B:1
S 34:8:J:1
S 38:2:I:1
S 42:4:B:1
R 2
S 46:1:J:1
R 2
R 7
*/
