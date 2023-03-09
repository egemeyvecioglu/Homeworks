#include "the5.h"


bool inside(vector<int>& path, int id) {
    
     for (int r =0; r < path.size(); r++)
        if (id == path[r])
            return true;
    return false;
    
}

vector<int> maze_trace(vector<Room*> maze) {
    
    bool return_totally = false;
    vector<int> path;
    vector<Room*> stack;
    stack.push_back(maze[0]);
    
    vector<int> completed;  // the rooms whose itself & subrooms entered & left
    
    while(stack.size() > 0) {
        Room* room = stack[stack.size()-1];
        if (inside(completed, room->id)) {  // this was re-encountered in a 
            stack.pop_back();               // future step and handled there
            continue;
        }
        
        if (room->content == '*') {
            return_totally = true;
            path.push_back(room->id);
            completed.push_back(room->id);
            stack.pop_back();
            continue;
        }
        
        if (return_totally) {
            if (inside(path, room->id)) {   // if this is an entered room,  
                path.push_back(room->id);   // leave it. 
                completed.push_back(room->id);  // otherwise neglect it
            }
            stack.pop_back();
            continue;
        }
        
        path.push_back(room->id);
        bool turn_back = true; // assume there is no nonvisited subroom
        
        for (int i=room->neighbors.size()-1; i>=0; i--) {
            
            Room* r = room->neighbors[i];
            
            bool is_visited = false;
            if (!inside(path, r->id)) {
                stack.push_back(room);
                stack.push_back(r);
                turn_back = false;  // there is nonvisited room, don't turn back
            }
                
        }
        
        if (turn_back) {
            stack.pop_back();
            completed.push_back(room->id);
        }
    }
    
    return path;
}


