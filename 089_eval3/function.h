#include <string>
#include <iostream>
#include <exception>

using namespace std;

void error(string e);
class Failure: public std::exception
{
private:
    string mErrMsg;

public:
  Failure(string errMsg):mErrMsg(errMsg){}
    const char* what() const noexcept
    {
        return mErrMsg.c_str();
    }
};

//vector<Page> readEachPage(string directory);
