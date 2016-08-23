#include "test_common.h"

#include <wcpp/exp.h>
#include <wcpp/any.h>

TEST_UNIT(testAny1) {
    std::string* buf(new std::string());
    wcpp::Any any(buf);

    std::string* b1 = wcpp::any_cast<std::string*>(any);
    H_TEST_ASSERT(buf == b1);

    delete buf;
}

TEST_UNIT(testAny2) {
    std::shared_ptr<std::string> buf(new std::string());
    wcpp::Any any(buf);

    std::shared_ptr<std::string> b1 = wcpp::any_cast<std::shared_ptr<std::string> >(any);
    H_TEST_ASSERT(buf.get() == b1.get());
}
