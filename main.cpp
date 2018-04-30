#include "httpservice.hpp"
#include <iostream>

using namespace std;


void handle_test1(std::shared_ptr<Response> res, std::shared_ptr<Request> req){
	res->write(req->body());
}

class CLASSA {
public:
	CLASSA(){};

	void handle_test2(std::shared_ptr<Response> res, std::shared_ptr<Request> req){
		//cout << "�յ�����: name" << req->query<std::string>("name") << ", age:" << req->query<int>("age") << endl; 
		res->set_header("Content-Type", "application/json");
		res->write("{\"name\":\"button\", \"age\":100}");
	}
};

int main()
{
	TinyHTTP http(8888);
	// ���������ɺ���ע��
	http.POST("/chen/test1", handle_test1);
	// �����ó�Ա����ע��
	CLASSA testclass;
	http.GET("/chen/test2", std::bind(&CLASSA::handle_test2, &testclass, std::placeholders::_1, std::placeholders::_2));
	// ������lambdaע��
	http.GET("/chen/test3", [](std::shared_ptr<Response> res, std::shared_ptr<Request> req){
		res->write("handle test3 url request");
	});

	http.run();

	(void) getchar ();
	return 0;
}

