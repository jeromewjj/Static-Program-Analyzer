#include "../Mocks.h"
#include "QPS/Evaluator/Entity/Entity.h"
#include "QPS/Parser/QpsParser.h"
#include "catch.hpp"

QpsParser parser;

TEST_CASE("Parsing Query") {
    SECTION("ResultCl") {
        SECTION("One Elem Tuple: AttrRef") {
            std::string query = R"(stmt s; constant c;
            Select s.stmt# with s.stmt# = c.value)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 2);
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s.stmt#");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::ATTRREF);
        }

        SECTION("Multi Elems Tuple: AttrRef & Syn") {
            std::string query = R"(stmt s; constant c; assign a2;
            Select <s.stmt#, a2> with s.stmt# = c.value)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 3);
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s.stmt#");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::ATTRREF);
            REQUIRE(tuplePtr->getTupleItems()[1].getStr() == "a2");
            REQUIRE(tuplePtr->getTupleItems()[1].getType() == ArgType::SYNONYM);
        }

        SECTION("BOOLEAN") {
            std::string query = R"(Select BOOLEAN such that Next* (2, 9))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 0);
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::BOOLEAN);
            REQUIRE(result.selClause.argument->getStr() == "BOOLEAN");
        }

        SECTION("BOOLEAN with BOOLEAN declaration") {
            std::string query = R"(stmt BOOLEAN; Select BOOLEAN such that Next* (2, 9))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);
            REQUIRE(result.selClause.argument->getStr() == "BOOLEAN");
        }
    }

    SECTION("with clause") {
        SECTION("Valid parsing of with clause") {
            std::string query = R"(stmt s; constant c;
            Select s with s.stmt# = c.value)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 2);
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid parsing of with clause with not") {
            std::string query = R"(stmt s; constant c;
            Select s with not 12 = 12)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 2);
            REQUIRE(result.clauses.size() == 1);
            REQUIRE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid parsing of with clause without attrRef") {
            std::string query = R"(stmt s; constant c;
            Select s with 12 = 12)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 2);
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid parsing of with clause and such that clause") {
            std::string query = R"(procedure p, q;
            Select p such that Calls (p, q) with q.procName = "Third" such that Modifies (p, "i"))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 2);
            REQUIRE(result.clauses.size() == 3);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE_FALSE(result.clauses[2]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "p");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid parsing of with clause and pattern clause") {
            std::string query = R"(assign a; while w; stmt s;
            Select a pattern a("x", _) with a.stmt# = s.stmt#)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 3);
            REQUIRE(result.clauses.size() == 2);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid parsing of multiple with clause") {
            std::string query = R"(assign a; while w; stmt s;
            Select a with a.stmt# = s.stmt# and w.stmt# = 2)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 3);
            REQUIRE(result.clauses.size() == 2);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }
    }

    SECTION("No Clauses") {
        SECTION("Valid multiple Declarations with multiple Declaration types With Select Synonym") {
            std::string query = R"(
		    procedure pr, p;
            assign a;
		    Select pr)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 3);
            REQUIRE(result.declarations[0].entityType == EntityType::PROCEDURE);
            REQUIRE(result.declarations[0].synonym == "pr");
            REQUIRE(result.declarations[1].entityType == EntityType::PROCEDURE);
            REQUIRE(result.declarations[1].synonym == "p");
            REQUIRE(result.declarations[2].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[2].synonym == "a");
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "pr");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid Stmt Declaration With Select Synonym") {
            std::string query = R"(
		    procedure pr;
		    Select pr)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::PROCEDURE);
            REQUIRE(result.declarations[0].synonym == "pr");
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "pr");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid Stmt Declaration") {
            std::string query = R"(stmt s; Select s)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::STATEMENT);
            REQUIRE(result.declarations[0].synonym == "s");
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid Multiple Declarations") {
            std::string query = R"(stmt s; print p; variable v; Select p)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 3);
            REQUIRE(result.declarations[0].entityType == EntityType::STATEMENT);
            REQUIRE(result.declarations[0].synonym == "s");
            REQUIRE(result.declarations[1].entityType == EntityType::PRINT);
            REQUIRE(result.declarations[1].synonym == "p");
            REQUIRE(result.declarations[2].entityType == EntityType::VARIABLE);
            REQUIRE(result.declarations[2].synonym == "v");
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "p");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }
    }

    SECTION("such that clause") {
        SECTION("Valid Such That Clause") {
            std::string query = R"(stmt s; Select s such that Modifies(s, _))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::STATEMENT);
            REQUIRE(result.declarations[0].synonym == "s");
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid Such That Clause with 'not'") {
            std::string query = R"(stmt s; Select s such that not Modifies(s, _))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::STATEMENT);
            REQUIRE(result.declarations[0].synonym == "s");
            REQUIRE(result.clauses.size() == 1);
            REQUIRE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid Such That Clause with multi declaration") {
            std::string query = R"(
                stmt s1, s2;
                Select s1 such that Follows(s1, s2))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 2);
            REQUIRE(result.declarations[0].entityType == EntityType::STATEMENT);
            REQUIRE(result.declarations[0].synonym == "s1");
            REQUIRE(result.declarations[1].entityType == EntityType::STATEMENT);
            REQUIRE(result.declarations[1].synonym == "s2");
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s1");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid Such That Clause with and") {
            std::string query = R"(stmt s; Select s such that Modifies(s, _) and Follows*(s, s1))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::STATEMENT);
            REQUIRE(result.declarations[0].synonym == "s");
            REQUIRE(result.clauses.size() == 2);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Invalid Such That Clause (Missing Arguments)") {
            std::string query = R"(stmt s; Select s such that Modifies(s))";

            REQUIRE_THROWS(parser.parseQuery(query));
        }

        SECTION("Invalid Such That Clause (Unknown Relation)") {
            std::string query = R"(stmt s; Select s such that InvalidRelation(s, _))";

            REQUIRE_THROWS(parser.parseQuery(query));
        }

        SECTION("Invalid Relation Format (Follows)") {
            std::string query = R"(stmt s, s1; Select s such that Follows * (s, s1))";

            REQUIRE_THROWS(parser.parseQuery(query));
        }

        SECTION("Invalid Relation Format (Parent)") {
            std::string query = R"(stmt s, s1; Select s such that Parent * (s, s1))";

            REQUIRE_THROWS(parser.parseQuery(query));
        }
    }

    SECTION("pattern clause") {
        SECTION("Valid Pattern Clause Query") {
            std::string query = R"(assign a; Select a pattern a ( _, "count + 1"))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Valid Pattern Clause Query with and") {
            std::string query = R"(assign a; Select a pattern a ( _, "count + 1") and a (_, _"cenX * cenX"_))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 2);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("Invalid Query with Missing Arguments in Pattern Clause") {
            std::string query = R"(assign a; Select a pattern a (_))";

            REQUIRE_THROWS(parser.parseQuery(query));
        }

        SECTION("Query with More Complex Pattern Clause") {
            std::string query = R"(assign a; Select a pattern a (_, _"cenX * cenX"_))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 1);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }
    }

    SECTION("such that and pattern clause") {
        SECTION("such that first and then pattern clause") {
            std::string query = R"(assign a;
            Select a such that Uses (a, "x")
            pattern a (_, _"cenX * cenX"_))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 2);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("pattern first and then such that clause") {
            std::string query = R"(assign a; Select a pattern a (_, _"cenX * cenX"_) such that Uses (a, "x"))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 2);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("pattern first with and then such that clause with and") {
            std::string query = R"(assign a; Select a pattern a (_, _"cenX * cenX"_) and
            a( _, "count + 1") such that Uses (a, "x") and Follows*(s, s1))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 4);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE_FALSE(result.clauses[2]->isNot);
            REQUIRE_FALSE(result.clauses[3]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }
    }

    SECTION("such that, pattern clause and with clause") {
        SECTION("such that first, then pattern clause and lastly with clause") {
            std::string query = R"(assign a;
            Select a such that Uses (a, "x")
            pattern a (_, _"cenX * cenX"_) with a.value = 3)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 3);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE_FALSE(result.clauses[2]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("such that first, then pattern clause and lastly with clause that contains and") {
            std::string query = R"(assign a;
            Select a such that Uses (a, "x")
            pattern a (_, _"cenX * cenX"_) with a.value = 3 and a.stmt# = 4)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 4);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE_FALSE(result.clauses[2]->isNot);
            REQUIRE_FALSE(result.clauses[3]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("such that first, then pattern clause and lastly with clause that contains and & not") {
            std::string query = R"(assign a;
            Select a such that Uses (a, "x")
            pattern a (_, _"cenX * cenX"_) with a.value = 3 and not a.stmt# = 4)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 4);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE_FALSE(result.clauses[2]->isNot);
            REQUIRE(result.clauses[3]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }
    }

    SECTION("such that, pattern clause and with clause") {
        SECTION("such that first, then pattern clause and lastly with clause") {
            std::string query = R"(assign a;
            Select a such that Uses (a, "x")
            pattern a (_, _"cenX * cenX"_) with a.value = 3)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 3);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE_FALSE(result.clauses[2]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }

        SECTION("such that first, then pattern clause and lastly with clause containing 'not'") {
            std::string query = R"(assign a;
            Select a such that not Uses (a, "x")
            pattern a (_, _"cenX * cenX"_) with not a.value = 3)";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 3);
            REQUIRE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE(result.clauses[2]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }
    }

    SECTION("Multiple ands") {
        SECTION("For such that clause") {
            std::string query = R"(assign a;
            Select a such that Uses (a, "x")
            and Modifies (a, "x")
            and Parent* (w, a))";

            Query result = parser.parseQuery(query);

            REQUIRE(result.declarations.size() == 1);
            REQUIRE(result.declarations[0].entityType == EntityType::ASSIGN);
            REQUIRE(result.declarations[0].synonym == "a");
            REQUIRE(result.clauses.size() == 3);
            REQUIRE_FALSE(result.clauses[0]->isNot);
            REQUIRE_FALSE(result.clauses[1]->isNot);
            REQUIRE_FALSE(result.clauses[2]->isNot);
            REQUIRE(result.selClause.argument->getType() == ArgType::TUPLE);

            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(result.selClause.argument);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a");
            REQUIRE(tuplePtr->getTupleItems()[0].getType() == ArgType::SYNONYM);
        }
    }
}

TEST_CASE("Test handlePotentialDeclaration") {
    std::vector<QpsToken> tokens;
    std::vector<Declaration> declarations;
    size_t currentIndex = 0;

    SECTION("Valid Handling Of a Declaration") {
        // Valid Design Entity, Synonym, and Semicolon
        tokens = {QpsToken("stmt", QpsTokenType::ALPHANUM), QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(Constants::SEMICOLON, QpsTokenType::SEMICOLON)};

        parser.handlePotentialDeclaration(tokens, currentIndex, declarations);

        REQUIRE(declarations.size() == 1);
        REQUIRE(declarations[0].entityType == EntityType::STATEMENT);
        REQUIRE(declarations[0].synonym == "s");
    }

    SECTION("Valid Handling Of Multi Declarations") {
        // Valid multi declarations
        currentIndex = 0;
        tokens = {QpsToken("stmt", QpsTokenType::ALPHANUM), QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(Constants::COMMA, QpsTokenType::COMMA), QpsToken("a", QpsTokenType::ALPHANUM),
                  QpsToken(Constants::SEMICOLON, QpsTokenType::SEMICOLON)};
        declarations.clear();

        parser.handlePotentialDeclaration(tokens, currentIndex, declarations);

        REQUIRE(declarations.size() == 2);
        REQUIRE(declarations[0].entityType == EntityType::STATEMENT);
        REQUIRE(declarations[0].synonym == "s");
        REQUIRE(declarations[1].entityType == EntityType::STATEMENT);
        REQUIRE(declarations[1].synonym == "a");
    }

    SECTION("Invalid Handling Of Declaration") {
        // Invalid Design Entity
        currentIndex = 0;
        tokens = {QpsToken("invalid", QpsTokenType::ALPHANUM), QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(Constants::SEMICOLON, QpsTokenType::SEMICOLON)};
        declarations.clear();

        REQUIRE_THROWS(parser.handlePotentialDeclaration(tokens, currentIndex, declarations));

        // Missing Semicolon
        currentIndex = 0;
        tokens = {QpsToken("stmt", QpsTokenType::ALPHANUM), QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken("extra", QpsTokenType::ALPHANUM)};
        declarations.clear();

        REQUIRE_THROWS(parser.handlePotentialDeclaration(tokens, currentIndex, declarations));

        // Invalid multiple declarations
        currentIndex = 0;
        tokens = {QpsToken("stmt", QpsTokenType::ALPHANUM), QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA),       QpsToken("assign", QpsTokenType::ALPHANUM),
                  QpsToken("a", QpsTokenType::ALPHANUM),    QpsToken(";", QpsTokenType::SEMICOLON)};
        declarations.clear();

        REQUIRE_THROWS(parser.handlePotentialDeclaration(tokens, currentIndex, declarations));

        // Missing multiple declarations
        currentIndex = 0;
        tokens = {QpsToken("stmt", QpsTokenType::ALPHANUM), QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA)};
        declarations.clear();

        REQUIRE_THROWS(parser.handlePotentialDeclaration(tokens, currentIndex, declarations));

        // Extra punctuation
        currentIndex = 0;
        tokens = {QpsToken("stmt", QpsTokenType::ALPHANUM), QpsToken("s", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA), QpsToken(";", QpsTokenType::SEMICOLON)};
        declarations.clear();

        REQUIRE_THROWS(parser.handlePotentialDeclaration(tokens, currentIndex, declarations));
    }
}

TEST_CASE("Test handlePotentialSelect") {
    std::vector<QpsToken> tokens;
    size_t currentIndex = 0;
    bool isAnd = false;

    SECTION("Valid Handling Of Select") {
        auto declarations = Mock::Declarations();

        SECTION("One Elem Tuple") {
            // Synonym result
            tokens = {QpsToken("Select", QpsTokenType::ALPHANUM), QpsToken("s", QpsTokenType::ALPHANUM)};

            std::unique_ptr<SelClause> selClause = parser.handlePotentialSelect(tokens, currentIndex, declarations);

            REQUIRE(selClause->argument->getType() == ArgType::TUPLE);
            REQUIRE(selClause->argument->getStr() == "s");
            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(selClause->argument);
            REQUIRE(tuplePtr->getTupleItems().size() == 1);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s");

            // AttrRef result: stmt#
            currentIndex = 0;
            tokens = {QpsToken("Select", QpsTokenType::ALPHANUM), QpsToken("s", QpsTokenType::ALPHANUM),
                      QpsToken(".", QpsTokenType::DOT), QpsToken("stmt", QpsTokenType::ALPHANUM),
                      QpsToken("#", QpsTokenType::HASH)};

            selClause = parser.handlePotentialSelect(tokens, currentIndex, declarations);

            REQUIRE(selClause->argument->getType() == ArgType::TUPLE);
            REQUIRE(selClause->argument->getStr() == "s.stmt#");
            tuplePtr = std::dynamic_pointer_cast<Tuple>(selClause->argument);
            REQUIRE(tuplePtr->getTupleItems().size() == 1);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "s.stmt#");

            // AttrRef result: value
            currentIndex = 0;
            tokens = {QpsToken("Select", QpsTokenType::ALPHANUM), QpsToken("c", QpsTokenType::ALPHANUM),
                      QpsToken(".", QpsTokenType::DOT), QpsToken("value", QpsTokenType::ALPHANUM)};

            selClause = parser.handlePotentialSelect(tokens, currentIndex, declarations);

            REQUIRE(selClause->argument->getType() == ArgType::TUPLE);
            REQUIRE(selClause->argument->getStr() == "c.value");
            tuplePtr = std::dynamic_pointer_cast<Tuple>(selClause->argument);
            REQUIRE(tuplePtr->getTupleItems().size() == 1);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "c.value");

            // "Select" Synonym
            currentIndex = 0;
            tokens = {QpsToken("Select", QpsTokenType::ALPHANUM), QpsToken("Select", QpsTokenType::ALPHANUM)};

            selClause = parser.handlePotentialSelect(tokens, currentIndex, declarations);

            REQUIRE(selClause->argument->getType() == ArgType::TUPLE);
            REQUIRE(selClause->argument->getStr() == "Select");
            tuplePtr = std::dynamic_pointer_cast<Tuple>(selClause->argument);
            REQUIRE(tuplePtr->getTupleItems().size() == 1);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "Select");
        }

        SECTION("Multi Elems Tuple") {
            // Tuple result with 2 synonyms
            // Select <a1, a2>
            currentIndex = 0;
            tokens = {QpsToken("Select", QpsTokenType::ALPHANUM), QpsToken("<", QpsTokenType::TUPLE_OPEN_BRACKET),
                      QpsToken("a1", QpsTokenType::ALPHANUM),     QpsToken(",", QpsTokenType::COMMA),
                      QpsToken("a2", QpsTokenType::ALPHANUM),     QpsToken(">", QpsTokenType::TUPLE_CLOSE_BRACKET)};

            std::unique_ptr<SelClause> selClause = parser.handlePotentialSelect(tokens, currentIndex, declarations);

            REQUIRE(selClause->argument->getType() == ArgType::TUPLE);
            REQUIRE(selClause->argument->getStr() == "<a1,a2>");
            std::shared_ptr<Tuple> tuplePtr = std::dynamic_pointer_cast<Tuple>(selClause->argument);
            REQUIRE(tuplePtr->getTupleItems().size() == 2);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a1");
            REQUIRE(tuplePtr->getTupleItems()[1].getStr() == "a2");

            // Tuple result with 3 synonyms
            // Select <a1, a2, a3>
            currentIndex = 0;
            tokens = {QpsToken("Select", QpsTokenType::ALPHANUM), QpsToken("<", QpsTokenType::TUPLE_OPEN_BRACKET),
                      QpsToken("a1", QpsTokenType::ALPHANUM),     QpsToken(",", QpsTokenType::COMMA),
                      QpsToken("a2", QpsTokenType::ALPHANUM),     QpsToken(",", QpsTokenType::COMMA),
                      QpsToken("a3", QpsTokenType::ALPHANUM),     QpsToken(">", QpsTokenType::TUPLE_CLOSE_BRACKET)};

            selClause = parser.handlePotentialSelect(tokens, currentIndex, declarations);

            REQUIRE(selClause->argument->getType() == ArgType::TUPLE);
            REQUIRE(selClause->argument->getStr() == "<a1,a2,a3>");
            tuplePtr = std::dynamic_pointer_cast<Tuple>(selClause->argument);
            REQUIRE(tuplePtr->getTupleItems().size() == 3);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a1");
            REQUIRE(tuplePtr->getTupleItems()[1].getStr() == "a2");
            REQUIRE(tuplePtr->getTupleItems()[2].getStr() == "a3");

            // Tuple result with 2 attrRef
            // Select <a.value, s.stmt#>
            currentIndex = 0;
            tokens = {QpsToken("Select", QpsTokenType::ALPHANUM),      QpsToken("<", QpsTokenType::TUPLE_OPEN_BRACKET),
                      QpsToken("a", QpsTokenType::ALPHANUM),           QpsToken(".", QpsTokenType::DOT),
                      QpsToken("value", QpsTokenType::ALPHANUM),       QpsToken(",", QpsTokenType::COMMA),
                      QpsToken("a2", QpsTokenType::ALPHANUM),          QpsToken(".", QpsTokenType::DOT),
                      QpsToken("stmt", QpsTokenType::ALPHANUM),        QpsToken("#", QpsTokenType::HASH),
                      QpsToken(">", QpsTokenType::TUPLE_CLOSE_BRACKET)};

            selClause = parser.handlePotentialSelect(tokens, currentIndex, declarations);

            REQUIRE(selClause->argument->getType() == ArgType::TUPLE);
            REQUIRE(selClause->argument->getStr() == "<a.value,a2.stmt#>");
            tuplePtr = std::dynamic_pointer_cast<Tuple>(selClause->argument);
            REQUIRE(tuplePtr->getTupleItems().size() == 2);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a.value");
            REQUIRE(tuplePtr->getTupleItems()[1].getStr() == "a2.stmt#");

            // Tuple result with synonym & attrRef
            // Select <a1, p.procName>
            currentIndex = 0;
            tokens = {QpsToken("Select", QpsTokenType::ALPHANUM),   QpsToken("<", QpsTokenType::TUPLE_OPEN_BRACKET),
                      QpsToken("a1", QpsTokenType::ALPHANUM),       QpsToken(",", QpsTokenType::COMMA),
                      QpsToken("p", QpsTokenType::ALPHANUM),        QpsToken(".", QpsTokenType::DOT),
                      QpsToken("procName", QpsTokenType::ALPHANUM), QpsToken(">", QpsTokenType::TUPLE_CLOSE_BRACKET)};

            selClause = parser.handlePotentialSelect(tokens, currentIndex, declarations);

            REQUIRE(selClause->argument->getType() == ArgType::TUPLE);
            REQUIRE(selClause->argument->getStr() == "<a1,p.procName>");
            tuplePtr = std::dynamic_pointer_cast<Tuple>(selClause->argument);
            REQUIRE(tuplePtr->getTupleItems().size() == 2);
            REQUIRE(tuplePtr->getTupleItems()[0].getStr() == "a1");
            REQUIRE(tuplePtr->getTupleItems()[1].getStr() == "p.procName");
        }
    }

    SECTION("Invalid Handling Of Select") {
        // Missing Synonym
        currentIndex = 0;
        tokens = {QpsToken("Select", QpsTokenType::ALPHANUM)};
        auto declarations = Mock::Declarations();

        try {
            parser.handlePotentialSelect(tokens, currentIndex, declarations);
        } catch (SyntacticException& e) {
            REQUIRE(e.what() == "SyntaxError");
        }

        // Invalid Tuple format (Missing CLOSE_TUPLE_BRACKET)
        currentIndex = 0;
        tokens = {QpsToken("Select", QpsTokenType::ALPHANUM), QpsToken("<", QpsTokenType::TUPLE_OPEN_BRACKET),
                  QpsToken("s1", QpsTokenType::ALPHANUM), QpsToken(",", QpsTokenType::COMMA),
                  QpsToken("s2", QpsTokenType::ALPHANUM)};

        try {
            parser.handlePotentialSelect(tokens, currentIndex, declarations);
        } catch (SyntacticException& e) {
            REQUIRE(e.what() == "SyntaxError");
        }

        // Invalid Tuple format (Missing OPEN_TUPLE_BRACKET)
        currentIndex = 0;
        tokens = {QpsToken("Select", QpsTokenType::ALPHANUM), QpsToken("s1", QpsTokenType::ALPHANUM),
                  QpsToken(",", QpsTokenType::COMMA), QpsToken("s2", QpsTokenType::ALPHANUM),
                  QpsToken(">", QpsTokenType::TUPLE_CLOSE_BRACKET)};

        try {
            parser.handlePotentialSelect(tokens, currentIndex, declarations);
        } catch (SyntacticException& e) {
            REQUIRE(e.what() == "SyntaxError");
        }
    }
}