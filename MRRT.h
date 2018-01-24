#ifndef MRRT_H_H
#define MRRT_H_H

#include "map_pgm.h"
#include <vector>


struct point 
{
	int x;
	int y;
	//	std::vector<point > next;
	point(int x=0,int y=0){this->x=x;this->y=y;}
	point(const point &p){this->x=p.x;this->y=p.y;}
};

struct tree_node
{
	tree_node * father;
	point pos;
	tree_node(point pos,tree_node * parent=NULL){this->pos=pos;father=parent;}
	tree_node& operator=(const tree_node &node){this->pos=node.pos;this->father=node.father;}
};

struct RRTtree
{
	std::vector<tree_node *> graph;
};

class MRRT
{
public:
	bool getPath();
	MRRT(const char * filename,point start,point goal);
	~MRRT();
	void showResult(const char * filename);
	bool getPath_repair();
	void repair();

private:
	int getDistance(const point p1,const point p2);
	bool if_line(const point a,const point b);
	const int K;
	const int minstep;
	Pgm_map basemap;

	std::vector<point > line;

	const int minDistance;

	static const int nTree=2;


	RRTtree rrttree[nTree];

	std::vector<point> path_repair;
	std::vector<point> path;
	point start;
	point goal;
	int ** map;
	cv::Mat img;
	int sizeX,sizeY;
};

#endif