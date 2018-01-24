#ifndef MAP_PGM_H_H
#define MAP_PGM_H_H

#include <iostream>
#include <opencv2/opencv.hpp>

/*
// 
// MRRT map1("分支/1.pgm",point(223,225),point(628,623));
//long tb=clock();
//map1.createTree();
bool ok= map1.getPath();
map1.repair();
//long te=clock();
//std::cout<<tb-t<<"ms create map,"<<te-tb<<"ms find path,"<<std::endl;
map1.showResult(n[i][0]);

MRRT map2("分支/2.pgm",point(594,483),point(394,183));
//	map2.createTree();
map2.getPath();
map2.repair();
map2.showResult(n[i][1]);

MRRT map3("分支/3.pgm",point(580,493),point(228,172));
//	map3.createTree();
map3.getPath();
map3.repair();
map3.showResult(n[i][2]);

MRRT map4("分支/4.pgm",point(580,155),point(266,719));
//	map4.createTree();
map4.getPath();
map4.repair();
map4.showResult(n[i][3]);

MRRT map5("分支/5.pgm",point(101,82),point(577,627));
//	map5.createTree();
map5.getPath();
map5.repair();
map5.showResult(n[i][4]);


MRRT map6("分支/6.pgm",point(605,365),point(151,119));
//map6.createTree();
map6.getPath();
map6.repair();
map6.showResult(n[i][5]);


MRRT map7("分支/7.pgm",point(167,101),point(163,743));
//	map7.createTree();
map7.getPath();
map7.repair();
map7.showResult(n[i][6]);

MRRT map8("分支/8.pgm",point(351,684),point(265,55));
//	map8.createTree();
map8.getPath();
map8.repair();
map8.showResult(n[i][7]);

MRRT map9("分支/9.pgm",point(206,509),point(601,89));
//	map9.createTree();
map9.getPath();
map9.repair();
map9.showResult(n[i][8]);

MRRT map10("分支/10.pgm",point(82,749),point(722,131));
//	map10.createTree();
map10.getPath();
map10.repair();
map10.showResult(n[i][9]);

// 
*/



class Pgm_map
{
public:
	int ** getGridMap2D();
	Pgm_map(const char * filename);
	bool transformMapToGrid();
	const int getSizeX();
	const int getSizeY();
	cv::Mat getImg();
	~Pgm_map();
private:
	bool isopen;
	cv::Mat	basemap;
	int ** gridmap2D;
	int sizeX;
	int sizeY;
	const Pgm_map & operator=(const Pgm_map &);	//must exist but not use
};


#endif