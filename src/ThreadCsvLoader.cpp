#include "ThreadCsvLoader.h"

vector<vector<string>> ThreadCsvLoader::parseLines(ofBuffer& buffer, string separator, string comment)
{
	auto data = vector<vector<string>>();

	int lineCount = 0;
	int maxCols = 0;
	for (auto line : buffer.getLines()) {
		if (line.empty()) {
			lineCount++;
			continue;
		}

		if (line.substr(0, comment.length()) == comment) {
			lineCount++;
			continue;
		}

		vector<string> cols = ofxCsvRow::fromString(line, separator);
		data.push_back(cols);

		if (cols.size() > maxCols) {
			maxCols = cols.size();
		}

		lineCount++;
	}

	buffer.clear();

	return data;
}

ThreadCsvLoader::ThreadCsvLoader(string url)
{

}

ThreadCsvLoader::~ThreadCsvLoader()
{

}

void ThreadCsvLoader::threadedFunction()
{
	/*
	リクエストを送信する
	パースする
	csvとして読み込む
	*/
	
	//フラグのリセット
	isLoaded = false;
	//HTTPリクエスト
	this->request.method = ofHttpRequest::Method::GET;
	this->request.url = this->url;
	//レスポンスを受け取る
	ofURLFileLoader httpHandler;
	auto response = httpHandler.handleRequest(this->request);
	this->buffer = response.data;

	//パースして読み込む
	auto data = this->parseLines(this->buffer, ",", "#");
	csv.load(data);

	isLoaded = true;
}

void ThreadCsvLoader::reset()
{
	isLoaded = false;
	csv.clear();
}
