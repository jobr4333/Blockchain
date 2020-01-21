//
// Created by Student on 2020-01-21.
//

#ifndef JONCECHAIN_COMMIT_OR_ROLLBACK_H
#define JONCECHAIN_COMMIT_OR_ROLLBACK_H

#include <utility>
#include <functional>

class CommitOrRollback
{
    bool committed;
    std::function<void()> rollback;

public:
    CommitOrRollback(std::function<void()> &&fail_handler)
            : committed(false),
              rollback(std::move(fail_handler))
    {
    }

    void commit() noexcept { committed = true; }

    ~CommitOrRollback()
    {
        if (!committed)
            rollback();
    }
};


#endif //JONCECHAIN_COMMIT_OR_ROLLBACK_H
