#if 0
#include "test_common.h"

#include <simcc/any.h>
#include <memory>

TEST_UNIT(testAny1) {
    std::string* buf(new std::string());
    simcc::Any any(buf);

    std::string* b1 = simcc::any_cast<std::string*>(any);
    H_TEST_ASSERT(buf == b1);

    delete buf;
}

TEST_UNIT(testAny2) {
    std::shared_ptr<std::string> buf(new std::string());
    simcc::Any any(buf);

    std::shared_ptr<std::string> b1 = simcc::any_cast<std::shared_ptr<std::string> >(any);
    H_TEST_ASSERT(buf.get() == b1.get());
}
#endif