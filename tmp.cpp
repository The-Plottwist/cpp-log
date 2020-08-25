#include <thread>
#include "Log.h"

Log lg{"Experiment.log", "LOG", Log::LEVEL::WARNING, Log::LEVEL::DEBUG};

void test (const float &f) {

    lg.debug("Float: ", f);
    lg.info("Float: ", f);
    lg.error("Float: ", f);
    lg.warning("Float: ", f);
    lg.critical("Float: ", f);
}

int main () {

    int i{15123123};
    float f{1098.688};

    std::thread threads[5];
    
    for (auto &th : threads) th = std::thread(test, f);
    for (auto &th : threads) th.join();
  
    return 0;
 }