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
	//�����켣���¼ʱ��Ĳ�ֵ�����Խһ��

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
	double latitude, longitude;//γ�ȣ�����
	Date date;//���ں�ʱ��
	GeoPoint(double lat, double lon, Date dat) :latitude(lat), longitude(lon), date(dat) {}
};

//O(nk^2mlogm+nk^2)
//nΪ�켣����
//mΪ·����
//kΪĳ���켣��ĺ�ѡ����

/****************������******************/
string dbname;//���ݿ�����
string dbport;//���ݿ�˿ں�
string dbaddr;//���ݿ��ַ
string roadTN;//��·������
int threadnum;//���ڼ�����߳�����
int top;//������·��ʱѡȡ��ǰֵ����TOP����������һ����ļ���
double R = 0.1;//ѡȡĳ�켣��ĺ�ѡ��ķ�Χ����λΪKm
double Sigma = 0.02;//��̬�ֲ�����λΪKm
int K = 5;//��ѡ����������
char buffer[BUFFSIZE];

time_t tm;//��ʱ����
double Coef;//norm distribution coef
vector <GeoPoint> P;//�켣��
vector < vector <Point> > candiPoint;/* ÿ���켣��ĺ�ѡ�㼯��
									 Fs�Ƕ�̬�滮�к�ѡ��ת��ʱ�ռ���ۣ�Ft��ʱ����ۣ�F���ܴ��ۡ�F = Fs*Ft */
map < pair<int, int>, double > F;

Database *DB;//���ݿ�����ʵ��
Graph *network;
/***************************************/