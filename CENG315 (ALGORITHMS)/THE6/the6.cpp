// I GOT 0/100 FOR THIS THE
#include "the6.h"

void create_adj_list(vector<Pipeline*> adj_list[],vector<Pipeline *> pipeline,int num_of_buildings)
{
	int n = pipeline.size();
	for(int i = 0;i<num_of_buildings;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(pipeline[j]->end1 == i or pipeline[j]->end2 == i)(adj_list[i]).push_back(pipeline[j]);
		}
	}
}
bool in(vector<int> will_be_deleted,int id)
{
	int n = will_be_deleted.size();
	for(int i=0;i<n;i++)
	{
		if(will_be_deleted[i]==id)return true;
	}
	return false;
}

Pipeline* get_min(vector<Pipeline*> pipeline)
{
	int min = INT_MAX;
	Pipeline *id;
	int n = pipeline.size();
	for(int i = 0; i < n; i++)
	{
		if(pipeline[i]->cost_of_consumption < min)
		{
			min = pipeline[i]->cost_of_consumption;
			id =pipeline[i];
		}
	}

	return id;
}

void sort_costs(vector<Pipeline*> &pipeline, int n)
{
    for(int i = 0; i<n;i++)
    {
        for(int j = 0; j<n-i-1;j++)
        {
            if(pipeline[j]->cost_of_consumption > pipeline[j+1]->cost_of_consumption)
            {
                Pipeline *temp = pipeline[j];
                pipeline[j] = pipeline[j+1];
                pipeline[j+1] = temp;
            }
        }
    }
}

int find(int x, vector<int> &parent) {
  if (parent[x] == x)
    return x;
  return parent[x] = find(parent[x], parent);
}

bool add(vector<int>&pipeline, int id)
{
	int n = pipeline.size();
	bool already_there = false;
	for(int ege = 0; ege < n; ege++)
	{
		if(pipeline[ege] == id)
		{
			already_there = true;
			break;
		}
	}
	if(not already_there)
	{
		pipeline.push_back(id);
		return true;
	}
	return false;
}

vector<int> plan_min_cost_pipeline_usage(vector<Pipeline*> pipelines, int num_of_buildings) 
{
	vector<Pipeline*> adj_list[num_of_buildings];
	
  	int n = pipelines.size();

  	sort_costs(pipelines,n);


	vector<Pipeline*> furnace_rooms;
	for(int i=0; i<n ;i++)
	{	
		if((pipelines[i])->end1 == (pipelines[i])->end2)
		furnace_rooms.push_back(pipelines[i]);
	}
	sort_costs(furnace_rooms, num_of_buildings);
	//for (int i = 0; i < num_of_buildings; i++) cout<<furnace_rooms[i]->id<<endl;
	vector<int> parent(num_of_buildings);
	for (int i = 0; i < num_of_buildings; i++)
		parent[i] = i;
	
	int total_cost=0;
	vector<Pipeline *> temp_usage_plan;
	vector<int> usage_plan;
	
	for (const auto &p : pipelines) {
		int u = find(p->end1, parent);
		int v = find(p->end2, parent);
		if (u != v) 
		{
			parent[u] = v;
			temp_usage_plan.push_back(p);
			
		}

	}
	create_adj_list(adj_list,temp_usage_plan,num_of_buildings);
	int k = temp_usage_plan.size();;
	int ind=0;
	vector<int> will_be_deleted;
	for(int i = 0; i < num_of_buildings ; i++)
	{ 
		bool flag = false;
		int min , id;
		Pipeline *furnace_room_of = furnace_rooms[ind];
		min = furnace_room_of->cost_of_consumption;
		id = furnace_room_of->id;
		cout<<"\nFurnace room:"<<furnace_room_of->id<<endl;
		
		for(int j = 0 ; j < k; j++)
		{
			if(((temp_usage_plan[j])->end1 == furnace_room_of->end1 or (temp_usage_plan[j])->end2 == furnace_room_of->end1)) 
			{
				if((temp_usage_plan[j])->cost_of_consumption < min)
				{
					min = temp_usage_plan[j]->cost_of_consumption;
					id = temp_usage_plan[j] ->id;
					cout<<"		ID: "<<id<<endl;
				}
			}
			
		}

		cout<<"Min edge: "<<id<<endl;
		if(furnace_room_of->id == id)
		{
			flag = true;
			ind++;
			
		}
		
		add(usage_plan,furnace_room_of->id );
		add(usage_plan,id);



	}

	cout << "Total Cost: " << total_cost<<endl;

	return usage_plan;
}

vector<int> optimize_plan(vector<Pipeline*> current_solution, Pipeline* new_pipeline) {
 
    vector<int> solution;
    
    //your code here
    

    return solution; // this is a dummy return value. YOU SHOULD CHANGE THIS!
    
}