#if 0
#include "test_common.h"
#include "simcc/json/json.h"
#include "simcc/base64.h"
#include "simcc/timestamp.h"

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>

#include <iostream>
#include <fstream>


TEST_UNIT(testJSONObjectGetDecimal) {
    const char* s = "{\"errno\":10,\"float\":0.1}";
    simcc::json::ObjectPtr o = simcc::json::JSONParser::Load(s);
    H_TEST_ASSERT(o);
    H_TEST_ASSERT(o->IsTypeOf(simcc::json::kJSONObject));

    simcc::json::JSONObject* jo = (simcc::json::JSONObject*)(o.get());
    simcc::float64 f = jo->GetDecimal("errno");
    H_TEST_ASSERT(f == 10);

    f = jo->GetDecimal("float");
    H_TEST_ASSERT(f == 0.1);
}

TEST_UNIT(testJSONPerformanceParsing) {
/*
{
    "key": "abcd",
    "table": "1",
    "url": "http://v.youku.com/v_show/id_XMTIwODE3MTI0.html",
    "bthumb": "",
    "class": "0",
    "length": "2765",
    "src": "youku",
    "star": "������,��ɮ,����,��,����,��Դ",
    "title": "���̱�ƽ",
    "type": "ս����,������",
    "cmd": "merge",
    "foo": "1.0.0 - 2.9999.9999",
    "bar": ">=1.0.2 <2.1.2",
    "baz": ">1.0.2 <=2.3.4",
    "boo": "2.0.1",
    "qux": "<1.0.0 || >=2.3.1 <2.4.5 || >=2.5.2 <3.0.0",
    "asd": "http://asdf.com/asdf.tar.gz",
    "til": "~1.2",
    "elf": "~1.2.3",
    "two": "2.x",
    "thr": "3.3.x"
}
*/
    std::string d = simcc::Base64::Decode("ewogICAgImtleSI6ICJhYmNkIiwgCiAgICAidGFibGUiOiAiMSIsIAogICAgInVybCI6ICJodHRwOi8vdi55b3VrdS5jb20vdl9zaG93L2lkX1hNVEl3T0RFM01USTAuaHRtbCIsIAogICAgImJ0aHVtYiI6ICIiLCAKICAgICJjbGFzcyI6ICIwIiwgCiAgICAibGVuZ3RoIjogIjI3NjUiLCAKICAgICJzcmMiOiAieW91a3UiLCAKICAgICJzdGFyIjogIuWImOS9qeeQpizlvpDlg6cs546L5pawLOmprOWigyzoiJLnoJos5p2c5rqQIiwgCiAgICAidGl0bGUiOiAi54u854Of5YyX5bmzIiwgCiAgICAidHlwZSI6ICLmiJjkuonliacs6Z2p5ZG95YmnIiwgCiAgICAiY21kIjogIm1lcmdlIiwgCiAgICAiZm9vIjogIjEuMC4wIC0gMi45OTk5Ljk5OTkiLCAKICAgICJiYXIiOiAiPj0xLjAuMiA8Mi4xLjIiLCAKICAgICJiYXoiOiAiPjEuMC4yIDw9Mi4zLjQiLCAKICAgICJib28iOiAiMi4wLjEiLCAKICAgICJxdXgiOiAiPDEuMC4wIHx8ID49Mi4zLjEgPDIuNC41IHx8ID49Mi41LjIgPDMuMC4wIiwgCiAgICAiYXNkIjogImh0dHA6Ly9hc2RmLmNvbS9hc2RmLnRhci5neiIsIAogICAgInRpbCI6ICJ+MS4yIiwgCiAgICAiZWxmIjogIn4xLjIuMyIsIAogICAgInR3byI6ICIyLngiLCAKICAgICJ0aHIiOiAiMy4zLngiCn0=");

    int loop = 10000;
    simcc::Timestamp t1 = simcc::Timestamp::Now();
    for (int i = 0; i < loop; i++) {
        rapidjson::Document doc;
        doc.Parse(d.data());
    }
    simcc::Timestamp t2 = simcc::Timestamp::Now();
    for (int i = 0; i < loop; i++) {
        simcc::json::JSONObject j;
        j.Parse(d.data(), d.size());
    }
    simcc::Timestamp t3 = simcc::Timestamp::Now();
    simcc::Duration rapidjson_cost = t2 - t1;
    simcc::Duration simccjson_cost = t3 - t2;
    std::cout << ">>>>>>>>>>>>>>>>  simccjson_cost=" << simccjson_cost.Milliseconds() << "\n";
    std::cout << ">>>>>>>>>>>>>>>> rapidjson_cost=" << rapidjson_cost.Milliseconds() << "\n";
    std::cout << ">>>>>>>>>>>>>>>> simccjson_cost/rapidjson_cost=" << simccjson_cost.Seconds() / rapidjson_cost.Seconds() << "\n";
    if (simccjson_cost.Seconds() < rapidjson_cost.Seconds()) {
        std::cout << ">>>>>>>>>>>>>>>> simcc json parsing fast!\n";
    } else {
        std::cout << ">>>>>>>>>>>>>>>> rapidjson parsing fast!\n";
    }
}


TEST_UNIT(testJSONPerformanceGet) {
/*
{
    "key": "abcd",
    "table": "1",
    "url": "http://v.youku.com/v_show/id_XMTIwODE3MTI0.html",
    "bthumb": "",
    "class": "0",
    "length": "2765",
    "src": "youku",
    "star": "������,��ɮ,����,��,����,��Դ",
    "title": "���̱�ƽ",
    "type": "ս����,������",
    "cmd": "merge",
    "foo": "1.0.0 - 2.9999.9999",
    "bar": ">=1.0.2 <2.1.2",
    "baz": ">1.0.2 <=2.3.4",
    "boo": "2.0.1",
    "qux": "<1.0.0 || >=2.3.1 <2.4.5 || >=2.5.2 <3.0.0",
    "asd": "http://asdf.com/asdf.tar.gz",
    "til": "~1.2",
    "elf": "~1.2.3",
    "two": "2.x",
    "thr": "3.3.x"
}
*/
    std::string key = "key";
    std::string table = "table";
    std::string url = "url";
    std::string bthumb = "bthumb";
    std::string length = "length";
    std::string src = "src";
    std::string star = "star";
    std::string title = "title";
    std::string type = "type";
    std::string cmd = "cmd";
    std::string foo = "foo";
    std::string bar = "bar";
    std::string baz = "baz";
    std::string boo = "boo";
    std::string qux = "qux";
    std::string asd = "asd";
    std::string til = "til";
    std::string elf = "elf";
    std::string two = "two";
    std::string thr = "thr";

    std::string d = simcc::Base64::Decode("ewogICAgImtleSI6ICJhYmNkIiwgCiAgICAidGFibGUiOiAiMSIsIAogICAgInVybCI6ICJodHRwOi8vdi55b3VrdS5jb20vdl9zaG93L2lkX1hNVEl3T0RFM01USTAuaHRtbCIsIAogICAgImJ0aHVtYiI6ICIiLCAKICAgICJjbGFzcyI6ICIwIiwgCiAgICAibGVuZ3RoIjogIjI3NjUiLCAKICAgICJzcmMiOiAieW91a3UiLCAKICAgICJzdGFyIjogIuWImOS9qeeQpizlvpDlg6cs546L5pawLOmprOWigyzoiJLnoJos5p2c5rqQIiwgCiAgICAidGl0bGUiOiAi54u854Of5YyX5bmzIiwgCiAgICAidHlwZSI6ICLmiJjkuonliacs6Z2p5ZG95YmnIiwgCiAgICAiY21kIjogIm1lcmdlIiwgCiAgICAiZm9vIjogIjEuMC4wIC0gMi45OTk5Ljk5OTkiLCAKICAgICJiYXIiOiAiPj0xLjAuMiA8Mi4xLjIiLCAKICAgICJiYXoiOiAiPjEuMC4yIDw9Mi4zLjQiLCAKICAgICJib28iOiAiMi4wLjEiLCAKICAgICJxdXgiOiAiPDEuMC4wIHx8ID49Mi4zLjEgPDIuNC41IHx8ID49Mi41LjIgPDMuMC4wIiwgCiAgICAiYXNkIjogImh0dHA6Ly9hc2RmLmNvbS9hc2RmLnRhci5neiIsIAogICAgInRpbCI6ICJ+MS4yIiwgCiAgICAiZWxmIjogIn4xLjIuMyIsIAogICAgInR3byI6ICIyLngiLCAKICAgICJ0aHIiOiAiMy4zLngiCn0=");
    std::string val;

    rapidjson::Document doc;
    doc.Parse(d.data());
    int loop = 10000;
    simcc::Timestamp t1 = simcc::Timestamp::Now();
    for (int i = 0; i < loop; i++) {
        val = doc[key].GetString();
        val = doc[table].GetString();
        val = doc[url].GetString();
        val = doc[bthumb].GetString();
        val = doc[length].GetString();
        val = doc[src].GetString();
        val = doc[star].GetString();
        val = doc[title].GetString();
        val = doc[type].GetString();
        val = doc[cmd].GetString();
        val = doc[foo].GetString();
        val = doc[bar].GetString();
        val = doc[baz].GetString();
        val = doc[boo].GetString();
        val = doc[qux].GetString();
        val = doc[asd].GetString();
        val = doc[til].GetString();
        val = doc[elf].GetString();
        val = doc[two].GetString();
        val = doc[thr].GetString();
    }
    simcc::Timestamp t2 = simcc::Timestamp::Now();

    simcc::json::JSONObject j;
    j.Parse(d.data(), d.size());
    for (int i = 0; i < loop; i++) {
        val = j.GetString(key);
        val = j.GetString(table);
        val = j.GetString(url);
        val = j.GetString(bthumb);
        val = j.GetString(length);
        val = j.GetString(src);
        val = j.GetString(star);
        val = j.GetString(title);
        val = j.GetString(type);
        val = j.GetString(cmd);
        val = j.GetString(foo);
        val = j.GetString(bar);
        val = j.GetString(baz);
        val = j.GetString(boo);
        val = j.GetString(qux);
        val = j.GetString(asd);
        val = j.GetString(til);
        val = j.GetString(elf);
        val = j.GetString(two);
        val = j.GetString(thr);
    }
    simcc::Timestamp t3 = simcc::Timestamp::Now();
    simcc::Duration rapidjson_cost = t2 - t1;
    simcc::Duration simccjson_cost = t3 - t2;
    std::cout << ">>>>>>>>>>>>>>>>  simccjson_cost=" << simccjson_cost.Milliseconds() << "\n";
    std::cout << ">>>>>>>>>>>>>>>> rapidjson_cost=" << rapidjson_cost.Milliseconds() << "\n";
    std::cout << ">>>>>>>>>>>>>>>> simccjson_cost/rapidjson_cost=" << simccjson_cost.Seconds() / rapidjson_cost.Seconds() << "\n";
    if (simccjson_cost.Seconds() < rapidjson_cost.Seconds()) {
        std::cout << ">>>>>>>>>>>>>>>> simcc json GetString fast!\n";
    } else {
        std::cout << ">>>>>>>>>>>>>>>> rapidjson GetString fast!\n";
    }
}



TEST_UNIT(testJSONPerformanceSerialize) {
/*
{
    "key": "abcd",
    "table": "1",
    "url": "http://v.youku.com/v_show/id_XMTIwODE3MTI0.html",
    "bthumb": "",
    "class": "0",
    "length": "2765",
    "src": "youku",
    "star": "������,��ɮ,����,��,����,��Դ",
    "title": "���̱�ƽ",
    "type": "ս����,������",
    "cmd": "merge",
    "foo": "1.0.0 - 2.9999.9999",
    "bar": ">=1.0.2 <2.1.2",
    "baz": ">1.0.2 <=2.3.4",
    "boo": "2.0.1",
    "qux": "<1.0.0 || >=2.3.1 <2.4.5 || >=2.5.2 <3.0.0",
    "asd": "http://asdf.com/asdf.tar.gz",
    "til": "~1.2",
    "elf": "~1.2.3",
    "two": "2.x",
    "thr": "3.3.x"
}
*/
    std::string d = simcc::Base64::Decode("ewogICAgImtleSI6ICJhYmNkIiwgCiAgICAidGFibGUiOiAiMSIsIAogICAgInVybCI6ICJodHRwOi8vdi55b3VrdS5jb20vdl9zaG93L2lkX1hNVEl3T0RFM01USTAuaHRtbCIsIAogICAgImJ0aHVtYiI6ICIiLCAKICAgICJjbGFzcyI6ICIwIiwgCiAgICAibGVuZ3RoIjogIjI3NjUiLCAKICAgICJzcmMiOiAieW91a3UiLCAKICAgICJzdGFyIjogIuWImOS9qeeQpizlvpDlg6cs546L5pawLOmprOWigyzoiJLnoJos5p2c5rqQIiwgCiAgICAidGl0bGUiOiAi54u854Of5YyX5bmzIiwgCiAgICAidHlwZSI6ICLmiJjkuonliacs6Z2p5ZG95YmnIiwgCiAgICAiY21kIjogIm1lcmdlIiwgCiAgICAiZm9vIjogIjEuMC4wIC0gMi45OTk5Ljk5OTkiLCAKICAgICJiYXIiOiAiPj0xLjAuMiA8Mi4xLjIiLCAKICAgICJiYXoiOiAiPjEuMC4yIDw9Mi4zLjQiLCAKICAgICJib28iOiAiMi4wLjEiLCAKICAgICJxdXgiOiAiPDEuMC4wIHx8ID49Mi4zLjEgPDIuNC41IHx8ID49Mi41LjIgPDMuMC4wIiwgCiAgICAiYXNkIjogImh0dHA6Ly9hc2RmLmNvbS9hc2RmLnRhci5neiIsIAogICAgInRpbCI6ICJ+MS4yIiwgCiAgICAiZWxmIjogIn4xLjIuMyIsIAogICAgInR3byI6ICIyLngiLCAKICAgICJ0aHIiOiAiMy4zLngiCn0=");
    std::string val;

    rapidjson::Document doc;
    doc.Parse(d.data());
    int loop = 10000;
    simcc::Timestamp t1 = simcc::Timestamp::Now();
    for (int i = 0; i < loop; i++) {
        using namespace rapidjson;
        GenericStringBuffer<UTF8<>, MemoryPoolAllocator<> > buf;
        Writer< GenericStringBuffer<UTF8<>, MemoryPoolAllocator<> > > writer(buf);
        doc.Accept(writer);
    }
    simcc::Timestamp t2 = simcc::Timestamp::Now();

    simcc::json::JSONObject j;
    j.Parse(d.data(), d.size());
    for (int i = 0; i < loop; i++) {
        simcc::DataStream buf(768);
        j.ToStringBuf(buf);
    }
    simcc::Timestamp t3 = simcc::Timestamp::Now();
    simcc::Duration rapidjson_cost = t2 - t1;
    simcc::Duration simccjson_cost = t3 - t2;
    std::cout << ">>>>>>>>>>>>>>>>  simccjson_cost=" << simccjson_cost.Milliseconds() << "\n";
    std::cout << ">>>>>>>>>>>>>>>> rapidjson_cost=" << rapidjson_cost.Milliseconds() << "\n";
    std::cout << ">>>>>>>>>>>>>>>> simccjson_cost/rapidjson_cost=" << simccjson_cost.Seconds() / rapidjson_cost.Seconds() << "\n";
    if (simccjson_cost.Seconds() < rapidjson_cost.Seconds()) {
        std::cout << ">>>>>>>>>>>>>>>> simcc json Serialize fast!\n";
    } else {
        std::cout << ">>>>>>>>>>>>>>>> rapidjson Serialize fast!\n";
    }
}
#endif