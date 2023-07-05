extern "C" {
  #include "./message.h"
  #include "./logging.h"
};

#include<math.h>
#include<iostream>
#include<vector>
#include<string>
#include<poll.h>
#include<sys/wait.h>
#include<algorithm>

using std::cout,std::cin,std::endl,std::vector,std::string,std::cerr;

typedef struct bomber
{
	pid_t pid;
	coordinate pos;
	int num_of_args;
	char **args;
	int alive;
	int fd[2];
}bomber;

typedef struct bomb
{
	pid_t pid;
	coordinate pos;
	unsigned int radius;
	int fd[2];
	int alive;
	vector<obsd> damaged_obstcl;
	vector<bomber> remarked_bombers;
	//long interval;
}bomb;


int map_width, map_height, obstacle_count, bomber_count, pipe_count = 0;
int **MAP;
int bomb_id = -1,bomber_id = -1;
int alive_bombers;
int	alive_bombs = 0;

vector<bomb> remarked_bombs;


pid_t WINNER = -1;



void read_input(obsd obstacle_data[], vector<bomber> &bombers)
{

	MAP = (int**) malloc(sizeof(int*)*(map_height));
	for (int i = 0; i < map_height; i++) {
		MAP[i] = (int*) calloc(map_width,sizeof(int));
	}

	for(int i = 0; i < obstacle_count ; i++)
	{
		cin >> (obstacle_data[i]).position.x >> (obstacle_data[i]).position.y >> (obstacle_data[i]).remaining_durability;
		MAP[(obstacle_data[i]).position.y][(obstacle_data[i]).position.x] = 4; // Obstacle is represented with 4
	}

	for(int i = 0; i < bomber_count ; i++)
	{
		cin >> (bombers[i]).pos.x >> (bombers[i]).pos.y >> (bombers[i]).num_of_args;
		MAP[(bombers[i]).pos.y][bombers[i].pos.x] = 2; // Bomber is represented with 2
		(bombers[i]).args = new char*[(bombers[i]).num_of_args+1];
        for(int j = 0; j < (bombers[i]).num_of_args ; j++)
        {
			char* argm = new char[20];
			cin >> argm;
            ((bombers[i]).args)[j] = argm;
        }
		((bombers[i]).args)[(bombers[i]).num_of_args]  = NULL;
		bombers[i].alive = 1;

	}

	return;
}

int check_surroundings(int a, int b,int radius, object_type type, od object_datas[])
{
	int object_count = 0;
	int x = a, y = b;

	if(MAP[y][x] == 3)
	{
		od obj_data;
		obj_data.position.y = y;
		obj_data.position.x = x;
		obj_data.type = type == BOMB ? BOMBER : BOMB;
		object_datas[object_count++] = obj_data;
	}

	for(int i = 1; i <=radius; i++) // RIGHT
	{
		x = a + i;
		if(y >= map_height)
		{
			break;
		}
		int vis_code = MAP[y][x];
		if(vis_code  == 4)
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = OBSTACLE;
			object_datas[object_count++] = obj_data;

			break;
		}
		else if(vis_code == 1) // There is only a bomb
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = BOMB;
			object_datas[object_count++] = obj_data;

		}else if(vis_code == 2) // There is only a bomber
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = BOMBER;
			object_datas[object_count++] = obj_data;


		}else if(vis_code == 3) // There are both bomber and bomb
		{
			od obj_data1;
			obj_data1.type = BOMB;
			obj_data1.position.y = y;
			obj_data1.position.x = x;

			od obj_data2;
			obj_data2.position.y = y;
			obj_data2.position.x = x;
			obj_data2.type = BOMBER;

			object_datas[object_count++] = obj_data1;
			object_datas[object_count++] = obj_data2;
			
		}
	}

	for(int i = -1; i >=-radius; i--) // LEFT
	{

		x = a + i;
		if(x < 0)
		{
			break;
		}
		int vis_code = MAP[y][x];
		if(vis_code  == 4)
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = OBSTACLE;
			object_datas[object_count++] = obj_data;
			break;
		}
		else if(vis_code == 1) // There is only a bomb
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = BOMB;
			object_datas[object_count++] = obj_data;
		}else if(vis_code == 2) // There is only a bomber
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = BOMBER;
			object_datas[object_count++] = obj_data;

		}else if(vis_code == 3) // There are both bomber and bomb
		{

			od obj_data1;
			obj_data1.type = BOMB;
			obj_data1.position.y = y;
			obj_data1.position.x = x;

			od obj_data2;
			obj_data2.position.y = y;
			obj_data2.position.x = x;
			obj_data2.type = BOMBER;

			object_datas[object_count++] = obj_data1;
			object_datas[object_count++] = obj_data2;
		}
	}

	x = a;

	for(int i = 1; i <=radius; i++) // UP
	{

		y = b + i;
		if(y >= map_height)
		{
			break;
		}

		int vis_code = MAP[y][x];
		if(vis_code  == 4)
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = OBSTACLE;
			object_datas[object_count++] = obj_data;;
			break;
		}
		else if(vis_code == 1) // There is only a bomb
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = BOMB;
			object_datas[object_count++] = obj_data;

		}else if(vis_code == 2) // There is only a bomber
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = BOMBER;
			object_datas[object_count++] = obj_data;

		}else if(vis_code == 3) // There are both bomber and bomb
		{
			od obj_data1;
			obj_data1.type = BOMB;
			obj_data1.position.y = y;
			obj_data1.position.x = x;

			od obj_data2;
			obj_data2.position.y = y;
			obj_data2.position.x = x;
			obj_data2.type = BOMBER;

			object_datas[object_count++] = obj_data1;
			object_datas[object_count++] = obj_data2;
		}
	}

	for(int i = -1; i >=-radius; i--) // DOWN
	{
		y = b + i;
		if(y < 0)
		{
			break;
		}

		int vis_code = MAP[y][x];
		if(vis_code  == 4)
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = OBSTACLE;
			object_datas[object_count++] = obj_data;;
			break;
		}
		else if(vis_code == 1) // There is only a bomb
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = BOMB;
			object_datas[object_count++] = obj_data;


		}else if(vis_code == 2) // There is only a bomber
		{
			od obj_data;
			obj_data.position.y = y;
			obj_data.position.x = x;
			obj_data.type = BOMBER;
			object_datas[object_count++] = obj_data;



		}else if(vis_code == 3) // There are both bomber and bomb
		{
			od obj_data1;
			obj_data1.type = BOMB;
			obj_data1.position.y = y;
			obj_data1.position.x = x;

			od obj_data2;
			obj_data2.position.y = y;
			obj_data2.position.x = x;
			obj_data2.type = BOMBER;

			object_datas[object_count++] = obj_data1;
			object_datas[object_count++] = obj_data2;

		}
	}

	return object_count;
}


void respond_message(im &coming_msg,  vector<bomber> &bombers, vector<bomb> &bombs)
{
	switch (coming_msg.type)
	{
		case BOMBER_START:
		{
			omp out;
			om going_msg;

			bombers[bomber_id].alive = 1;
			going_msg.type = BOMBER_LOCATION;
			going_msg.data.new_position.x = bombers[bomber_id].pos.x;
			going_msg.data.new_position.y = bombers[bomber_id].pos.y;

			send_message((bombers[bomber_id].fd)[1], &going_msg); // Send response
			out.m = &going_msg;
			out.pid = bombers[bomber_id].pid;
			print_output(NULL,&out,NULL,NULL);
			return;
		}

		case BOMBER_SEE:
		{
			omp out;
			om going_msg;
			going_msg.type = BOMBER_VISION;
			od object_datas[25];
			int obj_cnt;

			obj_cnt = check_surroundings(bombers[bomber_id].pos.x,bombers[bomber_id].pos.y, 3, BOMBER, object_datas);

			going_msg.data.object_count = obj_cnt;
			send_message((bombers[bomber_id].fd)[1], &going_msg); // Send response

			for(int i = 0; i < obj_cnt ; i++)
			{
				send_object_data((bombers[bomber_id].fd)[1], obj_cnt , object_datas + i); // Send response
			}

			out.m = &going_msg;
			out.pid = bombers[bomber_id].pid;
			od* obj = object_datas;
			print_output(NULL,&out,NULL,obj);

			return;
		}

		case BOMBER_MOVE:
		{
			omp out;
			om going_msg;
			coordinate target_coordinate;
			target_coordinate.x = coming_msg.data.target_position.x;
			target_coordinate.y = coming_msg.data.target_position.y;



			int x_distance = (int) target_coordinate.x - (int) bombers[bomber_id].pos.x;
			int y_distance = (int) target_coordinate.y - (int) bombers[bomber_id].pos.y;

			bool valid_move =	(  ((abs(y_distance) == 0) and (abs(x_distance) == 1)) or ((abs(x_distance == 0)) and (abs(y_distance) == 1))  ) // move is in one way and single step
								and  ((int) target_coordinate.x < map_width and (int) target_coordinate.y < map_height)  // target position is valid
								and	(MAP[target_coordinate.y][target_coordinate.x] < 2);  // target position not occupied by an obstacle or a bomber;

			if(valid_move)
			{
				MAP[(bombers[bomber_id]).pos.y][bombers[bomber_id].pos.x] -= 2;

				(bombers[bomber_id]).pos.y = target_coordinate.y;
				(bombers[bomber_id]).pos.x = target_coordinate.x;


				MAP[(bombers[bomber_id]).pos.y][bombers[bomber_id].pos.x] += 2;



			}

			going_msg.type = BOMBER_LOCATION;
			going_msg.data.new_position.x = (bombers[bomber_id]).pos.x;
			going_msg.data.new_position.y = (bombers[bomber_id]).pos.y;


			send_message((bombers[bomber_id].fd)[1], &going_msg); // Send response

			out.m = &going_msg;
			out.pid = bombers[bomber_id].pid;
			print_output(NULL,&out,NULL,NULL);

			return;
		}

		case BOMBER_PLANT:
		{

			omp out;
			om going_msg;
			bd bomb_info = coming_msg.data.bomb_info;
			bool planted = MAP[(bombers[bomber_id]).pos.y][bombers[bomber_id].pos.x] == 2;
			going_msg.type = BOMBER_PLANT_RESULT;
			going_msg.data.planted = planted;

			pid_t pid;
			if(planted)
			{
				bomb new_bomb;
				PIPE(new_bomb.fd);
				new_bomb.pos = bombers[bomber_id].pos;
				new_bomb.radius = bomb_info.radius;
				new_bomb.alive = 1;
				MAP[(bombers[bomber_id]).pos.y][bombers[bomber_id].pos.x] += 1;
				bombs.push_back(new_bomb);
				alive_bombs++;
				pid = fork();
				if(!pid)
				{

					if(pid == -1)
					{
						perror("fork");
            			exit(EXIT_FAILURE);
					}

					close((new_bomb.fd)[1]);
					dup2((new_bomb.fd)[0],1);
					dup2((new_bomb.fd)[0],0);
					close((new_bomb.fd)[0]);


					string interval_str = std::to_string(bomb_info.interval);
					char* args[] = {(char* ) "./bomb",(char*) interval_str.c_str() , NULL};
					execv(args[0], args);
				}else{
					//cerr << "new bomb pid: " << pid << endl;
					(bombs[bombs.size() - 1]).pid = pid;
				}
			}
			send_message((bombers[bomber_id].fd)[1], &going_msg); // Send response

			out.m = &going_msg;
			out.pid = bombers[bomber_id].pid;
			print_output(NULL,&out,NULL,NULL);

			return;
		}

		default:
			return;

	}

}


int main()
{

	cin >> map_width >> map_height >> obstacle_count >> bomber_count;
	obsd obstacle_data[obstacle_count];
	vector<bomber> bombers(bomber_count);
	vector<bomb> bombs;
	alive_bombers = bomber_count;

    read_input(obstacle_data,bombers);


	for(int i = 0; i < (int) bombers.size(); i++) PIPE(bombers[i].fd);

	pipe_count = bomber_count;


	for(int i = 0; i < (int) bombers.size(); i++)
	{
		pid_t pid = fork();
		if(pid)
		{
			bombers[i].pid = pid;
		}else
		{
			close((bombers[i].fd)[1]);
			dup2((bombers[i].fd)[0],1);
			dup2((bombers[i].fd)[0],0);
			close((bombers[i].fd)[0]);


			execv(((bombers[i]).args)[0],(bombers[i]).args);

		}
	}



	while((alive_bombers) > 0)
	{

        im bomb_msg;

        int k = bombs.size();
        struct pollfd bomb_polls[k];

        for(int i = 0; i < k; i++)
		{
			bomb_polls[i] = {(bombs[i].fd)[1], POLLIN, 0};
			if(bombs[i].alive != 1) bomb_polls[i].fd = -1;
		}

		int ret_bomb;
        if(k > 0)ret_bomb = poll(bomb_polls, k, 0);
        if (ret_bomb == -1) {
            perror("poll");
        }
        for(int i = k-1; i >= 0 ; i--){
            if((bomb_polls[i].revents & POLLIN))
            {
                if(read_data(bomb_polls[i].fd, &bomb_msg))
                {
					if(bomb_msg.type != BOMB_EXPLODE) continue;
                    bomb_id = i;


					int r = bombs[bomb_id].radius;
					int x =bombs[bomb_id].pos.x;
					int y =bombs[bomb_id].pos.y;
					od object_datas[25];

					int object_cnt = check_surroundings(x,y, r, BOMB, object_datas);

					MAP[bombs[bomb_id].pos.y][bombs[bomb_id].pos.x] -= 1;
					
					for(int m = 0 ; m < object_cnt; m++ )
					{
						if(object_datas[m].type == OBSTACLE)
						{
							for(int j = 0; j < obstacle_count ; j ++)
							{
								if((    (obstacle_data[j]).position.x == object_datas[m].position.x )
										and ((obstacle_data[j]).position.y == object_datas[m].position.y)
								)
								{
									if((obstacle_data[j]).remaining_durability != -1)(obstacle_data[j]).remaining_durability -= 1;

									if((obstacle_data[j]).remaining_durability == 0)
									{
										MAP[(obstacle_data[j]).position.y][(obstacle_data[j]).position.x] -=4; 
									} 

									obsd obstcl;

									obstcl.position.x = (obstacle_data[j]).position.x;
									obstcl.position.y = (obstacle_data[j]).position.y;
									obstcl.remaining_durability = (obstacle_data[j]).remaining_durability;
									bombs[bomb_id].damaged_obstcl.push_back(obstcl);

								}
							}
						}else if(object_datas[m].type == BOMBER){
							for(int j = 0; j < (int) bombers.size() ; j++)
							{
								if((bombers[j].pos.y == object_datas[m].position.y) and  (bombers[j].pos.x == object_datas[m].position.x) and bombers[j].alive == 1)
								{
									//int dst = abs((int) object_datas[m].position.x - (int) bombs[bomb_id].pos.x) + abs((int) object_datas[m].position.y - (int) bombs[bomb_id].pos.y);
									bombers[j].alive = -1;
									bombs[bomb_id].remarked_bombers.push_back(bombers[j]);
								}
							}
						}
					}


					if(alive_bombers == (int) bombs[bomb_id].remarked_bombers.size())
					{
						int dd = 0, dbm;
						pid_t pd =  bombs[bomb_id].remarked_bombers[0].pid;
						for(int ii = 0 ; ii < (int)  bombs[bomb_id].remarked_bombers.size(); ii++)
						{
							dbm = abs((int)  bombs[bomb_id].remarked_bombers[ii].pos.x - (int) bombs[bomb_id].pos.x) + abs((int)  bombs[bomb_id].remarked_bombers[ii].pos.y - (int) bombs[bomb_id].pos.y);
							if(dbm > dd)
							{
								dd = dbm;
								pd =  bombs[bomb_id].remarked_bombers[ii].pid;
							}
						}

						for(int jj = 0 ; jj < (int) bombers.size(); jj++)
						{
							if(pd == bombers[jj].pid)
							{
								bombers[jj].alive = 3;
								WINNER = bombers[jj].pid;
								break;
							} 
						}

						 bombs[bomb_id].remarked_bombers.clear();
					}

					bombs[bomb_id].alive = 0;

					remarked_bombs.push_back(bombs[bomb_id]);
                }else
                {
                    bomb_polls[i].fd = -1 ;
                }
            }
        }
        while(!remarked_bombs.empty())
        {
            bomb bmb= remarked_bombs.back();


			alive_bombs--;

			imp in;
			in.m = &bomb_msg;
			in.pid = bmb.pid;
			print_output(&in, NULL, NULL, NULL);
			while(!bmb.damaged_obstcl.empty())
			{
				obsd obscl = bmb.damaged_obstcl.back();
				bmb.damaged_obstcl.pop_back();
				print_output(NULL,NULL,&obscl,NULL);
			}

            int status;
            waitpid(bmb.pid, &status, 0);
            remarked_bombs.pop_back();
        };




        im bomber_msg;
        int s = bombers.size();
        struct pollfd bomber_polls[s];
        for(int i = 0; i < s; i++)
		{
			bomber_polls[i] = {(bombers[i].fd)[1], POLLIN, 0};
			if(bombers[i].alive == 0){
				(bomber_polls[i]).fd = -1;
				}
		}


        int ret_bomber = poll(bomber_polls, s, 0);
        if (ret_bomber == -1) {
            perror("poll");
        }



        for(int i = s-1 ; i >= 0; i--)
		{

            if((bomber_polls[i].revents & POLLIN))
            {

                if(read_data(bomber_polls[i].fd, &bomber_msg))
                {

					bomber_id = i;
                    imp in;
                    in.m = &bomber_msg;
                    in.pid = bombers[bomber_id].pid;

                    print_output(&in, NULL, NULL, NULL);

					if(bombers[bomber_id].pid == WINNER)
					{
						om going_msg;
						going_msg.type = BOMBER_WIN;
						bombers[bomber_id].alive = 0;
						alive_bombers -- ;
						MAP[bombers[bomber_id].pos.y][bombers[bomber_id].pos.x] -= 2;

						send_message((bombers[bomber_id].fd)[1], &going_msg);

						omp out;
						out.m = &going_msg;
						out.pid = bombers[bomber_id].pid;
						print_output(NULL,&out,NULL,NULL);

            			int status;
            			waitpid(bombers[bomber_id].pid, &status, 0);

					}

					else if(bombers[bomber_id].alive == -1)
					{
						om going_msg;
						going_msg.type = BOMBER_DIE;
						bombers[bomber_id].alive = 0;
						alive_bombers--;
						MAP[bombers[bomber_id].pos.y][bombers[bomber_id].pos.x] -= 2;

						if(alive_bombers == 1 and WINNER == -1)
						{
							for(int j = 0 ; j < (int) bombers.size() ; j ++)
							{
								if(bombers[j].alive != 0)
								{
									WINNER = bombers[j].pid;
								}

							}
						}

						omp out;

						send_message((bombers[bomber_id].fd)[1], &going_msg);

						out.m = &going_msg;
						out.pid = bombers[bomber_id].pid;
						print_output(NULL,&out,NULL,NULL);

            			int status;
            			waitpid(bombers[bomber_id].pid, &status, 0);

					}
                    else respond_message(bomber_msg,bombers,bombs); // Read and act according to the message;

                }else
                {
                    bomber_polls[i].fd = -1 ;
                }
            }
        }

		
	usleep(1000);

	}

	//wait for remaining bombs to explode and reap them

	for(int i = 0; i < int (bombs.size()) ; i++)
	{
		if(bombs[i].alive == 0) continue;
		im bomb_msg;
		bomb_msg.type = BOMB_EXPLODE;
		bombs[i].alive = 0;
		alive_bombs--;
		imp in;
		in.m = &bomb_msg;
		in.pid = bombs[i].pid;
		print_output(&in, NULL, NULL, NULL);
		int status;
		waitpid(bombs[i].pid, &status, 0);
			
	}



	for (int i = 0; i < map_height; i++) {
		free(MAP[i]);
	}
	free(MAP);


	return 0;

}


