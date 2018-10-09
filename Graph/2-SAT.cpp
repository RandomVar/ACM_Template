/**2-SAT**/
vector<int> g[maxn*2];
bool mark[maxn*2];
int s[maxn*2],c;
bool dfs(int x){
    if(mark[x^1]) return false;
    if(mark[x]) return true;
    mark[x]=true;
    s[c++]=x;
    for(int i=0;i<g[x].size();i++)
        if(!dfs(g[x][i])) return false;
    return true;
}
void init(int n){
    for(int i=0;i<n*2;i++) g[i].clear();
    memset(mark,0,sizeof(mark));
}
void add_clause(int x,int xval,int y,int yval){
//x的xval状态与y的yval状态冲突
    x=x*2+xval;
    y=y*2+yval;
    g[x^1].push_back(y); //选了x^1就必须选y，连边表示 推导出
    g[y^1].push_back(x);
}
bool solve(int n){
    for(int i=0;i<n*2;i+=2)
        if(!mark[i]&&!mark[i+1]){
            c=0;
            if(!dfs(i)){
                while(c>0) mark[s[--c]]=false;
                if(!dfs(i+1)) return false;
            }
        }
    return true;
}