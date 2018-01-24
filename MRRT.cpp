#include "MRRT.h"
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>


void MRRT::showResult(const char * filename)
{
	using namespace cv;
	using namespace std;
	namedWindow("map");
	imshow("map",img);
	imwrite(filename,img);
	waitKey();
/*	ofstream out;

	out.open(filename,ios::out);
	if (out.is_open())
	{
		//char a;
		//in>>a;
		for (int i=0;i<path.size();i++)
		{
			out<<path[i].x<<" "<<path[i].y<<"\n";
		}


		out.close();
	}*/

}

bool MRRT::if_line(const point a,const point b)
{
	int ** walkability = map;
	line.clear();
	int dx=abs(a.x-b.x);
	int dy=abs(a.y-b.y);
	double k;
	if (dx != 0)
	{
		k=double(b.y-a.y)/double(b.x-a.x);
	}
	else if (dy ==0)
	{
		k=1;
	}
	else
	{
		k=99999;
	}

	point temp;

	if (dx>=dy)
	{
		if (a.x<b.x)
		{
			temp =a;
		}
		else 
			temp=b;
		for (int i=1;i<dx+1;i++)
		{
			int x=temp.x+i;
			int y=temp.y+k*i;
			point pt(x,y);
			line.push_back(pt);
		}
	}
	else
	{
		if (a.y<b.y)
		{
			temp =a;
		}
		else 
			temp=b;
		for (int i=1;i<dy+1;i++)
		{
			int x=temp.x+i/k;
			int y=temp.y+i;

			point pt(x,y);
			line.push_back(pt);
		}
	}
	int len=line.size();
	for (int i=0;i<len;i++)
	{
		if (1 == walkability[line[i].x][line[i].y])
		{
			return false;
		}
	}
	return true;
}

int MRRT::getDistance(const point p1,const point p2)
{
	return (int)sqrt(double((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)));
}

MRRT::MRRT(const char * filename,point start,point goal):K(10000),basemap(filename),minstep(1),minDistance(20)
{
	using namespace cv;
	
	tree_node * t1=new tree_node(start);
	tree_node * t2=new tree_node(goal);
	
	rrttree[0].graph.push_back(t1);
	rrttree[1].graph.push_back(t2);

	img= imread(filename);
	this->start=start;
	this->goal=goal;
	if (basemap.transformMapToGrid())
	{
		map=basemap.getGridMap2D();
		sizeX=basemap.getSizeX();
		sizeY=basemap.getSizeY();
	}


}

bool MRRT::getPath()
{
	using namespace std;
	using namespace cv;

	circle( img,Point(start.x,start.y), 3,  Scalar(0,0,0), 3, 1, 0 );
	circle( img,Point(goal.x,goal.y), 3,  Scalar(0,0,0), 3, 1, 0 );

	if ( getDistance(start,goal) < minDistance && if_line(start,goal))
	{
		for (int i=0;i<line.size();i++)
		{
			path.push_back(line[i]);
		}
		return true;
	}

	int i=0;
	srand(time(0));

	bool findpath=false;
	int totaldist = 0;
	while (i++ < K && !findpath)
	{
		for (int m=0;m<nTree;m++)
		{
			int x=rand()%sizeX;
			int y=rand()%sizeY;

			while(map[x][y] != 0)
			{
				x=rand()%sizeX;
				y=rand()%sizeY;
			}

			point temp(x,y);
			int flag=0;
			int dist=999999;
			point p;
			for (int i=0;i<rrttree[m].graph.size();i++)
			{
				int d=getDistance(temp,rrttree[m].graph[i]->pos);
				if (d< dist)
				{
					dist=d;
					flag=i;
				}
			}
			p.x=rrttree[m].graph[flag]->pos.x;
			p.y=rrttree[m].graph[flag]->pos.y;

			int num=9999;
			int pos=0;
			while (! if_line(p,temp) && num >minstep)
			{
				num=line.size();
				pos = rand()%num;
				num=pos;
				temp=line[pos];
			}
			num=line.size();
			if (num < minstep || ! if_line(p,temp))
			{
				continue;
			}

			if (m== 0 )
			{
				for (int i=0;i<num;i++)
				{
					circle( img,Point(line[i].x,line[i].y), 0.1,  Scalar(m*255,m*100,255), 0.1, 1, 0 );
				}
				//totaldist += num;
			}

			else
			{
				for (int i=0;i<num;i++)
				{
					circle( img,Point(line[i].x,line[i].y), 0.1,  Scalar(0,0,0), 0.1, 1, 0 );
				}
				//totaldist += num;
			}
			

			if (!findpath)
			{
				tree_node * t=new tree_node(temp,rrttree[m].graph[flag]);
				rrttree[m].graph.push_back(t);

			}
			/* more trees should rewrite here     */
			for (int n=0;n<rrttree[1-m].graph.size();n++)
			{
				if (getDistance(temp,rrttree[1-m].graph[n]->pos) < minDistance && if_line(temp,rrttree[1-m].graph[n]->pos))
				{
					for (int u=0;u<line.size();u++)
					{
						circle( img,Point(line[u].x,line[u].y), 1,  Scalar(0,0,0), 1, 1, 0 );
					}
					
					findpath = true;
					if (m==0)
					{
						//int len=rrttree[1].graph.size();
						tree_node * o = rrttree[0].graph[rrttree[0].graph.size()-1];
						tree_node * p = rrttree[1].graph[n];
						tree_node * q = p->father;


						while(q != NULL)
						{
							p->father = o;
							o=p;
							p=q;
							q=q->father;

						}

						p->father = o;

						for (tree_node * temp_= rrttree[1].graph[0];temp_ != NULL;temp_=temp_->father   )
						{
							path.push_back(temp_->pos);
						}
						for (int i=0;i<path.size()-1;i++)
						{

							cv::line(img,Point(path[i].x,path[i].y),Point(path[i+1].x,path[i+1].y),Scalar(255,0,0),2);
							totaldist += getDistance(point(path[i].x,path[i].y),point(path[i+1].x,path[i+1].y));
						}
					}

					else if (m==1)
					{
						//int len=rrttree[1].graph.size();
						tree_node * o = rrttree[0].graph[n];
						tree_node * p = rrttree[1].graph[rrttree[1].graph.size()-1];
						tree_node * q = p->father;


						while(q != NULL)
						{
							p->father = o;
							o=p;
							p=q;
							q=q->father;

						}

						p->father = o;

						for (tree_node * temp_= rrttree[1].graph[0];temp_ != NULL;temp_=temp_->father   )
						{
							path.push_back(temp_->pos);
						}
						for (int i=0;i<path.size()-1;i++)
						{

							cv::line(img,Point(path[i].x,path[i].y),Point(path[i+1].x,path[i+1].y),Scalar(255,0,0),2);
							totaldist += getDistance(point(path[i].x,path[i].y),point(path[i+1].x,path[i+1].y));
						}
					}

					std::cout << "total distance is : " << totaldist << std::endl;

					return true;
				}
			}
		}

	}
	return false;
}

MRRT ::~MRRT()
{
	for (int i=0;i<nTree;i++)
	{
		for (int j=0;j<rrttree[i].graph.size();j++)
		{
			delete rrttree[i].graph[j];
		}
	}
}

bool MRRT::getPath_repair()
{
	using namespace cv;
	if (path_repair.size()== 0)
	{
		return false;
	}
	else
	{
		for (int i=0;i<path_repair.size()-1;i++)
		{

			cv::line(img,Point(path_repair[i].x,path_repair[i].y),Point(path_repair[i+1].x,path_repair[i+1].y),Scalar(255,0,0),2);
		}
		return true;
	}

}

void MRRT::repair()
{
	if (path.size()==0)
	{
		return;
	}
	int i=0;
	path_repair.push_back(path[0]);
	while (i < (path.size()-1) )
	{
		int flag=i;
		for (int j=i+1;j<path.size();j++)
		{
			if (if_line(path[i],path[j]))
			{
				flag=j;
			}
		}
	/*	if (flag < path.size()-1)
		{
			if_line(path[flag],path[flag+1]);
			std::vector<point > temp;
			int flag2=0;
			for (int i=0;i<line.size();i++)
			{
				temp.push_back(line[i]);
			}
			for(int m=0;m<temp.size();m++)
			{
				if (if_line(path[i],temp[m]))
				{
					flag2=m;
				}
			}
			path_repair.push_back(temp[flag2]);
		}*/
		
		path_repair.push_back(path[flag]);
		i=flag;
	}
	path_repair.push_back(path[path.size()-1]);
}