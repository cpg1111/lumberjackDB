#include <cstdint>
#include <map>
#include <vector>
#include "storage.h"

#ifndef LJ_RAFT_H_
#define LJ_RAFT_H_
    typedef struct{
        uint64_t lead;
        int state_type;
    } SoftRaftState;

    typedef struct{
        uint64_t term;
        uint64_t vote;
        uint64_t commit;
    } HardRaftState;

    typedef struct{
    } RaftMessage;

    class RaftLogger
    {
        public:
            RaftLogger(StorageBackend storage);
            ~RaftLogger();
            uint64_t get_commited();
        private:
            uint64_t commited;
    }

    class RaftManager
    {
        public:
            RaftManager();
            ~RaftManager();
            bool has_leader();
            SoftRaftState get_soft_state();
            HardRaftState get_hard_state();
            int quorum();
            std::vector<uint64_t> nodes();
            void send()
        private:
            int election_timeout;
            int heartbeat_timeout;
            RaftLogger *logger;
            uint64_t term;
            uint64_t vote;
            int state;
            std::map<uint64_t, *RaftProgess> peers;
            std::vector<RaftMessage> msgs;
    }

#endif
