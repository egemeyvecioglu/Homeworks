#include "the7.h"

void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath) {
    
    std::vector<int> path;
    int INF = INT_MAX;
    int adj[n][n];
    std::vector<int> path_arr[n][n];
    for(int i = 0; i< n; i++)
    {
        for(int j=0;j<n;j++) 
        {
            if(i==j) adj[i][j]=0;
            else adj[i][j]=INT_MAX;
        }
    }    
    
    for(std::vector<Road>::iterator road =roads.begin();road != roads.end();road++)
    {
        adj[(road->buildings).first][(road->buildings).second]=adj[(road->buildings).second][(road->buildings).first]=road->time;
    }

    if(printPath)
    {
        for(int i = 0; i< n; i++)
        {
            for(int j=0;j<n;j++) 
            {
                if(adj[i][j]!=INF && i!=j)path_arr[i][j].push_back(j);
            }
        }    
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int temp;
                if(adj[i][k] == INF || adj[k][j]==INF) temp = INF;
                else temp=adj[i][k]+adj[k][j];
                if(adj[i][j]>temp)
                {
                    adj[i][j]=temp;
                    if(printPath)
                    {
                        if(!path_arr[i][j].empty())path_arr[i][j].erase(path_arr[i][j].begin(),path_arr[i][j].end());
                        path_arr[i][j].insert(path_arr[i][j].end(),path_arr[i][k].begin(),path_arr[i][k].end());
                        path_arr[i][j].insert(path_arr[i][j].end(),path_arr[k][j].begin(),path_arr[k][j].end());
                    }

                }
                
            }
        }
    }

    int s_x_y_d = adj[s][x] + adj[x][y] + adj[y][d];
    int s_y_x_d = adj[s][y] + adj[y][x] + adj[x][d];
    
    if(s_x_y_d <= l && s_x_y_d <= s_y_x_d)
    {
        std::cout<<"YES BOTH "<<s_x_y_d<<"MINUTES\n";
        if(printPath)
        {
            std::cout<<s<<"->";
            PrintRange(path_arr[s][x].begin(),path_arr[s][x].end());std::cout<<"->";
            PrintRange(path_arr[x][y].begin(),path_arr[x][y].end());std::cout<<"->";
            PrintRange(path_arr[y][d].begin(),path_arr[y][d].end());
        }
        
    }
    else if(s_y_x_d <=l)
    {
        std::cout<<"YES BOTH "<<s_y_x_d<<"MINUTES\n";   
        if(printPath)
        {
            std::cout<<s<<"->";
            PrintRange(path_arr[s][y].begin(),path_arr[s][y].end());std::cout<<"->";
            PrintRange(path_arr[y][x].begin(),path_arr[y][x].end());std::cout<<"->";
            PrintRange(path_arr[x][d].begin(),path_arr[x][d].end());            
        }

        
    }
    else
    {
        int s_y_d = adj[s][y]  + adj[y][d];
        int s_x_d = adj[s][x] + adj[x][d];
        
        
        if(s_x_d<=s_y_d and s_x_d<=l)
        {
            std::cout<<"YES PRINTER "<<s_x_d<<"MINUTES\n";   
            if(printPath)
            {
                std::cout<<s<<"->";
                PrintRange(path_arr[s][x].begin(),path_arr[s][x].end());std::cout<<"->";
                PrintRange(path_arr[x][d].begin(),path_arr[x][d].end());
            }

        }
        else if(s_y_d<=l)
        {
            std::cout<<"YES DORM "<<s_y_d<<"MINUTES\n";
            if(printPath)
            {
                std::cout<<s<<"->";
                PrintRange(path_arr[s][y].begin(),path_arr[s][y].end());std::cout<<"->";
                PrintRange(path_arr[y][d].begin(),path_arr[y][d].end());                
            }

        }
        else
        {
            int t = adj[s][d];
            if(t<=l)
            {
                std::cout<<"YES DIRECTLY "<<t<<"MINUTES\n";
                if(printPath)
                {
                    std::cout<<s<<"->";
                    PrintRange(path_arr[s][d].begin(),path_arr[s][d].end());                
                }

            }
            else
            {
                std::cout<<"IMPOSSIBLE\n";
            }
        }
    }
    
    
}