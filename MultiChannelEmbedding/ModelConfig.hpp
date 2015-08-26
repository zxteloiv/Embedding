#pragma once
#include "Import.hpp"

class Dataset
{
public:
	const string&	base_dir;
	const string&	training;
	const string&	developing;
	const string&	testing;
	const bool&	self_false_sampling;

public:
	Dataset(const string& base_dir,
		const string& training,
		const string& developing,
		const string& testing,
		const bool& self_false_sampling)
		:base_dir(base_dir),
		training(training),
		developing(developing),
		testing(testing),
		self_false_sampling(self_false_sampling)
	{
		;
	}
};

enum TaskType
{
	LinkPredictionHead,
	LinkPredictionTail, 
	TripletClassification
};

class ModelLogging
{
protected:
	ofstream fout;

public:
	ModelLogging(const string& base_dir)
	{
		const time_t log_time = time(nullptr);
		struct tm* current_time = localtime(&log_time);
		stringstream ss;
		ss<<1900 + current_time->tm_year<<"-";
		ss<<setfill('0')<<setw(2)<<current_time->tm_mon + 1<<"-";
		ss<<setfill('0')<<setw(2)<<current_time->tm_mday<<" ";
		ss<<setfill('0')<<setw(2)<<current_time->tm_hour<<".";
		ss<<setfill('0')<<setw(2)<<current_time->tm_min<<".";
		ss<<setfill('0')<<setw(2)<<current_time->tm_sec;

		fout.open((base_dir + ss.str() + ".log").c_str());
		fout<<'['<<ss.str()<<']'<<'\t'<<"Starting...";
	}

	ModelLogging& record()
	{
		const time_t log_time = time(nullptr);
		struct tm* current_time = localtime(&log_time);
		stringstream ss;
		ss<<1900 + current_time->tm_year<<"-";
		ss<<setfill('0')<<setw(2)<<current_time->tm_mon + 1<<"-";
		ss<<setfill('0')<<setw(2)<<current_time->tm_mday<<" ";
		ss<<setfill('0')<<setw(2)<<current_time->tm_hour<<".";
		ss<<setfill('0')<<setw(2)<<current_time->tm_min<<".";

		fout<<endl;
		fout<<'['<<ss.str()<<']'<<'\t';
		
		return *this;
	}

	template<typename T>
	ModelLogging& operator << (T things)
	{
		fout<<things;
		return *this;
	}

	~ModelLogging()
	{
		fout.close();
	}
};