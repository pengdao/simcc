#include <iostream>
#include <functional>
#include <thread>
#include <string>
#include <iomanip>
#include <stdlib.h>  
#include <stdio.h>
#include <string.h>
#include <string>
#include <assert.h>
#include <memory>

#include "test_common.h"
namespace {

typedef struct {
	int len;
	char *buf;
}mm_t;

struct MsgArg
{
	MsgArg(char* _buf, int _len)
	{
		m_.len = _len;
		m_.buf = new char[m_.len];
		memcpy(m_.buf, _buf,m_.len);
	}
	~MsgArg() 
	{
		if(m_.buf != nullptr)
		{
			free(m_.buf);
		}
	}
    mm_t m_;
};

typedef std::shared_ptr<MsgArg> MsgArgPtr;

typedef std::function<int()> Functor;

Functor fn;

int show(MsgArgPtr msg_ptr)
{
    int ret = -1;
	if (msg_ptr->m_.len > 0)
	{
        char buf[10];
        memset(buf, 1, sizeof(buf));
        ret = memcmp(buf, msg_ptr->m_.buf, msg_ptr->m_.len);   
	}
    return ret;
}

void  testA()
{
	MsgArgPtr msg_ptr;
	static int i=0;
	i++;
	char buf[10] = {0};
	memset(buf, i, sizeof(buf));
	msg_ptr.reset(new MsgArg(buf,sizeof(buf)));
	fn = std::bind(&show, msg_ptr);
	i++;
	memset(buf, i, sizeof(buf));
	msg_ptr.reset(new MsgArg(buf,sizeof(buf)));
}

void test_01()
{
    testA();
    int ret = fn();
    H_TEST_ASSERT(ret == 0);
}
}

TEST_UNIT(test_01) {
    test_01();
}