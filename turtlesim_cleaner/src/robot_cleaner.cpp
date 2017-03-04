#include <bits/stdc++.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>
#include <turtlesim/TeleportAbsolute.h>

using namespace std;

#define TOTAL_POINTS 10


struct co_ordinates {
	int x;
	int y;
};


int decode(int x, int y){
	static int seq_count=0, redo=0;
	int rand_x, rand_y, count = 0;
	static vector<co_ordinates> vec;
	co_ordinates temp;

	if(!redo){
		while (count != TOTAL_POINTS){
			while(1){
				int flag=0;
				rand_x = rand()%10;
				rand_y = rand()%10;
				if((rand_x == 0 || rand_x == 9) && (rand_y == 0 || rand_y == 9))
					continue;
				else{
					for(int i=0;i<vec.size(); ++i){
						if(((rand_x == vec[i].x   ) && (rand_y == vec[i].y   )) ||
						   ((rand_x == vec[i].x -1) && (rand_y == vec[i].y   )) ||
						   ((rand_x == vec[i].x +1) && (rand_y == vec[i].y   )) ||
						   ((rand_x == vec[i].x   ) && (rand_y == vec[i].y -1)) ||
						   ((rand_x == vec[i].x   ) && (rand_y == vec[i].y +1)) ||
						   ((rand_x == vec[i].x -1) && (rand_y == vec[i].y -1)) ||
						   ((rand_x == vec[i].x +1) && (rand_y == vec[i].y +1)) ||
						   ((rand_x == vec[i].x -1) && (rand_y == vec[i].y +1)) ||
						   ((rand_x == vec[i].x +1) && (rand_y == vec[i].y -1))){
							flag=1;
							break;
						}
					}
					if(!flag){
						temp.x = rand_x;
						temp.y = rand_y;
						vec.push_back(temp);
						break;
					}
					else{
						continue;
					}
				}
			}
			++count;
		}
		++redo;
	}

	for(int i=0;i<vec.size();++i){
		if(vec[i].x==x && vec[i].y==y){
			if(i==seq_count){
				++seq_count;
				return 2;
			}
			else
				return 1;
		}
	}
	return 0;
}

int main(int argc, char **argv){


	ros::init(argc, argv, "robot_cleaner");
	ros::NodeHandle nh;
    ros::ServiceClient teleport_absoluteClient=nh.serviceClient<turtlesim::TeleportAbsolute>("turtle1/teleport_absolute");
    turtlesim::TeleportAbsolute::Request req;
    turtlesim::TeleportAbsolute::Response resp;

    int t,c=0;
    bool istrue=true;
    vector< pair <int,int> > vec;

    for(int i=1;i<=10;i++){
      if(i%2!=0){
      	for(int j=0;j<=i;j++){
      		t=decode(j,i);
      		if(t==0){
                     req.x=j;
                     req.y=i;
    			     bool success=teleport_absoluteClient.call(req,resp);
                 }else if(t==1){
             	vec.push_back(make_pair(j,i));
             	for(int m=-1;m<=1;m++)
             		if(istrue)
             		for(int n=-1;n<=1;n++)
             			if(j+m>0&&i+n>0&&j+m<11&&i+n<11&&(m!=0||n!=0)){
             				req.x=j+m;
             				req.y=i+n;
             				bool success=teleport_absoluteClient.call(req,resp);
                            istrue=false;
                            break;
                        }
             		}else if(t==2){
             			c++;
             			if(c>10) return 0;
             			cout<<"Block No."<<c<<" "<<j<<","<<i<<endl;
             			istrue=true;
             			for(int m=-1;m<=1;m++)
             		         if(istrue)
             		         for(int n=-1;n<=1;n++)
             			if(j+m>0&&i+n>0&&j+m<11&&i+n<11&&(m!=0||n!=0)){
             				req.x=j+m;
             				req.y=i+n;
             				bool success=teleport_absoluteClient.call(req,resp);
                            istrue=false;
                            break;
                        }

             		}
              }

       for(int k=i-1;k>=0;k--){
           	t=decode(i,k);
      		if(t==0){
                     req.x=i;
                     req.y=k;
    			     bool success=teleport_absoluteClient.call(req,resp);
                 }else if(t==1){
             	vec.push_back(make_pair(i,k));
             	for(int m=-1;m<=1;m++)
             		if(istrue)
             		for(int n=-1;n<=1;n++)
             			if(i+m>0&&k+n>0&&i+m<11&&k+n<11&&(m!=0||n!=0)){
             				req.x=i+m;
             				req.y=k+n;
             				bool success=teleport_absoluteClient.call(req,resp);
                            istrue=false;
                            break;
                        }
             		}else if(t==2){
             			c++;
             			if(c>10) return 0;
             			cout<<"Block No. "<<c<<" "<<i<<","<<k<<endl;
             			istrue=true;
             			for(int m=-1;m<=1;m++)
             		         if(istrue)
             		         for(int n=-1;n<=1;n++)
             			if(i+m>0&&k+n>0&&i+m<11&&k+n<11&&(m!=0||n!=0)){
             				req.x=i+m;
             				req.y=k+n;
             				bool success=teleport_absoluteClient.call(req,resp);
                            istrue=false;
                            break;
                        }

             		}

       }

      }else if(i%2==0){
    		for(int j=0;j<=i;j++){                       //x=i;y=j
    				t=decode(i,j);
      		if(t==0){
                     req.x=i;
                     req.y=j;
    			     bool success=teleport_absoluteClient.call(req,resp);
                 }else if(t==1){
             	vec.push_back(make_pair(i,j));
             	for(int m=-1;m<=1;m++)
             		if(istrue)
             		for(int n=-1;n<=1;n++)
             			if(i+m>0&&j+n>0&&i+m<11&&j+n<11&&(m!=0||n!=0)){
             				req.x=i+m;
             				req.y=j+n;
             				bool success=teleport_absoluteClient.call(req,resp);
                            istrue=false;
                            break;
                        }
             		}else if(t==2){
             			c++;
             			if(c>10) return 0;
             			cout<<"Block No."<<" "<<i<<","<<j<<endl;
             			istrue=true;
             			for(int m=-1;m<=1;m++)
             		         if(istrue)
             		         for(int n=-1;n<=1;n++)
             			if(i+m>0&&j+n>0&&i+m<11&&j+n<11&&m!=0&&n!=0){
             				req.x=i+m;
             				req.y=j+n;
             				bool success=teleport_absoluteClient.call(req,resp);
                            istrue=false;
                            break;
                        }

             		}
    		}

    	for(int k=i-1;k>=0;k--){                //k,i
    	           		t=decode(k,i);
      		if(t==0){
                     req.x=k;
                     req.y=i;
    			     bool success=teleport_absoluteClient.call(req,resp);
                 }else if(t==1){
             	vec.push_back(make_pair(k,i));
             	for(int m=-1;m<=1;m++)
             		if(istrue)
             		for(int n=-1;n<=1;n++)
             			if(k+m>0&&i+n>0&&k+m<11&&i+n<11&&(m!=0||n!=0)){
             				req.x=k+m;
             				req.y=i+n;
             				bool success=teleport_absoluteClient.call(req,resp);
                            istrue=false;
                            break;
                        }
             		}else if(t==2){
             			c++;
             			if(c>10) return 0;
             			cout<<"Block No. "<<c<<" "<<k<<","<<i<<endl;
             			istrue=true;
             			for(int m=-1;m<=1;m++)
             		         if(istrue)
             		         for(int n=-1;n<=1;n++)
             			if(k+m>0&&i+n>0&&k+m<11&&i+n<11&&(m!=0||n!=0)){
             				req.x=k+m;
             				req.y=i+n;
             				bool success=teleport_absoluteClient.call(req,resp);
                            istrue=false;
                            break;
                        }

             		}

    	}
   	}

  }
       for(int l=0;l<vec.size();l++){
       	if(decode(vec[l].first,vec[l].second)==2){
       		c++;
            cout<<"Block No."<<c<<" "<<vec[l].first<<","<<vec[l].second<<endl;
            vec.erase(vec.begin()+l);
           }
       }

 return 0;
}
