#include <algorithm>

#include "QPS/Clause/CondClause.h"
#include "QPS/Optimiser/Optimiser.h"
#include "catch.hpp"

class DummyCondClause : public CondClause {
public:
    explicit DummyCondClause(const std::vector<std::string>& synonyms) : synonyms_(synonyms) {}

    std::vector<std::string> getSynonyms() override {
        return synonyms_;
    }

private:
    std::vector<std::string> synonyms_;
};

TEST_CASE("Test Optimise") {
    std::vector<CondClause*> clauses;

    // Create some DummyCondClause objects with different synonym lengths
    clauses.push_back(new DummyCondClause({"apple", "banana"}));       // Length: 2
    clauses.push_back(new DummyCondClause({"cherry", "date", "fig"})); // Length: 3
    clauses.push_back(new DummyCondClause({"grapefruit"}));            // Length: 1

    // Call the Optimise method to sort the clauses
    Optimiser::Optimise(clauses);

    // Check if the clauses are sorted in ascending order of synonym length
    REQUIRE(clauses.size() == 3);
    REQUIRE(clauses[0]->getSynonyms().size() == 1); // Smallest synonym length
    REQUIRE(clauses[1]->getSynonyms().size() == 2);
    REQUIRE(clauses[2]->getSynonyms().size() == 3); // Largest synonym length
}

TEST_CASE("Test sortCondClausesBySynonymLength") {
    std::vector<CondClause*> clauses;

    // Create some DummyCondClause objects with different synonym lengths
    clauses.push_back(new DummyCondClause({"apple", "banana"}));       // Length: 2
    clauses.push_back(new DummyCondClause({"cherry", "date", "fig"})); // Length: 3
    clauses.push_back(new DummyCondClause({"grapefruit"}));            // Length: 1

    // Call the sortCondClausesBySynonymLength method to sort the clauses
    Optimiser::sortCondClausesBySynonymLength(clauses);

    // Check if the clauses are sorted in ascending order of synonym length
    REQUIRE(clauses.size() == 3);
    REQUIRE(clauses[0]->getSynonyms().size() == 1); // Smallest synonym length
    REQUIRE(clauses[1]->getSynonyms().size() == 2);
    REQUIRE(clauses[2]->getSynonyms().size() == 3); // Largest synonym length
}
