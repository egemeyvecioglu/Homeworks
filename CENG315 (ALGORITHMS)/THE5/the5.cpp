#include "the5.h"

/* 
    in the5.h "struct Room" is defined as below:
    
    struct Room {
        int id;
        char content;
        vector<Room*> neighbors;
    };

*/

bool recursive_maze_trace(Room* room,vector<int>& path,bool visited[])
{
    visited[room->id] = true;
    
    if(room->content == '*')
    {
        path.push_back(room->id);             //IF IT FOUND THE TREASURE
        return true;
    }
    
    
    int n = (room->neighbors).size();
    int m = 0;
    for(int j =0;j<n;j++)                                               //IF IT HAS NO UNVISITED NEIGHBORS                        
        if(   visited[((room->neighbors)[j])->id]    ==false    )m++;  //AND DIDN'T FIND THE TREASURE
    if(m==0)
    {
        path.push_back(room->id);
        return false;
    }
    
    
    bool found;
    for(int i = 0; i < n; i++)
    {

        Room* successor = (room->neighbors)[i];
        if(not visited[successor->id])
        {
            path.push_back(room->id);
            found=recursive_maze_trace(successor,path,visited);         //GENERAL CASE
        }   
        if(found)break;  
        
    }
    path.push_back(room->id);
    return found;
}

vector<int> maze_trace(vector<Room*> maze) { 


    bool visited[10000]= {false};
    vector<int> path;

    Room* room = maze[0];
    
    recursive_maze_trace(room,path,visited);

    return path;
}