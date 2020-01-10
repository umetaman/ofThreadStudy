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
	���N�G�X�g�𑗐M����
	�p�[�X����
	csv�Ƃ��ēǂݍ���
	*/
	
	//�t���O�̃��Z�b�g
	isLoaded = false;
	//HTTP���N�G�X�g
	this->request.method = ofHttpRequest::Method::GET;
	this->request.url = this->url;
	//���X�|���X���󂯎��
	ofURLFileLoader httpHandler;
	auto response = httpHandler.handleRequest(this->request);
	this->buffer = response.data;

	//�p�[�X���ēǂݍ���
	auto data = this->parseLines(this->buffer, ",", "#");
	csv.load(data);

	isLoaded = true;
}

void ThreadCsvLoader::reset()
{
	isLoaded = false;
	csv.clear();
}
