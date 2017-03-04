#include <bits/stdc++.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/Spawn.h>

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


    ros::init(argc, argv, "robo3");

    ros::NodeHandle n;
 
    ros::ServiceClient Client=n.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn::Request reqq;
    turtlesim::Spawn::Response respp;
    reqq.x=10;
    reqq.y=10;
    reqq.theta=3.14/2;
    reqq.name="shubham";
    bool successs=Client.call(reqq,respp);



    ros::ServiceClient Clients=n.serviceClient<turtlesim::TeleportAbsolute>("shubham/teleport_absolute");
    turtlesim::TeleportAbsolute::Request reqv;
    turtlesim::TeleportAbsolute::Response respv;


    int t,c=0;
    bool istrue=true;
    vector< pair <int,int> > vec;

  for(int i=9;i>=5;i--){
      if(i%2!=0){
        for(int j=10;j>=i;j--){
            t=decode(i,j);
            if(t==0){
                     reqv.y=j;
                     reqv.x=i;
                     successs=Clients.call(reqv,respv);
                 }else if(t==1){
                vec.push_back(make_pair(i,j));
                for(int m=-1;m<=1;m++)
                    if(istrue)
                    for(int n=-1;n<=1;n++)
                        if(i+m>0&&j+n>0&&i+m<11&&j+n<11&&(m!=0||n!=0)){
                             reqv.y=j+n;
                             reqv.x=i+m;
                             successs=Clients.call(reqv,respv);
                             istrue=false;
                             break;
                        }
                    }else if(t==2){
                        c++;
                        if(c>10) return 0;
                        cout<<"Block No."<<c<<" "<<i<<","<<j<<endl;
                        istrue=true;
                        for(int m=-1;m<=1;m++)
                             if(istrue)
                             for(int n=-1;n<=1;n++)
                        if(i+m>0&&j+n>0&&i+m<11&&j+n<11&&(m!=0||n!=0)){
                             reqv.y=j+n;
                             reqv.x=i+m;
                             successs=Clients.call(reqv,respv);
                            istrue=false;
                            break;
                        }

                    }
              }
                
       for(int k=i+1;k<=10;k++){
            t=decode(k,i);
            if(t==0){
                     reqv.y=i;
                     reqv.x=k;
                     successs=Clients.call(reqv,respv);
                 }else if(t==1){
                vec.push_back(make_pair(k,i));
                for(int m=-1;m<=1;m++)
                    if(istrue)
                    for(int n=-1;n<=1;n++)
                        if(k+m>0&&i+n>0&&k+m<11&&i+n<11&&(m!=0||n!=0)){
                           reqv.x=k+m;
                           reqv.y=i+n;
                            successs=Clients.call(reqv,respv);
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
                            reqv.x=k+m;
                            reqv.y=i+n;
                            successs=Clients.call(reqv,respv);
                            istrue=false;
                            break;
                        }

                    }

       }

      }else if(i%2==0){
            for(int j=10;j>=i;j--){                       //x=i;y=j
                    t=0;
            if(t==decode(j,i)){
                     reqv.y=i;
                     reqv.x=j;
                     successs=Clients.call(reqv,respv);
                 }else if(t==1){
                vec.push_back(make_pair(j,i));
                for(int m=-1;m<=1;m++)
                    if(istrue)
                    for(int n=-1;n<=1;n++)
                        if(j+m>0&&i+n>0&&j+m<11&&i+n<11&&(m!=0||n!=0)){
                            reqv.x=j+m;
                            reqv.y=i+n;
                            successs=Clients.call(reqv,respv);
                            istrue=false;
                            break;
                        }
                    }else if(t==2){
                        c++;
                        if(c>10) return 0;
                        cout<<"Block No."<<" "<<j<<","<<i<<endl;
                        istrue=true;
                        for(int m=-1;m<=1;m++)
                             if(istrue)
                             for(int n=-1;n<=1;n++)
                        if(j+m>0&&i+n>0&&j+m<11&&i+n<11&&m!=0&&n!=0){
                            reqv.x=j+m;
                            reqv.y=i+n;
                            successs=Clients.call(reqv,respv);
                            istrue=false;
                            break;
                        }

                    }
            }           
                
        for(int k=i+1;k<=10;k++){                
                        t=decode(i,k);
            if(t==0){
                           reqv.y=k;
                            reqv.x=i;
                            successs=Clients.call(reqv,respv);
                 }else if(t==1){
                vec.push_back(make_pair(i,k));
                for(int m=-1;m<=1;m++)
                    if(istrue)
                    for(int n=-1;n<=1;n++)
                        if(i+m>0&&k+n>0&&i+m<11&&k+n<11&&(m!=0||n!=0)){
                            reqv.y=k+n;
                            reqv.x=i+m;
                            successs=Clients.call(reqv,respv);
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
                            reqv.x=i+m;
                            reqv.y=k+n;
                            successs=Clients.call(reqv,respv);
                            istrue=false;
                            break;
                        }

                    }

        }
    }

  }

   return 0;
}
      






