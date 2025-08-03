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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

struct node{
	char *A,*B;
	int lenA,lenB;
}A[maxn];
int T;
int n,m;
char buffer[3000007],*buf=buffer;
int equal(char A[],int lenA,char B[],int lenB){
	int i;
	for(i=0;i<min(lenA,lenB);i++)
		if (A[i]!=B[i]) return A[i]<B[i]?-1:1;
	if (lenA!=lenB) return lenA<lenB?-1:1;
	return 0;
}
bool cmp(node &A,node &B){
	int t=equal(A.B,A.lenB,B.B,B.lenB);
	if (t==0) return equal(A.A,A.lenA,B.A,B.lenA)<0;
	return t>0;
}
bool cmpp(int i,int j){
	return cmp(A[i],A[j]);
}
void read(int &x){
	for(x=0;*buf<48;++buf);
	while(*buf>=48)x=x*10+*buf-48,++buf;
}
inline void read(char *&A,int &len){
	while (*buf=='\n'||*buf==' '||*buf=='\r') buf++;
	A=buf;
	// printf("%d : %d %c\n",buf-buffer,*buf,*buf);
	while (*buf!='\n'&&*buf!=' '&&*buf!='\r') buf++;
	len=buf-A;while (A[1]=='.'&&A[len-1]=='0') len--;
	*buf=0;buf++;
}
char write[7000000],*ed=write;
inline void print(char *A){
	while (*A!=0) *ed++=*A,A++;
}
int id[maxn];
int main() {
	int i;
	fread(buffer,1,3000000,stdin);
	read(n);
	REP(i,n) read(A[i].A,A[i].lenA),read(A[i].B,A[i].lenB);
	REP(i,n) id[i]=i;
	stable_sort(id,id+n,cmpp);
	REP(i,n) {
		print(A[id[i]].A);
		*ed++=' ';
		print(A[id[i]].B);
		*ed++='\n';
		// printf("%s %s\n",A[id[i]].A,A[id[i]].B);
	}
    fwrite(write,1,ed-write,stdout);
	return 0;
}
/*
*/
