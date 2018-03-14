#pragma once

#include "util.h"
#include "database.h"
#include "geometry.h"
#include "Graph.h"

#define BUFFSIZE 5000000
#define threadNum 3

struct Date {
	int year, month, day;
	int hour, minute, second;
	static const int daySec = 3600 * 24;
	explicit Date(int y, int mon, int d, int h, int min, int sec) :year(y), month(mon), day(d), hour(h), minute(min), second(sec) {}
	//两个轨迹点记录时间的差值不会跨越一天

	int operator - (const Date& rhs) const {
		int s1 = hour * 3600 + minute * 60 + second;
		int s2 = rhs.hour * 3600 + rhs.minute * 60 + rhs.second;
		if (year == rhs.year && month == rhs.month && day == rhs.day)
			return abs(s1 - s2);
		else
			return abs(daySec - abs(s1 - s2));
	}
	bool operator == (const Date& rhs) const {
		return year == rhs.year && month == rhs.month && day == rhs.day && hour == rhs.hour && minute == rhs.minute && second == rhs.second;
	}
};

struct GeoPoint {
	double latitude, longitude;//纬度，经度
	Date date;//日期和时间
	GeoPoint(double lat, double lon, Date dat) :latitude(lat), longitude(lon), date(dat) {}
};

//O(nk^2mlogm+nk^2)
//n为轨迹点数
//m为路段数
//k为某个轨迹点的候选点数

/****************变量区******************/
string dbname;//数据库名称
string dbport;//数据库端口号
string dbaddr;//数据库地址
string roadTN;//道路表名称
int threadnum;//用于计算的线程数量
int top;//求最优路径时选取当前值最大的TOP个点用于下一个点的计算
double R = 0.1;//选取某轨迹点的候选点的范围，单位为Km
double Sigma = 0.02;//正态分布，单位为Km
int K = 5;//候选点最多的数量
char buffer[BUFFSIZE];

time_t tm;//计时变量
double Coef;//norm distribution coef
vector <GeoPoint> P;//轨迹点
vector < vector <Point> > candiPoint;/* 每个轨迹点的候选点集合
									 Fs是动态规划中候选点转移时空间代价，Ft是时间代价，F是总代价。F = Fs*Ft */
map < pair<int, int>, double > F;

Database *DB;//数据库连接实例
Graph *network;
/***************************************/