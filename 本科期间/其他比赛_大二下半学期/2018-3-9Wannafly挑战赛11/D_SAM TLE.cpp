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
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//�����len������ֱ��ʹ��~ ԭ���������lenָ����ԭ��len
//fail����,len�ǿ���ֱ��ʹ�õ�~ (��fail��ȷ���Ľڵ���)
//���fail�ĺ�����˵��׺��ͬ,��ǰ��չ��val(һ��һ����չlen����)
//sam����Ϊ������!ע���Լ�������������
//����ʱע��len������!(��Ϊ����ʱ���ܸ���û�п���ǰ׺len)
//ע��nq�ڸ���ʱ����ʱval��q����ȵ�,Ҳ����˵,ά��ֵʱnqҪ��ȫ��qһ��
//sum{len[x]-len[fail[x]]}=��ͬ������,ÿ��������fail->this��len
//ÿ������λ�ý�����ʱ��ͱ�������~ Ҫ�����е��鷳��
//���Ƴ���������ڵ��ڼ������ʱ���������~
//Ҳ����˵������ͬ������ʱ,���Ƴ�����ֻ�Ǹ�����Ľڵ�
//queryʱ��ĩβ�Ӹ�0����ȥ���ܶ���ж�!
//�ӿ��ַ�ʱע��len,���len����������:����topo�Ŵ�,����add����
//�ӵĲ���root,���Ǹ����ַ�,dfs�Ļ�ֻ��dfsһ����!�Ӻ���ǰ���ƿ���
//�������һ�����Ͻ�,��ôֱ�Ӽ�������len���Ǵ��!һ��ע��!


struct linknode{
    struct node{
        int key,val;int next;
        node(){};
        node(int k,int v,int n):key(k),val(v),next(n){};
    }T[maxn];//���õؿռ�ֲ���?(��)
    int head[maxn],size;
    void clear(){
        memset(head,-1,sizeof(head));
        size=0;
    }
    int get(int x,int y){
        for (int i=head[x];~i;i=T[i].next)
            if (T[i].key==y) return T[i].val;
        return -2;
    }
    void insert(int pos,int key,int val){
        T[size]=node(key,val,head[pos]);
        head[pos]=size++;
    }
};

struct SAM{
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    void init(){
        int i;
        cnt=last=0;fail[0]=-1;len[0]=0;
        nextfail.clear();
    }
    void add(int c){
        int np=++cnt,p=last;
        len[np]=len[p]+1;
        for (;p!=-1&&!next[p][c];p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else{
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q];
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        last=np;
    }
    int S[maxn],Q[maxn];
    linknode nextfail;
    int query(char a[],int n,int N){
        int i,j;LL ret=0;
        int p=0,l=0;
        REP(i,N){
            int c=a[i]-'a';
            if (next[p][c]) l++,p=next[p][c];
            else {
                int nxt=nextfail.get(p,c);
                if (nxt!=-2) p=nxt;
                else{
                    int pre=p;
                    while (p!=-1&&!next[p][c]) p=fail[p];
                    nextfail.insert(pre,c,p);
                }
                if (p==-1) p=l=0;
                else l=len[p]+1,p=next[p][c];
            }if (l>=n) ret++;
        }return ret;
    }
    void print(){
        int i;
        FOR(i,1,cnt) {
        }
    }
    char a[maxn];
    void dfs(int x=0,int len=0){
        int i;
        printf("%-3d(fail:%-3d,len=%-2d):%s\n",x,fail[x],this->len[x],a);
        REP(i,26){
            if (next[x][i]){
                a[len]=i+'a';
                dfs(next[x][i],len+1);
                a[len]=0;
            }
        }
    }
}sam;
int n,m,T;
int i,j,k;
char *a,*b;
char buffer[36000000],*buf=buffer;
void read(int &x){
    for(x=0;*buf<48;++buf);
    while(*buf>=48)x=x*10+*buf-48,++buf;
}
char* getstart(){
    for (;*buf<'a';++buf);
    return buf;
}
int main(){
    fread(buffer,1,36000000,stdin);
    a=getstart();
    for(;*buf>='a';++buf);
//    printf("a=%s",a);
    n=buf-a;sam.init();
    REP(i,n) sam.add(a[i]-'a');
    REP(i,n) sam.add(a[i]-'a');
    read(m);
    REP(i,m){
        b=getstart();
        for(;*buf>='a';++buf);*buf=0;
//        printf("b=%s",b);
        if (buf-b<n) puts("0");
        else printf("%d\n",sam.query(b,n,buf-b));
    }
    return 0;
}
/*
*/
