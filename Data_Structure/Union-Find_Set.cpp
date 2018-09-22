/*并查集（带路径压缩）*/
const int maxn= " ";
int p[maxn];
void init(int n)
{
    for(int i=0; i<=n; i++)
        p[i]=i;
}
int Find(int x)
{
    if(x==p[x])
        return p[x];
    int y=Find(p[x]);
    return p[x]=y;
}

int Union(int x,int y)
{
    int x1=Find(x);
    int y1=Find(y);
    if(x1==y1)
        return 0;
    p[x1]=y1;
      return 1;
}

/* 带权并查集 */
const int maxn=" ";
int p[maxn],ran[maxn];
void init(int n)
{
    for(int i=0; i<=n; i++)
    {
        p[i]=i;
        ran[i]=0;//
    }
    return;
}
int Find(int x)
{
    if(x==p[x])
        return p[x];
    int y=Find(p[x]);
        ran[x]=(ran[x]+ran[p[x]])%3;//
    return p[x]=y;
}
int Union(int x,int y,int typ)
{
    int x1=Find(x);
    int y1=Find(y);
    if(x1==y1)
    {
        if((ran[x]-ran[y]+3)%3==typ-1)//
            return 0;
        return 1;
    }
    p[x1]=y1;
    ran[x1]=(-ran[x]+typ-1+ran[y]+3)%3;//
    return 0;
}
