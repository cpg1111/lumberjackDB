#include <sort>
#include "lj_raft.h"

RaftLogger::RaftLogger(StorageBackend *storage)
{

}

RaftManager::RaftManager(cpptoml::table conf)
{
    this->election_timeout = conf->get_as<int>("election_timeout").value_or(5);
    this->heartbeat_timeout = conf->get_as<int>("heartbeat_timeout").value_or(5);
    RaftLogger l(NULL);
    this->logger = &l;
    this->leader = NULL;
    this->state = 0;
}

bool RaftManager::has_leader()
{
    return this->leader != NULL;
}

SoftRaftState RaftManager::get_soft_state()
{
    SoftRaftState state;
    state.lead = this->leader;
    state.state = this->state;
    return state;
}

HardRaftState RaftManager::get_hard_state()
{
    HardRaftState state;
    state.term = this->term;
    state.vote = this->vote;
    state.commit = this->logger->get_commited();
    return state;
}

int RaftManager::quorum()
{
    return this->peers.size() / 2 + 1;
}

std::vector<uint64_t> RaftManager::nodes()
{
    std::vector<uint64_t> nodes;
    int idx = 0;
    for(std::map<uint64_t, *RaftProgess>::iterator it = this->peers.begin(); it != this->peers.end(); ++it)
    {
        nodes[idx] = it->first;
        idx++;
    }
    std::sort(nodes.begin(), nodes.end());
    return nodes;
}


