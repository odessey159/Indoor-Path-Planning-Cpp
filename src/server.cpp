#include "httplib.h"
#include "reference.h"
#include <vector>
#include <string>
#include <iostream>

using namespace httplib;

int default_weights_storage[4][1000];

int main()
{
    Server svr;

    for(int i=0;i<4;++i)
        for(int j=0;j<1000;++j)
            default_weights_storage[i][j]=10;

    svr.Post("/route",[](const Request& req,Response& res)
    {
        try
        {
            std::string body=req.body;

            std::string start="";
            std::string end="";

            auto s_pos=body.find("start");
            auto e_pos=body.find("end");

            if(s_pos!=std::string::npos)
            {
                start=body.substr(s_pos+8,body.find("\"",s_pos+8)-(s_pos+8));
            }

            if(e_pos!=std::string::npos)
            {
                end=body.substr(e_pos+6,body.find("\"",e_pos+6)-(e_pos+6));
            }

            std::vector<std::string> path;

            int* w[4];
            for(int i=0;i<4;++i)
                w[i]=default_weights_storage[i];

            int dist=reference::FindShortestPath(start,end,path,w);

            std::string json="{ \"distance\": "+std::to_string(dist)+", \"path\": [";

            for(int i=0;i<path.size();++i)
            {
                json+="\""+path[i]+"\"";
                if(i!=path.size()-1)json+=",";
            }

            json+="] }";

            res.set_content(json,"application/json");
        }
        catch(...)
        {
            res.status=500;
            res.set_content("{\"error\":\"internal error\"}","application/json");
        }
    });

    std::cout<<"Server running at http://localhost:8081\n";
    svr.listen("0.0.0.0",8081);
}