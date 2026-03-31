#include<bits/stdc++.h>
namespace reference{
const int MaxN=100010,MaxM=500010;
int n,f=1000,s,endpoint;
bool ifnear;
std::string nodestart;
struct edge
{
    int to,dis,next;
};
edge e[MaxM];
int head[MaxN],dis[MaxN],cnt,pre[MaxN],room9,sf9;
bool vis[MaxN];
inline void add_single_edge(int u,int v,int d)
{
    cnt++;
    e[cnt].dis=d;
    e[cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline void add_edge(int u,int v,int d)
{
    cnt++;
    e[cnt].dis=d;
    e[cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
    cnt++;
    e[cnt].dis=d;
    e[cnt].to=u;
    e[cnt].next=head[v];
    head[v]=cnt;
}
struct node
{
    int dis;
    int pos;
    bool operator <(const node &x)const
    {
        return x.dis<dis;
    }
};
inline void mapconstruct(int** eWeights)
{
    add_edge(11,13,100);
    add_edge(12,14,100);
    for(int i=1;i<=f;++i)
    {
        add_single_edge(i*10+1,i*10+11,eWeights[0][i-1]);
        add_single_edge(i*10+2,i*10+12,eWeights[1][i-1]);
        add_single_edge(i*10+3,i*10+13,eWeights[2][i-1]);
        add_single_edge(i*10+4,i*10+14,eWeights[3][i-1]);

        add_single_edge(i*10+1,i*10-10+1,eWeights[0][i-1]);
        add_single_edge(i*10+2,i*10-10+2,eWeights[1][i-1]);
        add_single_edge(i*10+3,i*10-10+3,eWeights[2][i-1]);
        add_single_edge(i*10+4,i*10-10+4,eWeights[3][i-1]);

        add_edge(i*10+1,i*10+2,81);
        add_edge(i*10+3,i*10+4,81);
        if(i%10==0)
        {
            add_edge(i*10+5,i*10+7-10,eWeights[0][0]);
            add_edge(i*10+6,i*10+8+10,eWeights[0][0]);

            add_edge(i*10+5,i*10+6,15);
            add_edge(i*10+5,i*10+1,48);
            add_edge(i*10+2,i*10+5,43);
            add_edge(i*10+1,i*10+6,53);
            add_edge(i*10+6,i*10+2,38);
            
            add_edge(i*10+8+10,i*10+3+10,53);
            add_edge(i*10+8+10,i*10+4+10,38);
            
            add_edge(i*10+7-10,i*10+3-10,48);
            add_edge(i*10+4-10,i*10+7-10,43);
        }
    }
}
std::priority_queue<node> q;
inline int nodetransfer(std::string nodex,int codenum)
{
    static int k=1,room,cntnode,sf,len;
    k=1;
    len=nodex.length();
    sf=0;
    while(k<len-2)
    {
        sf*=10;
        sf+=nodex[k++]-'0';
    }
    room=(nodex[len-2]-'0')*10+(nodex[len-1]-'0');
    if(nodex[0]=='A')
    {
        if(sf%10==0)
        {
            if(room==22)
            {
                cntnode=sf*10+5;
            }
            else if(room==23)
            {
                cntnode=sf*10+6;
            }
            else
            { 
                if(room>14)room-=14;
                add_edge(sf*10+codenum,sf*10+5,(abs(room-8))*5+10);
                add_edge(sf*10+codenum,sf*10+6,(abs(room-9))*5+10);
                add_edge(sf*10+codenum,sf*10+1,room*5+8);
                add_edge(sf*10+codenum,sf*10+2,83-room*5);
                cntnode=sf*10+codenum;
            }
        }
        else
        {
            if(room>14)room-=14;
            add_edge(sf*10+codenum,sf*10+1,room*5+8);
            add_edge(sf*10+codenum,sf*10+2,83-room*5);
            cntnode=sf*10+codenum;
        }
    }
    else if(nodex[0]=='B')
    {
        if(sf%10==9)
        {
            if(room==8)
            {
                cntnode=sf*10+7;
            }
            else
            { 
                if(room>14)room-=14;
                add_edge(sf*10+codenum,sf*10+7,(abs(room-8))*5+10);
                add_edge(sf*10+codenum,sf*10+3,room*5+8);
                add_edge(sf*10+codenum,sf*10+4,83-room*5);
                cntnode=sf*10+codenum;
            }
        }
        else if(sf%10==1)
        {
            if(room==9)
            {
                cntnode=sf*10+8;
            }
            else
            { 
                if(room>14)room-=14;
                add_edge(sf*10+codenum,sf*10+8,(abs(room-8))*5+10);
                add_edge(sf*10+codenum,sf*10+3,room*5+8);
                add_edge(sf*10+codenum,sf*10+4,83-room*5);
                cntnode=sf*10+codenum;
            }
        }
        else
        {
            if(room>14)room-=14;
            add_edge(sf*10+codenum,sf*10+3,room*5+8);
            add_edge(sf*10+codenum,sf*10+4,83-room*5);
            cntnode=sf*10+codenum;
        }
    }
    if(codenum==9)
    {
        room9=room;
        sf9=sf;
        nodestart=nodex[0];
    }
    if(sf9==sf and nodex[0]==nodestart[0] and codenum!=9)
    {
        add_edge(sf*10+codenum,sf*10+9,(abs(room-room9))*5+10);
        ifnear=1;
        dis[cntnode]=(abs(room-room9))*5+10;
    }
    return cntnode;
}
inline void dijkstra()
{
    dis[s]=0;
    q.push((node){0,s});
    while(!q.empty())
    {
        node tmp=q.top();
        q.pop();
        int x=tmp.pos,d=tmp.dis;
        if(vis[x])continue;
        vis[x]=1;
        if(x==endpoint)return;
        for(int i=head[x];i;i=e[i].next)
        {
            int y=e[i].to;
            if(dis[y]>dis[x]+e[i].dis)
            {
                dis[y]=dis[x]+e[i].dis;
                pre[y]=x;
                if(!vis[y])
                {
                    q.push((node){dis[y],y});
                }
            }
        }
    }
}
inline void endpush(std::string nodex,std::string startnode,int nextnum,std::vector<std::string>& path)
{
    int sf,room,len,k=1,rooms;
    std::string corridorcode;
    len=nodex.length();
    sf=0;
    room=(nodex[len-2]-'0')*10+(nodex[len-1]-'0');
    while(k<len-2)
    {
        sf*=10;
        sf+=nodex[k++]-'0';
    }
    if(room>14)room-=14;
    if(nextnum==1)
    {
        for(int j=room;j>=1;--j)
        {
            corridorcode=std::to_string(j);
            if(j<10)corridorcode="0"+corridorcode;
            path.push_back("AC"+std::to_string(sf)+corridorcode);
        }
    }
    else if(nextnum==2)
    {
        for(int j=room;j<=14;++j)
        {
            corridorcode=std::to_string(j);
            if(j<10)corridorcode="0"+corridorcode;
            path.push_back("AC"+std::to_string(sf)+corridorcode);
        }
    }
    else if(nextnum==3)
    {
        for(int j=room;j>=1;--j)
        {
            corridorcode=std::to_string(j);
            if(j<10)corridorcode="0"+corridorcode;
            path.push_back("BC"+std::to_string(sf)+corridorcode);
        }
    }
    else if(nextnum==4)
    {
        for(int j=room;j<=14;++j)
        {
            corridorcode=std::to_string(j);
            if(j<10)corridorcode="0"+corridorcode;
            path.push_back("BC"+std::to_string(sf)+corridorcode);
        }
    }
    else if(nextnum==5)
    {
        if(room<8)
            for(int j=room;j<=8;++j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
        else if(room>8)
            for(int j=room;j>=8;--j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
    }
    else if(nextnum==6)
    {
        if(room<9)
            for(int j=room;j<=9;++j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
        else if(room>9)
            for(int j=room;j>=9;--j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
    }
    else if(nextnum==7)
    {
        if(room<8)
            for(int j=room;j<=8;++j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("BC"+std::to_string(sf)+corridorcode);
            }
        else if(room>8)
            for(int j=room;j>=8;--j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("BC"+std::to_string(sf)+corridorcode);
            }
    }
    else if(nextnum==8)
    {
        if(room<9)
            for(int j=room;j<=9;++j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("BC"+std::to_string(sf)+corridorcode);
            }
        else if(room>9)
            for(int j=room;j>=9;--j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("BC"+std::to_string(sf)+corridorcode);
            }
    }
    else if(nextnum==9)
    {
        rooms=(startnode[len-2]-'0')*10+(startnode[len-1]-'0');
        if(rooms>14)rooms-=14;
        if((nodex[len-2]-'0')*10+(nodex[len-1]-'0')!=(startnode[len-2]-'0')*10+(startnode[len-1]-'0') and rooms==room)
        {
            corridorcode=std::to_string(room);
            if(room<10)corridorcode="0"+corridorcode;
            path.push_back("AC"+std::to_string(sf)+corridorcode);
        }
        if(room<rooms)
            for(int j=room;j<=rooms;++j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
        else if(room>rooms)
            for(int j=room;j>=rooms;--j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
    }
}
inline void startpush(std::string nodex,int formernum,std::vector<std::string>& path)
{
    int sf,room,len,k=1,rooms;
    std::string corridorcode;
    len=nodex.length();
    sf=0;
    room=(nodex[len-2]-'0')*10+(nodex[len-1]-'0');
    while(k<len-2)
    {
        sf*=10;
        sf+=nodex[k++]-'0';
    }
    if(room>14)room-=14;
    if(formernum==1)
    {
        for(int j=1;j<=room;++j)
        {
            corridorcode=std::to_string(j);
            if(j<10)corridorcode="0"+corridorcode;
            path.push_back("AC"+std::to_string(sf)+corridorcode);
        }
    }
    else if(formernum==2)
    {
        for(int j=14;j>=room;--j)
        {
            corridorcode=std::to_string(j);
            if(j<10)corridorcode="0"+corridorcode;
            path.push_back("AC"+std::to_string(sf)+corridorcode);
        }
    }
    else if(formernum==3)
    {
        for(int j=1;j<=room;++j)
        {
            corridorcode=std::to_string(j);
            if(j<10)corridorcode="0"+corridorcode;
            path.push_back("BC"+std::to_string(sf)+corridorcode);
        }
    }
    else if(formernum==4)
    {
        for(int j=14;j>=room;--j)
        {
            corridorcode=std::to_string(j);
            if(j<10)corridorcode="0"+corridorcode;
            path.push_back("BC"+std::to_string(sf)+corridorcode);
        }
    }
    else if(formernum==5)
    {
        if(room<8)
            for(int j=8;j>=room;--j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
        else if(room>8)
            for(int j=8;j<=room;++j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
    }
    else if(formernum==6)
    {
        if(room<9)
            for(int j=9;j>=room;--j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
        else if(room>9)
            for(int j=9;j<=room;++j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("AC"+std::to_string(sf)+corridorcode);
            }
    }
    else if(formernum==7)
    {
        if(room<8)
            for(int j=8;j>=room;--j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("BC"+std::to_string(sf)+corridorcode);
            }
        else if(room>8)
            for(int j=8;j<=room;++j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("BC"+std::to_string(sf)+corridorcode);
            }
    }
    else if(formernum==8)
    {
        if(room<9)
            for(int j=9;j>=room;--j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("BC"+std::to_string(sf)+corridorcode);
            }
        else if(room>9)
            for(int j=9;j<=room;++j)
            {
                corridorcode=std::to_string(j);
                if(j<10)corridorcode="0"+corridorcode;
                path.push_back("BC"+std::to_string(sf)+corridorcode);
            }
    }
}
int FindShortestPath(std::string start, std::string end, std::vector<std::string>& path, int** eWeights)
{
    if(start==end)
    {
        path.clear();
        path.push_back(start);
        return 0;
    }
    n=f*10;
    for(int i=1;i<=n;++i)
    {
        dis[i]=0x7fffffff;
        vis[i]=0;
        head[i]=0;
        pre[i]=0;
    }
    std::string corridorcode,istr;
    int ilen,formercode,nowcode,nextcode;
    nodestart="X";
    cnt=0;
    sf9=-1;
    path.clear();
    q=std::priority_queue<node>();
    s=nodetransfer(start,9);
    endpoint=nodetransfer(end,0);
    if(ifnear==1)
    {
        ifnear=0;
        path.push_back(end);
        nextcode=s%10;
        endpush(end,start,nextcode,path);
        path.push_back(start);
        std::reverse(path.begin(),path.end());
        return dis[endpoint];
    }
    mapconstruct(eWeights);
    dijkstra();
    nextcode=pre[endpoint]%10;
    path.push_back(end);
    endpush(end,start,nextcode,path);
    for(int i=pre[endpoint];i!=s;i=pre[i])
    {
        istr=std::to_string(i);
        ilen=istr.length();
        int iroom=istr[ilen-1],ifloor;
        ifloor=0;
        for(int j=0;j<ilen-1;++j)
        {
            ifloor=ifloor*10+istr[j]-'0';
        }
        nowcode=i%10;
        nextcode=pre[i]%10;
        if(istr[ilen-1]=='1')
        {
            path.push_back("AE"+std::to_string(ifloor)+"01");
            if(nextcode==2)
            {
                for(int j=1;j<=14;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
        }
        if(istr[ilen-1]=='2')
        {
            path.push_back("AE"+std::to_string(ifloor)+"02");
            if(nextcode==1)
            {
                for(int j=14;j>=1;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
        }
        if(istr[ilen-1]=='3')
        {
            path.push_back("BE"+std::to_string(ifloor)+"01");
            if(nextcode==4)
            {
                for(int j=1;j<=14;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
        }
        if(istr[ilen-1]=='4')
        {
            path.push_back("BE"+std::to_string(ifloor)+"02");
            if(nextcode==3)
            {
                for(int j=14;j>=1;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
        }
        if(istr[ilen-1]=='5')
        {
            if(formercode==1)
            {
                for(int j=1;j<=8;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(formercode==2)
            {
                for(int j=14;j>=8;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(formercode==6)
            {
                path.push_back("AC"+std::to_string(ifloor)+"09");
                path.push_back("AC"+std::to_string(ifloor)+"08");
            }
            path.push_back("A"+std::to_string(ifloor)+"22");
            if(nextcode==1)
            {
                for(int j=8;j>=1;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(nextcode==2)
            {
                for(int j=8;j<=14;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(nextcode==6)
            {
                path.push_back("AC"+std::to_string(ifloor)+"08");
                path.push_back("AC"+std::to_string(ifloor)+"09");
            }
        }
        if(istr[ilen-1]=='6')
        {
            if(formercode==1)
            {
                for(int j=1;j<=9;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(formercode==2)
            {
                for(int j=14;j>=9;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
            path.push_back("A"+std::to_string(ifloor)+"23");
            if(nextcode==1)
            {
                for(int j=9;j>=1;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(nextcode==2)
            {
                for(int j=9;j<=14;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("AC"+std::to_string(ifloor)+corridorcode);
                }
            }
        }
        if(istr[ilen-1]=='7')
        {
            if(formercode==3)
            {
                for(int j=1;j<=8;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(formercode==4)
            {
                for(int j=14;j>=8;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
            path.push_back("B"+std::to_string(ifloor)+"08");
            if(nextcode==3)
            {
                for(int j=8;j>=1;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(nextcode==4)
            {
                for(int j=8;j<=14;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
        }
        if(istr[ilen-1]=='8')
        {
            if(formercode==3)
            {
                for(int j=1;j<=9;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(formercode==4)
            {
                for(int j=14;j>=9;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
            path.push_back("B"+std::to_string(ifloor)+"09");
            if(nextcode==3)
            {
                for(int j=9;j>=1;--j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
            else if(nextcode==4)
            {
                for(int j=9;j<=14;++j)
                {
                    corridorcode=std::to_string(j);
                    if(j<10)corridorcode="0"+corridorcode;
                    path.push_back("BC"+std::to_string(ifloor)+corridorcode);
                }
            }
        }
        formercode=i%10;
    }
    startpush(start,formercode,path);
    path.push_back(start);
    std::reverse(path.begin(),path.end());
    return dis[endpoint];
}
}