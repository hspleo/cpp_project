#include"Group.h"
#include"Stock.h"
#include"VectorOperator.h"
#include<algorithm>
#include<numeric>
#include<time.h>
using namespace std;

void BootStrap(Group& StockPool, Index& benchmark, vector<double>& AAR_, vector<double>& CAAR_)
{
	Group Sample;
	vector<int> index_(StockPool.Ticker.size());
	iota(index_.begin(), index_.end(), 0);
	srand(time(NULL));
	random_shuffle(index_.begin(), index_.end());
	for (unsigned int i = 0; i < SampleNum; i++)
	{

		map<string, Stock>::iterator itr = StockPool.Content.find(StockPool.Ticker[index_[i]]);
		if (itr != StockPool.Content.end())
			Sample.Content.insert(pair<string, Stock>(StockPool.Ticker[i], itr->second));
	}

	Sample.CalAbnormalReturn(benchmark);
	Sample.CalAAR();
	Sample.CalCAAR();
	AAR_ = AAR_ + Sample.AAR;
	CAAR_ = CAAR_ + Sample.CAAR;

}

void Group::CalAAR()
{
	Vect W(DayNum, 0);
	map<string, Stock>::iterator it;
	for (it = Content.begin(); it != Content.end(); it++)
		W = W + it->second.AbnormalReturn;
	W = W / SampleNum;
	AAR = W;
}

void Group::CalCAAR()
{
	CAAR = Cumsum(AAR);
}


void Group::CalAbnormalReturn(Index& benchmark)
{
	for (map<string, Stock>::iterator itr = Content.begin(); itr != Content.end(); )
	{
		itr->second.CalDailyReturn();
		itr->second.CalAbnormalReturn(benchmark);
		itr++;
	}

}

