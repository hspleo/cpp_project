#pragma once
#ifndef Stock_h
#define Stock_h

#include<string>
#include<vector>
#include<map>
#include<iostream>
#include"ExcelDriver\ExcelDriver.hpp"
#include"ExcelDriver\stdafx.h"
#include"ExcelDriver\BitsAndPieces\StringConversions.hpp"
#include"ExcelDriver\ExcelMechanisms.hpp"
#include"ExcelDriver\VectorsAndMatrices\NumericMatrix.cpp"
#include"ExcelDriver\ExceptionClasses\DatasimException.hpp"

#define DayNum 91
#define SPYRange 357

using namespace std;

class Index
{
protected:
	string Ticker;
	string StartTime;
	string EndTime;


public:
	vector<string> Date;
	vector<double> Price;
	vector<double> DailyReturn;

	Index() : Ticker("0"), StartTime("0"), EndTime("0") {}
	Index(string ticker, string startdate, string enddate) :Ticker(ticker), StartTime(startdate), EndTime(enddate) {}

	void CalDailyReturn();

	void SetTicker(string name);
	void SetStartTime(char* source);
	void SetEndTime(char* source);
	
	string GetTicker() const;
	string GetStartTime() const;
	string GetEndTime() const;
};

class Stock : public Index
{

public:
	string Est_EPS;
	string Act_EPS;
	string Act_to_Est;
	vector<double> AbnormalReturn;

	Stock() :Index() { Act_EPS = "0"; Est_EPS = "0"; Act_to_Est = "0"; }
	Stock(string ticker, string startdate, string enddate, string act_eps, string est_eps, string act_to_est)
		:Index(ticker, startdate, enddate) { Act_EPS = act_eps; Est_EPS = est_eps; Act_to_Est = act_to_est; }

	void ExportData() const;

	int check() const;

	void CalAbnormalReturn(Index& benchmark);

	friend ostream& operator<<(ostream& os, const Stock& source);
};
#endif