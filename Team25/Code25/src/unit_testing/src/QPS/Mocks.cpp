#include "Mocks.h"

#include "QPS/Evaluator/Entity/Entity.h"

std::vector<Declaration> Mock::Declarations() {
    Declaration declaration1 = {EntityType::VARIABLE, "v"};
    Declaration declaration2 = {EntityType::ASSIGN, "a"};
    Declaration declaration3 = {EntityType::CONSTANT, "cst"};
    Declaration declaration4 = {EntityType::STATEMENT, "s"};
    Declaration declaration4_1 = {EntityType::STATEMENT, "s1"};
    Declaration declaration4_2 = {EntityType::STATEMENT, "s2"};
    Declaration declaration4_3 = {EntityType::STATEMENT, "Select"};
    Declaration declaration4_4 = {EntityType::STATEMENT, "BOOLEAN"};
    Declaration declaration5 = {EntityType::PROCEDURE, "p"};
    Declaration declaration6 = {EntityType::CALL, "c"};
    Declaration declaration7 = {EntityType::WHILE, "w"};
    Declaration declaration8 = {EntityType::PRINT, "pr"};
    Declaration declaration9 = {EntityType::READ, "r"};
    Declaration declaration10 = {EntityType::IF, "i"};
    std::vector<Declaration> declarations = {
        declaration1,   declaration2, declaration3, declaration4, declaration4_1, declaration4_2, declaration4_3,
        declaration4_4, declaration5, declaration6, declaration7, declaration8,   declaration9,   declaration10};
    return declarations;
}

bool Mock::MockPKBReader::containFollowsRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        for (const auto& [_, second] : intAbsMap.at(AbstractionType::FOLLOWS)) {
            if (std::stoi(secondArg.str) == second) {
                return true;
            }
        }
        return false;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : intAbsMap.at(AbstractionType::FOLLOWS)) {
            if (std::stoi(firstArg.str) == first) {
                return true;
            }
        }
        return false;
    }

    return intAbsMap.at(AbstractionType::FOLLOWS).count(std::pair{std::stoi(firstArg.str), std::stoi(secondArg.str)}) ==
           1;
}

bool Mock::MockPKBReader::containFollowsStarRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        for (const auto& [_, second] : intAbsMap.at(AbstractionType::FOLLOWS_T)) {
            if (std::stoi(secondArg.str) == second) {
                return true;
            }
        }
        return false;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : intAbsMap.at(AbstractionType::FOLLOWS_T)) {
            if (std::stoi(firstArg.str) == first) {
                return true;
            }
        }
        return false;
    }

    return intAbsMap.at(AbstractionType::FOLLOWS_T)
               .count(std::pair{std::stoi(firstArg.str), std::stoi(secondArg.str)}) == 1;
}

bool Mock::MockPKBReader::containParentRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        for (const auto& [_, second] : intAbsMap.at(AbstractionType::PARENTS)) {
            if (std::stoi(secondArg.str) == second) {
                return true;
            }
        }
        return false;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : intAbsMap.at(AbstractionType::PARENTS)) {
            if (std::stoi(firstArg.str) == first) {
                return true;
            }
        }
        return false;
    }

    return intAbsMap.at(AbstractionType::PARENTS).count(std::pair{std::stoi(firstArg.str), std::stoi(secondArg.str)}) ==
           1;
}

bool Mock::MockPKBReader::containParentStarRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        for (const auto& [_, second] : intAbsMap.at(AbstractionType::PARENTS_T)) {
            if (std::stoi(secondArg.str) == second) {
                return true;
            }
        }
        return false;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : intAbsMap.at(AbstractionType::PARENTS_T)) {
            if (std::stoi(firstArg.str) == first) {
                return true;
            }
        }
        return false;
    }

    return intAbsMap.at(AbstractionType::PARENTS_T)
               .count(std::pair{std::stoi(firstArg.str), std::stoi(secondArg.str)}) == 1;
}

bool Mock::MockPKBReader::containStmtUsesRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : intexprMap.at(AbstractionType::USES)) {
            if (std::stoi(firstArg.str) == first) {
                return true;
            }
        }
        return false;
    }

    return intexprMap.at(AbstractionType::USES).count(std::pair{std::stoi(firstArg.str), secondArg.str}) == 1;
}

bool Mock::MockPKBReader::containProcUsesRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : exprexprMap.at(AbstractionType::USES)) {
            if (firstArg.str == first) {
                return true;
            }
        }
        return false;
    }

    return exprexprMap.at(AbstractionType::USES).count(std::pair{firstArg.str, secondArg.str}) == 1;
}

bool Mock::MockPKBReader::containStmtModifiesRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : intexprMap.at(AbstractionType::MODIFIES)) {
            if (std::stoi(firstArg.str) == first) {
                return true;
            }
        }
        return false;
    }

    return intexprMap.at(AbstractionType::MODIFIES).count(std::pair{std::stoi(firstArg.str), secondArg.str}) == 1;
}

bool Mock::MockPKBReader::containProcModifiesRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : exprexprMap.at(AbstractionType::MODIFIES)) {
            if (firstArg.str == first) {
                return true;
            }
        }
        return false;
    }

    return exprexprMap.at(AbstractionType::MODIFIES).count(std::pair{firstArg.str, secondArg.str}) == 1;
}

bool Mock::MockPKBReader::containAssignPattern(const StmtNum stmtNum, Argument firstArg, Argument secondArg) const {
    std::unordered_map<int, PatAssignStmt> assignStoreVariable = {
        {6, {"v_x", {"(5)"}}},
        {7, {"v_y", {"(v_x)", "(v_y)", "((v_x)+(v_y))"}}},
        {8, {"v_z", {"(v_x)", "(v_y)", "(3)", "((3)*(v_y))", "((v_x)-((3)*(v_y)))"}}}};

    if (assignStoreVariable.count(stmtNum) == 0) {
        return false;
    }

    if (firstArg.type == ArgType::SYNONYM || firstArg.type == ArgType::EXPRESSION) {
        const auto& [first, _] = assignStoreVariable.at(stmtNum);
        if (first != firstArg.str) {
            return false;
        }
    }

    if (secondArg.type == ArgType::EXPRESSION || secondArg.type == ArgType::WILDCARD_EXPR) {
        const auto& [_, second] = assignStoreVariable.at(stmtNum);
        if (std::count(second.begin(), second.end(), secondArg.str) == 0) {
            return false;
        }
    }

    return true;
}

bool Mock::MockPKBReader::containIfPattern(const StmtNum stmtNum, Argument firstArg) const {
    std::unordered_map<int, std::string> ifStoreVariable = {{11, "v_x"}, {12, "v_y"}, {13, "v_z"}};

    if (ifStoreVariable.count(stmtNum) == 0) {
        return false;
    }

    if (firstArg.type == ArgType::SYNONYM || firstArg.type == ArgType::EXPRESSION) {
        const auto& first = ifStoreVariable.at(stmtNum);
        if (first != firstArg.str) {
            return false;
        }
    }

    return true;
}

bool Mock::MockPKBReader::containWhilePattern(const StmtNum stmtNum, Argument firstArg) const {
    std::unordered_map<int, std::string> whileStoreVariable = {{10, "v_x"}};

    if (whileStoreVariable.count(stmtNum) == 0) {
        return false;
    }

    if (firstArg.type == ArgType::SYNONYM || firstArg.type == ArgType::EXPRESSION) {
        const auto& first = whileStoreVariable.at(stmtNum);
        if (first != firstArg.str) {
            return false;
        }
    }

    return true;
}

bool Mock::MockPKBReader::containNextRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        for (const auto& [_, second] : intAbsMap.at(AbstractionType::NEXT)) {
            if (std::stoi(secondArg.str) == second) {
                return true;
            }
        }
        return false;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : intAbsMap.at(AbstractionType::NEXT)) {
            if (std::stoi(firstArg.str) == first) {
                return true;
            }
        }
        return false;
    }

    return intAbsMap.at(AbstractionType::NEXT).count(std::pair{std::stoi(firstArg.str), std::stoi(secondArg.str)}) == 1;
}

bool Mock::MockPKBReader::containNextStarRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        for (const auto& [_, second] : intAbsMap.at(AbstractionType::NEXT_T)) {
            if (std::stoi(secondArg.str) == second) {
                return true;
            }
        }
        return false;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : intAbsMap.at(AbstractionType::NEXT_T)) {
            if (std::stoi(firstArg.str) == first) {
                return true;
            }
        }
        return false;
    }

    return intAbsMap.at(AbstractionType::NEXT_T).count(std::pair{std::stoi(firstArg.str), std::stoi(secondArg.str)}) ==
           1;
}

bool Mock::MockPKBReader::containAffectRelation(Argument firstArg, Argument secondArg) const {
    if (firstArg.type == ArgType::WILDCARD && secondArg.type == ArgType::WILDCARD) {
        return true;
    }

    if (firstArg.type == ArgType::WILDCARD) {
        for (const auto& [_, second] : intAbsMap.at(AbstractionType::AFFECTS)) {
            if (std::stoi(secondArg.str) == second) {
                return true;
            }
        }
        return false;
    }

    if (secondArg.type == ArgType::WILDCARD) {
        for (const auto& [first, _] : intAbsMap.at(AbstractionType::AFFECTS)) {
            if (std::stoi(firstArg.str) == first) {
                return true;
            }
        }
        return false;
    }

    return intAbsMap.at(AbstractionType::AFFECTS).count(std::pair{std::stoi(firstArg.str), std::stoi(secondArg.str)}) ==
           1;
}

Procedure Mock::MockPKBReader::getProcedureCalledByStmt(StmtNum stmtNum) const {
    std::unordered_map<int, std::string> store = {{1, "p_x"}, {2, "p_x"}, {3, "p_z"}};
    return store.at(stmtNum);
}

PKBReaderEntityI::VariableSet Mock::MockPKBReader::getVarsUsedByStmt(StmtNum stmtNum) const {
    std::unordered_map<int, std::string> store = {{4, "v_y"}, {5, "v_y"}, {3, "v_z"}};
    return {store.at(stmtNum)};
}

PKBReaderEntityI::VariableSet Mock::MockPKBReader::getVarsModifiedByStmt(StmtNum stmtNum) const {
    std::unordered_map<int, std::string> store = {{4, "v_y"}, {5, "v_y"}, {3, "v_z"}};
    return {store.at(stmtNum)};
}

void Mock::CounterAction::doAction() {
    counter++;
    context.result.insert(std::to_string(counter));
}

void Mock::MockResultStrategy::write(const PKBReader& reader, Context& context) {
    context.result.insert("MOCK");
}

void Mock::MockResultStrategy::defaultWrite(Context& context) {
    context.result.insert("MOCKED");
}

bool Mock::MockResultStrategy::tryShortCircuit(const PKBReader& reader, Context& context) {
    return true;
}

bool Mock::MockFalseStrategy::execute(const PKBReader& reader, const Context& context) {
    return false;
}

bool Mock::MockTrueStrategy::execute(const PKBReader& reader, const Context& context) {
    return true;
}
