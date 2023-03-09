#include "the8.h"

//DO NOT ADD OTHER LIBRARIES


void matchPattern(const std::string& sequence, const std::pair<std::string,std::string> mapping, const std::string& pattern){
    
    int  hash_arr[26];
    int diff =(mapping.second[0])-(mapping.first)[0]; 
    
    
    for(int i = 0; i < 26; i++)
    {
        hash_arr[i] = i;

    }

    for(int i = 0; i < 26; i++)
    {
        if(mapping.second[0]-65 == i)
        {
            if(diff>0)hash_arr[i-diff] = i;
            else hash_arr[i] = hash_arr[i-diff];
            break;
        }
    }

    int pattern_size = pattern.size();
    char transitions[1000];
    for(int i = 0; i < pattern_size; i++)
    {
        transitions[i]=pattern[i];
    }
    
    int seq_size = sequence.size();
    int state = 0;
    bool none=true;
    bool first=true;
    int overlap = 0;
    for(int i = 0; i < seq_size; i++)
    {
        //std::cout<<hash_arr[sequence[i]-65]<<"      "<<hash_arr[transitions[state]-65]<<"\n";
        if(hash_arr[sequence[i]-65] == hash_arr[transitions[state]-65] )
        {
            
            state++;
            if(state==pattern_size)
            {
                if(first)
                {
                    std::cout<<i-pattern_size+1;
                    first=false;
                }
                else std::cout<<" "<<i-pattern_size+1;
                overlap = state - 2;
                state = overlap;
                none=false;
            }
        }
        else state = overlap = 0;
    }
    if(none)std::cout<<"NONE";

}
