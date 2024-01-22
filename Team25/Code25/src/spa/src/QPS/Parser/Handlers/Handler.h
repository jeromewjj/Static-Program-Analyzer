#pragma once

#include <memory>
#include <vector>

#include "QPS/Clause/CondClause.h"
#include "QPS/Tokenizer/QpsToken.h"

class Handler {

protected:
    std::unique_ptr<Handler> next;

public:
    virtual ~Handler() = default;
    virtual void setNext(std::unique_ptr<Handler> handler) {
        this->next = std::move(handler);
    };
    virtual std::unique_ptr<CondClause> handle(std::vector<QpsToken>& tokens, size_t& currentIndex) = 0;
};