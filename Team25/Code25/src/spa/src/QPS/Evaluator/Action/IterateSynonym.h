#include <utility>

#include "Action.h"

#ifndef SPA_ITERATESYNONYM_H
#define SPA_ITERATESYNONYM_H

class IterateSynonym : public Action {
    std::string synonym;

public:
    void doAction() override;
    IterateSynonym(Action& action, std::string basicString) : Action(action), synonym(std::move(basicString)){};
};

#endif // SPA_ITERATESYNONYM_H
