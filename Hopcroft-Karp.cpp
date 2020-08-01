#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int M=100007;
const ll q=7057594037927903;
const ll prime=2137;
#define pb push_back
#define mp make_pair
#define f first
#define s second

int dis[M],vis[M],match[M],n,m,odwiedzone[M],kolor[M],odwiedzone2[M]; ll tab[M];
queue <int>Q; vector <int>v[M],ans; map <ll,int>zbior;

int dfs(int h)
{
    if(vis[h])
        return 0;
    vis[h]=true;

    for(int i=0; i<(int)v[h].size(); i++)
    {
        if(!match[v[h][i]])
        {
            match[h]=v[h][i];
            match[v[h][i]]=h;
            return 1;
        }
        else if(dis[match[v[h][i]]]==dis[h]+1 && dfs(match[v[h][i]]))
        {
            match[h]=v[h][i];
            match[v[h][i]]=h;
            return 1;
        }
    }
    return 0;
}

void matching()
{
    int res=0,pres=-1;
    while(res!=pres)
    {
        pres=res;
        for(int i=1; i<=n; i++)
            dis[i]=0,vis[i]=0;

        /*  for(int i=1; i<=n; i++)
              if(!match[i] && !kolor[i])
                  Q.push(i),dis[i]=0,vis[i]=1;


          while(!Q.empty())
          {
              int w=Q.front();
              Q.pop();
              for(int i=0; i<(int)v[w].size(); i++)
              {
                  if(match[v[w][i]] && !vis[match[v[w][i]]])
                  {
                      int pom=match[v[w][i]];
                      Q.push(pom);
                      dis[pom]=dis[w]+1;
                      vis[pom]=1;
                  }
              }
          }

          for(int i=1; i<=n; i++)
              vis[i]=0;
        */

        for(int i=1; i<=n; i++)
            if(!match[i] && !kolor[i])
                res+=dfs(i);
    }
}

void wczytaj()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        scanf("%lld",&tab[i]);
        zbior[tab[i]]=i;
    }

    for(int i=1; i<=n; i++)
    {
        if(zbior[2LL*tab[i]])
            v[i].pb(zbior[2LL*tab[i]]);

        if(zbior[3LL*tab[i]])
            v[i].pb(zbior[3LL*tab[i]]);

        if(tab[i]%2LL==0 && zbior[tab[i]/2LL])
            v[i].pb(zbior[tab[i]/2LL]);

        if(tab[i]%3LL==0 && zbior[tab[i]/3LL])
            v[i].pb(zbior[tab[i]/3LL]);
    }
}

void dfs2(int h)
{
    odwiedzone[h]=1;
    for(int i=0; i<(int)v[h].size(); i++)
        if(!odwiedzone[v[h][i]])
        {
            if(kolor[h]==0)
                kolor[v[h][i]]=1;
            else
                kolor[v[h][i]]=0;
            dfs2(v[h][i]);
        }
}

void dfs3(int h)
{
    odwiedzone2[h]=1;
    for(int i=0; i<(int)v[h].size(); i++)
    {
        if(!kolor[h] && v[h][i]!=match[h] && !odwiedzone2[v[h][i]])
            dfs3(v[h][i]);
        else if(kolor[h] && v[h][i]==match[h] && !odwiedzone2[v[h][i]])
            dfs3(v[h][i]);
    }
}

int main()
{
    wczytaj();
    for(int i=1; i<=n; i++)
        if(!odwiedzone[i])
            dfs2(i);

    matching();

    int wynik=n;
    for(int i=1; i<=n; i++)
        if(!kolor[i] && match[i])
            wynik--;

    for(int i=1; i<=n; i++)
        if(!odwiedzone2[i] && !match[i] && !kolor[i])
            dfs3(i);

    for(int i=1; i<=n; i++)
        if((!kolor[i] && odwiedzone2[i] && match[i]) || (kolor[i] && !odwiedzone2[i] && match[i]) || !match[i])
            ans.pb(i);

    printf("%d\n",wynik);
    for(int i=0; i<(int)ans.size(); i++)
        printf("%lld ",tab[ans[i]]);

    printf("\n");
    return 0;
}
