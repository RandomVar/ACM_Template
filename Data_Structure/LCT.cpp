//维护点权
struct LCT
{
    int val[maxn],sum[maxn];
    int rev[maxn],ch[maxn][2],fa[maxn];
    int nxt[maxn];
    int stk[maxn];
    void init(int n)
    {
        for(int i=1;i<=n;i++)
            val[i]=1,fa[i]=0,rev[i]=0,ch[i][0]=ch[i][1]=0;
    }
    bool isroot(int x)
    {
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    bool get(int x)
    {
        return ch[fa[x]][1]==x;
    }
    void pushdown(int x)
    {
        if(!rev[x])
            return ;
        swap(ch[x][0],ch[x][1]);
        if(ch[x][0])
            rev[ch[x][0]]^=1;
        if(ch[x][1])
            rev[ch[x][1]]^=1;
        rev[x]^=1;
    }
    void pushup(int x)
    {
        sum[x]=val[x]+sum[ch[x][0]]+sum[ch[x][1]];
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[fa[x]],d=get(x);
        if(!isroot(y))
            ch[z][get(y)]=x;
        fa[x]=z;
        ch[y][d]=ch[x][d^1],fa[ch[y][d]]=y;
        ch[x][d^1]=y,fa[y]=x;
        pushup(y),pushup(x);
    }
    void splay(int x)
    {
        int top=0;
        stk[++top]=x;
        for(int i=x;!isroot(i);i=fa[i]) stk[++top]=fa[i];
        for(int i=top;i;i--) pushdown(stk[i]);
        for(int f;!isroot(x);rotate(x))
            if(!isroot(f=fa[x]))
                rotate(get(x)==get(f)?f:x);
    }
    void access(int x)
    {
        for(int y=0;x;y=x,x=fa[x])
        {
            splay(x);
            ch[x][1]=y;
            pushup(x);
        }
    }
    int find(int x)
    {
        access(x),splay(x);
        while(ch[x][0])
            x=ch[x][0];
        return x;
    }
    void makeroot(int x) {access(x),splay(x),rev[x]^=1;}
    void link(int x,int y){makeroot(x),fa[x]=y,splay(x);}
    void cut(int x,int y){makeroot(x),access(y),splay(y),fa[x]=ch[y][0]=0;}
    void update(int x,int v){val[x]=v,access(x),splay(x);}
    int query(int x,int y)
    {
        makeroot(y),access(x),splay(x);
        return sum[ch[x][0]];
    }
}lct;

//维护子树
#include <cstdio>
#include <algorithm>
#define N 100010
using namespace std;
int fa[N] , c[2][N] , si[N] , sum[N] , rev[N];
char str[5];
void pushup(int x)
{
    sum[x] = sum[c[0][x]] + sum[c[1][x]] + si[x] + 1;
}
void pushdown(int x)
{
    if(rev[x])
    {
        int l = c[0][x] , r = c[1][x];
        swap(c[0][l] , c[1][l]) , swap(c[0][r] , c[1][r]);
        rev[l] ^= 1 , rev[r] ^= 1 , rev[x] = 0;
    }
}
bool isroot(int x)
{
    return c[0][fa[x]] != x && c[1][fa[x]] != x;
}
void update(int x)
{
    if(!isroot(x)) update(fa[x]);
    pushdown(x);
}
void rotate(int x)
{
    int y = fa[x] , z = fa[y] , l = (c[1][y] == x) , r = l ^ 1;
    if(!isroot(y)) c[c[1][z] == y][z] = x;
    fa[x] = z , fa[y] = x , fa[c[r][x]] = y , c[l][y] = c[r][x] , c[r][x] = y;
    pushup(y) , pushup(x);
}
void splay(int x)
{
    update(x);
    while(!isroot(x))
    {
        int y = fa[x] , z = fa[y];
        if(!isroot(y))
        {
            if((c[0][y] == x) ^ (c[0][z] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}
void access(int x)
{
    int t = 0;
    while(x) splay(x) , si[x] += sum[c[1][x]] - sum[t] , c[1][x] = t , pushup(x) , t = x , x = fa[x];
}
void makeroot(int x)
{
    access(x) , splay(x) , swap(c[0][x] , c[1][x]) , rev[x] = 1;
}
void split(int x , int y)
{
    makeroot(x) , makeroot(y);
}
void link(int x , int y)
{
    split(x , y) , fa[x] = y , si[y] += sum[x] , pushup(y);
}
