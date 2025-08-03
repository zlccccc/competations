#include <cstdio>
#include <cstring>
char s[100001];
int ed[26];
int ans[26];
int main()
{
    int len,anss;
    scanf("%s",s);
    len=strlen(s);
    for(int i=0;i<26;i++)
        ed[i]=-1;
    for(int i=0;i<len;i++)
    {
        if(i-ed[s[i]-'a']>ans[s[i]-'a'])
            ans[s[i]-'a']=i-ed[s[i]-'a'];
        ed[s[i]-'a']=i;
    }
    for(int i=0;i<26;i++)
        if(len-ed[i]>ans[i])
            ans[i]=len-ed[i];
    anss=0x7fffffff;
    for(int i=0;i<26;i++)
        if(ans[i]!=0&&ans[i]<anss)
            anss=ans[i];
    printf("%d\n",anss);
    return 0;
}
