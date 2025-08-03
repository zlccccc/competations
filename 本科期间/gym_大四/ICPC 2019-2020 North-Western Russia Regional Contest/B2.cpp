#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int>pii;
#define pb push_back
#define rank rankk
#define mp make_pair
const int MAX=4e5+5;
 
int n,k,anp;
char a[MAX];
int lcp[MAX],sa[MAX],fa[MAX],val[MAX],cnt[MAX],LCP[MAX];
vector<pii>v;
pii an;
set<int>s[MAX];
int tmp[MAX];
 
 
 
 
const int MAXN=800010;
int t1[MAXN],t2[MAXN],c[MAXN];//��SA������Ҫ���м����������Ҫ��ֵ
//��������ַ�������s�����У���s[0]��s[n-1],����Ϊn,�����ֵС��m,
//��s[n-1]�������s[i]������0��r[n-1]=0 ������ԭ�����һ��0 ԭ����ֵ����[1,m)���� ������һ���ѼӲ������Լ��ģ�
//���������Ժ�������sa������
bool cmp(int *r,int a,int b,int l)
{
    return r[a] == r[b] && r[a+l] == r[b+l];
}
void da(int str[],int sa[],int rank[],int height[],int n,int m)
{
    str[n++]=0;
    int i, j, p, *x = t1, *y = t2;
    //��һ�ֻ����������s�����ֵ�ܴ󣬿ɸ�Ϊ��������
    for(i = 0;i < m;i++)c[i] = 0;
    for(i = 0;i < n;i++)c[x[i] = str[i]]++;
    for(i = 1;i < m;i++)c[i] += c[i-1];
    for(i = n-1;i >= 0;i--)sa[--c[x[i]]] = i;
    for(j = 1;j <= n; j <<= 1)
    {
        p = 0;
        //ֱ������sa��������ڶ��ؼ���
        for(i = n-j; i < n; i++)y[p++] = i;//�����j�����ڶ��ؼ���Ϊ�յ���С
        for(i = 0; i < n; i++)if(sa[i] >= j)y[p++] = sa[i] - j;
        //��������y����ľ��ǰ��յڶ��ؼ�������Ľ��
        //���������һ�ؼ���
        for(i = 0; i < m; i++)c[i] = 0;
        for(i = 0; i < n; i++)c[x[y[i]]]++;
        for(i = 1; i < m;i++)c[i] += c[i-1];
        for(i = n-1; i >= 0;i--)sa[--c[x[y[i]]]] = y[i];
        swap(x,y);
        //����sa��x��������µ�x���� swap(x,y);
        p = 1; x[sa[0]] = 0;
        for(i = 1;i < n;i++)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if(p >= n)break;
        m = p;//�´λ�����������ֵ
    }
    int k = 0; n--;
    for(i = 0;i <= n;i++)rank[sa[i]] = i;
    for(i = 0;i < n;i++)
    {
        if(k)k--;
        j = sa[rank[i]-1]; while(str[i+k] == str[j+k])k++; height[rank[i]] = k;
    }
}
int rank[MAXN],height[MAXN];
 
 
 
inline int find(int x){printf("find %d\n",x);if(x==fa[x])return x;return fa[x]=find(fa[x]);}
inline void unite(int x,int y,int z){
    x=find(x+1)-1;y=find(y+1)-1;
    if(x!=y){
        if(cnt[x]>cnt[y])swap(x,y);
        LCP[y]=min(LCP[y],z);
        LCP[y]=min(LCP[y],LCP[x]);
        fa[x]=y;val[y]=min(val[y],val[x]);
        cnt[y]+=cnt[x];
        for(int u:s[x]){
            set<int>::iterator lo=s[y].lower_bound(u);///>=
            if(lo!=s[y].end())val[y]=min(val[y],(*lo)-u);
            if(lo==s[y].begin())continue;
            --lo;
            val[y]=min(val[y],u-(*lo));
        }
        for(int u:s[x]){s[y].insert(u);}
        s[x].clear();
    }
}
char ss[MAX];
int sss[MAX];
int main(){
//    freopen("in.txt","r",stdin);
    scanf("%s",ss);n=strlen(ss);
    for(int i=0;i<n;i++)sss[i]=ss[i]-'a'+1;
    if(n==1){
        puts("1/1");return 0;
    }
    da(sss,sa,rank,lcp,n,28);
//    construct_sa(ss,sa);construct_lcp(ss,sa,lcp);
//    for(int i=n-10;i<=n;i++)printf("%3d ",i);
//    puts("");
//    for(int i=0;i<=n;i++)printf("%6d ",sa[i]);
//    puts("");
//    for(int i=0;i<=n;i++)printf("%6d ",lcp[i]);
//    puts("");
//    for(int i=0;i<=n;i++)printf("%6d ",rank[i]);
//    puts("");
   for (int i=0;i<=n;i++) printf("%6d %6d %s\n",lcp[i],sa[i],ss+sa[i]);
//    printf("%d!!",lcp[0]);
    for(int i=1;i<=n+1;i++) fa[i]=i,val[i]=n+2,cnt[i]=1,LCP[i]=MAX;
    for(int i=1;i<=n;i++) v.pb(mp(lcp[i],i));
    for (int i=0;i<=n;i++) s[i].insert(i);
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    bool flag=0;
    for(pii tem:v){
        int h=tem.first,pr=tem.second;
//        if(rank[pr]==0)continue;
        int pl=sa[rank[pr]-1];
        printf("h=%d pl=%d pr=%d\n",h,pl,pr);
        unite(pl,pr,h);
        int id=find(pl+1)-1;
        int L=LCP[id],len=val[id];
        // printf("id=%d")
        if(!flag||1LL*(L+len)*an.second>1LL*an.first*len){
            int P=L+len,Q=len,GCD=__gcd(P,Q);P/=GCD;Q/=GCD;
            an=mp(P,Q);
            flag=1;
        }
    }
    printf("%d/%d\n",an.first,an.second);
}
/*
aaaaaa
aaaaaaaaaaaa
 
*/