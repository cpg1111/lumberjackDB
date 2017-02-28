#include <cpptoml.h>
#include <uvw/uvw.hpp>
#include "lj_raft.h"

using namespace std;

int main(int argc, char** argv)
{
    cpptoml::table conf;
    try {
        conf = cpptoml::parse_File("/etc/lumberjackdb/lumberjackd.toml");
    } catch(cpptoml:parse_exception) {
        // TODO handle conf parse exception
    }
    auto loop = uvw::Loop::getDefault();
    auto raft_mgr = RaftManager(conf);
    return 0;
}
