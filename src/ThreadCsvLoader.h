#pragma once
#include "ofMain.h"
#include "ofxCsv.h"
class ThreadCsvLoader : public ofThread
{
private:
	ofHttpRequest request;
	ofBuffer buffer;

	vector<vector<string>> parseLines(ofBuffer& buffer, string separator, string comment);
public:
	ThreadCsvLoader() {

	};
	ThreadCsvLoader(string url);
	~ThreadCsvLoader();

	ofxCsv csv;
	string url;
	bool isLoaded = false;

	void threadedFunction();
	void reset();
};

