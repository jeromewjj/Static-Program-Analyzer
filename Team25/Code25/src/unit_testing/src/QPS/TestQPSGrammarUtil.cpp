#include "QPS/Argument/Argument.h"
#include "QPS/QPSGrammarUtil.h"
#include "catch.hpp"

TEST_CASE("Test isName") {
    SECTION("Valid Names") {
        REQUIRE(isName("x"));
        REQUIRE(isName("var123"));
        REQUIRE(isName("A"));
        REQUIRE(isName("Abc"));
        REQUIRE(isName("abc123"));
    }

    SECTION("Invalid Names") {
        REQUIRE_FALSE(isName(""));
        REQUIRE_FALSE(isName("1abc"));
        REQUIRE_FALSE(isName("var@"));
        REQUIRE_FALSE(isName("Var 123"));
    }
}

TEST_CASE("Test isIdent") {
    SECTION("Valid Ident") {
        REQUIRE(isIdent("x"));
        REQUIRE(isIdent("var123"));
        REQUIRE(isIdent("A"));
        REQUIRE(isIdent("Abc"));
        REQUIRE(isIdent("abc123"));
    }

    SECTION("Invalid Ident") {
        REQUIRE_FALSE(isIdent(""));
        REQUIRE_FALSE(isIdent("1abc"));
        REQUIRE_FALSE(isIdent("var@"));
        REQUIRE_FALSE(isIdent("Var 123"));
    }
}

TEST_CASE("Test isInteger") {
    SECTION("Valid Integer") {
        REQUIRE(isInteger("1"));
        REQUIRE(isInteger("123"));
        REQUIRE(isInteger("0"));
        REQUIRE(isInteger("10"));
        REQUIRE(isInteger("9"));
        REQUIRE(isInteger("99"));
    }

    SECTION("Invalid Integer") {
        REQUIRE_FALSE(isInteger("01"));
        REQUIRE_FALSE(isInteger("abc"));
        REQUIRE_FALSE(isInteger("@"));
        REQUIRE_FALSE(isInteger("012"));
        REQUIRE_FALSE(isInteger(" "));
        REQUIRE_FALSE(isInteger("1.2"));
    }
}

TEST_CASE("Test isSynonym") {
    SECTION("Valid Synonym") {
        REQUIRE(isSynonym("x"));
        REQUIRE(isSynonym("var123"));
        REQUIRE(isSynonym("A"));
        REQUIRE(isSynonym("Abc"));
        REQUIRE(isSynonym("abc123"));
    }

    SECTION("Invalid Synonym") {
        REQUIRE_FALSE(isSynonym(""));
        REQUIRE_FALSE(isSynonym("1abc"));
        REQUIRE_FALSE(isSynonym("var@"));
        REQUIRE_FALSE(isSynonym("Var 123"));
    }
}

TEST_CASE("Test isDesignEntity") {
    SECTION("Valid DesignEntity") {
        REQUIRE(isDesignEntity("stmt"));
        REQUIRE(isDesignEntity("read"));
        REQUIRE(isDesignEntity("print"));
        REQUIRE(isDesignEntity("call"));
        REQUIRE(isDesignEntity("while"));
        REQUIRE(isDesignEntity("if"));
        REQUIRE(isDesignEntity("assign"));
        REQUIRE(isDesignEntity("variable"));
        REQUIRE(isDesignEntity("constant"));
        REQUIRE(isDesignEntity("procedure"));
        REQUIRE(isDesignEntity("stmt "));
        REQUIRE(isDesignEntity(" stmt"));
        REQUIRE(isDesignEntity(" stmt "));
    }

    SECTION("Invalid DesignEntity") {
        REQUIRE_FALSE(isDesignEntity(""));
        REQUIRE_FALSE(isDesignEntity(" "));
        REQUIRE_FALSE(isDesignEntity("Stmt"));
        REQUIRE_FALSE(isDesignEntity("STMT"));
        REQUIRE_FALSE(isDesignEntity("*"));
        REQUIRE_FALSE(isDesignEntity("1"));
    }
}

TEST_CASE("Test isDeclaration") {
    SECTION("Valid Declaration") {
        REQUIRE(isDeclaration("stmt", "s", ";"));
        REQUIRE(isDeclaration("variable", "v", ";"));
    }

    SECTION("Invalid Declaration") {
        REQUIRE_FALSE(isDeclaration("variable", "v", ""));
        REQUIRE_FALSE(isDeclaration("", "v", ";"));
        REQUIRE_FALSE(isDeclaration("variable", "", ";"));
    }
}

TEST_CASE("Test isSelect") {
    SECTION("Valid Select") {
        REQUIRE(isSelect("Select"));
    }

    SECTION("Invalid Select") {
        REQUIRE_FALSE(isSelect("s"));
    }
}

TEST_CASE("Test isSuch") {
    SECTION("Valid Such") {
        REQUIRE(isSuch("such"));
    }

    SECTION("Invalid Such") {
        REQUIRE_FALSE(isSuch("that"));
    }
}

TEST_CASE("Test isThat") {
    SECTION("Valid That") {
        REQUIRE(isThat("that"));
    }

    SECTION("Invalid That") {
        REQUIRE_FALSE(isThat("such"));
    }
}

TEST_CASE("Test isStmtRef") {
    SECTION("Valid StmtRef") {
        REQUIRE(isStmtRef("s"));
        REQUIRE(isStmtRef("_"));
        REQUIRE(isStmtRef("123"));
        REQUIRE(isStmtRef("stmt")); // Synonym and design entity names can be same
        REQUIRE(isStmtRef("St"));
        REQUIRE(isStmtRef("Select"));
        REQUIRE(isStmtRef("Pattern"));
        REQUIRE(isStmtRef("Such"));
    }
    SECTION("Invalid StmtRef") {
        REQUIRE_FALSE(isStmtRef(""));
        REQUIRE_FALSE(isStmtRef("stmt;"));
    }
}

TEST_CASE("Test isEntRef") {
    SECTION("Valid EntRef") {
        REQUIRE(isEntRef("stmt"));
        REQUIRE(isEntRef("_"));
        REQUIRE(isEntRef("\"variable\""));
        REQUIRE(isEntRef("St"));
    }
    SECTION("Invalid EntRef") {
        REQUIRE_FALSE(isEntRef(""));
        REQUIRE_FALSE(isEntRef("stmt;"));
        REQUIRE_FALSE(isEntRef("\"stmt"));
        REQUIRE_FALSE(isEntRef("123"));
    }
}

TEST_CASE("Test isFollows") {
    SECTION("Valid Follows") {
        REQUIRE(isFollows("Follows(s, v)"));
        REQUIRE(isFollows("Follows(_, v)"));
        REQUIRE(isFollows("Follows(s, _)"));
        REQUIRE(isFollows("Follows(_, _)"));
        REQUIRE(isFollows("Follows(stmt1, v2)"));
        REQUIRE(isFollows("Follows(s, v2)"));
        REQUIRE(isFollows("Follows(stmt1, v)"));
        REQUIRE(isFollows("Follows(1, v)"));
    }

    SECTION("Invalid Follows") {
        REQUIRE_FALSE(isFollows("Follows(s,)"));
        REQUIRE_FALSE(isFollows("Follows(s,)"));
        REQUIRE_FALSE(isFollows("Follows (s, v)"));
        REQUIRE_FALSE(isFollows("Follows (stmt1, v 2)"));
        REQUIRE_FALSE(isFollows("Follows (s, v 2)"));
        REQUIRE_FALSE(isFollows("Follows(stmt 1, v)"));
    }
}

TEST_CASE("Test isFollowsT") {
    SECTION("Valid Follows*") {
        REQUIRE(isFollowsT("Follows*(s, v)"));
        REQUIRE(isFollowsT("Follows*(_, v)"));
        REQUIRE(isFollowsT("Follows*(s, _)"));
        REQUIRE(isFollowsT("Follows*(_, _)"));
        REQUIRE(isFollowsT("Follows*(stmt1, v2)"));
        REQUIRE(isFollowsT("Follows*(s, v2)"));
        REQUIRE(isFollowsT("Follows*(stmt1, v)"));
        REQUIRE(isFollowsT("Follows*(1, v)"));
    }

    SECTION("Invalid Follows*") {
        REQUIRE_FALSE(isFollowsT("Follows*(s,)"));
        REQUIRE_FALSE(isFollowsT("Follows*(s,)"));
        REQUIRE_FALSE(isFollowsT("Follows* (s, v)"));
        REQUIRE_FALSE(isFollowsT("Follows* (stmt1, v 2)"));
        REQUIRE_FALSE(isFollowsT("Follows* (s, v 2)"));
        REQUIRE_FALSE(isFollowsT("Follows*(stmt 1, v)"));
    }
}

TEST_CASE("Test isParent") {
    SECTION("Valid Parent") {
        REQUIRE(isParent("Parent(s, v)"));
        REQUIRE(isParent("Parent(_, v)"));
        REQUIRE(isParent("Parent(s, _)"));
        REQUIRE(isParent("Parent(_, _)"));
        REQUIRE(isParent("Parent(stmt1, v2)"));
        REQUIRE(isParent("Parent(s, v2)"));
        REQUIRE(isParent("Parent(stmt1, v)"));
        REQUIRE(isParent("Parent(1, v)"));
    }

    SECTION("Invalid Parent") {
        REQUIRE_FALSE(isParent("Parent(s,)"));
        REQUIRE_FALSE(isParent("Parent(s,)"));
        REQUIRE_FALSE(isParent("Parent (s, v)"));
        REQUIRE_FALSE(isParent("Parent (stmt1, v 2)"));
        REQUIRE_FALSE(isParent("Parent (s, v 2)"));
        REQUIRE_FALSE(isParent("Parent(stmt 1, v)"));
    }
}

TEST_CASE("Test isParentT") {
    SECTION("Valid Parent*") {
        REQUIRE(isParentT("Parent*(s, v)"));
        REQUIRE(isParentT("Parent*(_, v)"));
        REQUIRE(isParentT("Parent*(s, _)"));
        REQUIRE(isParentT("Parent*(_, _)"));
        REQUIRE(isParentT("Parent*(stmt1, v2)"));
        REQUIRE(isParentT("Parent*(s, v2)"));
        REQUIRE(isParentT("Parent*(stmt1, v)"));
        REQUIRE(isParentT("Parent*(1, v)"));
    }

    SECTION("Invalid Parent*") {
        REQUIRE_FALSE(isParentT("Parent*(s,)"));
        REQUIRE_FALSE(isParentT("Parent*(s,)"));
        REQUIRE_FALSE(isParentT("Parent* (s, v)"));
        REQUIRE_FALSE(isParentT("Parent* (stmt1, v 2)"));
        REQUIRE_FALSE(isParentT("Parent* (s, v 2)"));
        REQUIRE_FALSE(isParentT("Parent*(stmt 1, v)"));
    }
}

TEST_CASE("Test isUsesS") {
    SECTION("Valid UsesS") {
        REQUIRE(isUsesS("Uses(s, v)"));
        REQUIRE(isUsesS("Uses(_, v)"));
        REQUIRE(isUsesS("Uses(s, _)"));
        REQUIRE(isUsesS("Uses(_, _)"));
        REQUIRE(isUsesS("Uses(stmt1, v2)"));
        REQUIRE(isUsesS("Uses(s, v2)"));
        REQUIRE(isUsesS("Uses(stmt1, v)"));
        REQUIRE(isUsesS("Uses(1, v)"));
    }

    SECTION("Invalid UsesS") {
        REQUIRE_FALSE(isUsesS("Uses(s,)"));
        REQUIRE_FALSE(isUsesS("Uses(s,)"));
        REQUIRE_FALSE(isUsesS("Uses (s, v)"));
        REQUIRE_FALSE(isUsesS("Uses (stmt1, v 2)"));
        REQUIRE_FALSE(isUsesS("Uses (s, v 2)"));
        REQUIRE_FALSE(isUsesS("Uses(stmt 1, v)"));
    }
}

TEST_CASE("Test isUsesP") {
    SECTION("Valid UsesP") {
        REQUIRE(isUsesP("Uses(s, v)"));
        REQUIRE(isUsesP("Uses(_, v)"));
        REQUIRE(isUsesP("Uses(s, _)"));
        REQUIRE(isUsesP("Uses(_, _)"));
        REQUIRE(isUsesP("Uses(stmt1, v2)"));
        REQUIRE(isUsesP("Uses(s, v2)"));
        REQUIRE(isUsesP("Uses(stmt1, v)"));
        REQUIRE(isUsesP("Uses(\"hello\", \"test\")"));
        REQUIRE(isUsesP("Uses(\"hello\", c)"));
        REQUIRE(isUsesP("Uses(c, \"hello\")"));
    }

    SECTION("Invalid UsesP") {
        REQUIRE_FALSE(isUsesP("Uses(s,)"));
        REQUIRE_FALSE(isUsesP("Uses(s,)"));
        REQUIRE_FALSE(isUsesP("Uses (s, v)"));
        REQUIRE_FALSE(isUsesP("Uses (stmt1, v 2)"));
        REQUIRE_FALSE(isUsesP("Uses (s, v 2)"));
        REQUIRE_FALSE(isUsesP("Uses(stmt 1, v)"));
        REQUIRE_FALSE(isUsesP("Uses(1, v)"));
        REQUIRE_FALSE(isUsesP("Uses(v, 1)"));
        REQUIRE_FALSE(isUsesP("Uses(1, 1)"));
    }
}

TEST_CASE("Test isModifiesS") {
    SECTION("Valid ModifiesS") {
        REQUIRE(isModifiesS("Modifies(s, v)"));
        REQUIRE(isModifiesS("Modifies(_, v)"));
        REQUIRE(isModifiesS("Modifies(s, _)"));
        REQUIRE(isModifiesS("Modifies(_, _)"));
        REQUIRE(isModifiesS("Modifies(stmt1, v2)"));
        REQUIRE(isModifiesS("Modifies(s, v2)"));
        REQUIRE(isModifiesS("Modifies(stmt1, v)"));
        REQUIRE(isModifiesS("Modifies(1, v)"));
    }

    SECTION("Invalid ModifiesS") {
        REQUIRE_FALSE(isModifiesS("Modifies(s,)"));
        REQUIRE_FALSE(isModifiesS("Modifies(s,)"));
        REQUIRE_FALSE(isModifiesS("Modifies (s, v)"));
        REQUIRE_FALSE(isModifiesS("Modifies (stmt1, v 2)"));
        REQUIRE_FALSE(isModifiesS("Modifies (s, v 2)"));
        REQUIRE_FALSE(isModifiesS("Modifies(stmt 1, v)"));
    }
}

TEST_CASE("Test isModifiesP") {
    SECTION("Valid ModifiesP") {
        REQUIRE(isModifiesP("Modifies(s, v)"));
        REQUIRE(isModifiesP("Modifies(_, v)"));
        REQUIRE(isModifiesP("Modifies(s, _)"));
        REQUIRE(isModifiesP("Modifies(_, _)"));
        REQUIRE(isModifiesP("Modifies(stmt1, v2)"));
        REQUIRE(isModifiesP("Modifies(s, v2)"));
        REQUIRE(isModifiesP("Modifies(stmt1, v)"));
        REQUIRE(isModifiesP("Modifies(\"hello\", \"test\")"));
        REQUIRE(isModifiesP("Modifies(\"hello\", c)"));
        REQUIRE(isModifiesP("Modifies(c, \"hello\")"));
    }

    SECTION("Invalid ModifiesP") {
        REQUIRE_FALSE(isModifiesP("Modifies(s,)"));
        REQUIRE_FALSE(isModifiesP("Modifies(s,)"));
        REQUIRE_FALSE(isModifiesP("Modifies (s, v)"));
        REQUIRE_FALSE(isModifiesP("Modifies (stmt1, v 2)"));
        REQUIRE_FALSE(isModifiesP("Modifies (s, v 2)"));
        REQUIRE_FALSE(isModifiesP("Modifies(stmt 1, v)"));
        REQUIRE_FALSE(isModifiesP("Modifies(1, v)"));
        REQUIRE_FALSE(isModifiesP("Modifies(v, 1)"));
        REQUIRE_FALSE(isModifiesP("Modifies(1, 1)"));
    }
}

TEST_CASE("Test isCalls") {
    SECTION("Valid Calls") {
        REQUIRE(isCalls("Calls(s, v)"));
        REQUIRE(isCalls("Calls(_, v)"));
        REQUIRE(isCalls("Calls(s, _)"));
        REQUIRE(isCalls("Calls(_, _)"));
        REQUIRE(isCalls("Calls(stmt1, v2)"));
        REQUIRE(isCalls("Calls(s, v2)"));
        REQUIRE(isCalls("Calls(stmt1, v)"));
        REQUIRE(isCalls("Calls(\"hello\", \"test\")"));
        REQUIRE(isCalls("Calls(\"hello\", c)"));
        REQUIRE(isCalls("Calls(c, \"hello\")"));
    }

    SECTION("Invalid Calls") {
        REQUIRE_FALSE(isCalls("Calls(s,)"));
        REQUIRE_FALSE(isCalls("Calls(s,)"));
        REQUIRE_FALSE(isCalls("Calls (s, v)"));
        REQUIRE_FALSE(isCalls("Calls (stmt1, v 2)"));
        REQUIRE_FALSE(isCalls("Calls (s, v 2)"));
        REQUIRE_FALSE(isCalls("Calls(stmt 1, v)"));
        REQUIRE_FALSE(isCalls("Calls(1, v)"));
        REQUIRE_FALSE(isCalls("Calls(v, 1)"));
        REQUIRE_FALSE(isCalls("Calls(1, 1)"));
    }
}

TEST_CASE("Test isCalls_T") {
    SECTION("Valid Calls*") {
        REQUIRE(isCallsT("Calls*(s, v)"));
        REQUIRE(isCallsT("Calls*(_, v)"));
        REQUIRE(isCallsT("Calls*(s, _)"));
        REQUIRE(isCallsT("Calls*(_, _)"));
        REQUIRE(isCallsT("Calls*(stmt1, v2)"));
        REQUIRE(isCallsT("Calls*(s, v2)"));
        REQUIRE(isCallsT("Calls*(stmt1, v)"));
        REQUIRE(isCallsT("Calls*(\"hello\", \"test\")"));
        REQUIRE(isCallsT("Calls*(\"hello\", c)"));
        REQUIRE(isCallsT("Calls*(c, \"hello\")"));
    }

    SECTION("Invalid Calls*") {
        REQUIRE_FALSE(isCallsT("Calls*(s,)"));
        REQUIRE_FALSE(isCallsT("Calls*(s,)"));
        REQUIRE_FALSE(isCallsT("Calls* (s, v)"));
        REQUIRE_FALSE(isCallsT("Calls* (stmt1, v 2)"));
        REQUIRE_FALSE(isCallsT("Calls* (s, v 2)"));
        REQUIRE_FALSE(isCallsT("Calls*(stmt 1, v)"));
        REQUIRE_FALSE(isCallsT("Calls*(1, v)"));
        REQUIRE_FALSE(isCallsT("Calls*(v, 1)"));
        REQUIRE_FALSE(isCallsT("Calls*(1, 1)"));
    }
}

TEST_CASE("Test isNext") {
    SECTION("Valid Next") {
        REQUIRE(isNext("Next(s, v)"));
        REQUIRE(isNext("Next(_, v)"));
        REQUIRE(isNext("Next(s, _)"));
        REQUIRE(isNext("Next(_, _)"));
        REQUIRE(isNext("Next(stmt1, v2)"));
        REQUIRE(isNext("Next(s, v2)"));
        REQUIRE(isNext("Next(stmt1, v)"));
        REQUIRE(isNext("Next(1, v)"));
    }

    SECTION("Invalid Next") {
        REQUIRE_FALSE(isNext("Next(s,)"));
        REQUIRE_FALSE(isNext("Next(s,)"));
        REQUIRE_FALSE(isNext("Next (s, v)"));
        REQUIRE_FALSE(isNext("Next (stmt1, v 2)"));
        REQUIRE_FALSE(isNext("Next (s, v 2)"));
        REQUIRE_FALSE(isNext("Next(stmt 1, v)"));
    }
}

TEST_CASE("Test isNextT") {
    SECTION("Valid Next*") {
        REQUIRE(isNextT("Next*(s, v)"));
        REQUIRE(isNextT("Next*(_, v)"));
        REQUIRE(isNextT("Next*(s, _)"));
        REQUIRE(isNextT("Next*(_, _)"));
        REQUIRE(isNextT("Next*(stmt1, v2)"));
        REQUIRE(isNextT("Next*(s, v2)"));
        REQUIRE(isNextT("Next*(stmt1, v)"));
        REQUIRE(isNextT("Next*(1, v)"));
    }

    SECTION("Invalid Next*") {
        REQUIRE_FALSE(isNextT("Next*(s,)"));
        REQUIRE_FALSE(isNextT("Next*(s,)"));
        REQUIRE_FALSE(isNextT("Next* (s, v)"));
        REQUIRE_FALSE(isNextT("Next* (stmt1, v 2)"));
        REQUIRE_FALSE(isNextT("Next* (s, v 2)"));
        REQUIRE_FALSE(isNextT("Next*(stmt 1, v)"));
    }
}

TEST_CASE("Test isAffects") {
    SECTION("Valid Affects") {
        REQUIRE(isAffects("Affects(s, v)"));
        REQUIRE(isAffects("Affects(_, v)"));
        REQUIRE(isAffects("Affects(s, _)"));
        REQUIRE(isAffects("Affects(_, _)"));
        REQUIRE(isAffects("Affects(stmt1, v2)"));
        REQUIRE(isAffects("Affects(s, v2)"));
        REQUIRE(isAffects("Affects(stmt1, v)"));
        REQUIRE(isAffects("Affects(1, v)"));
    }

    SECTION("Invalid Affects") {
        REQUIRE_FALSE(isAffects("Affects(s,)"));
        REQUIRE_FALSE(isAffects("Affects(s,)"));
        REQUIRE_FALSE(isAffects("Affects (s, v)"));
        REQUIRE_FALSE(isAffects("Affects (stmt1, v 2)"));
        REQUIRE_FALSE(isAffects("Affects (s, v 2)"));
        REQUIRE_FALSE(isAffects("Affects(stmt 1, v)"));
    }
}

TEST_CASE("Test isRelRef") {
    SECTION("Valid Rel names") {
        REQUIRE(isRelRef("Follows(s, v)"));
        REQUIRE(isRelRef("Follows*(s, v)"));
        REQUIRE(isRelRef("Parent(s, v)"));
        REQUIRE(isRelRef("Parent*(s, v)"));
        REQUIRE(isRelRef("Uses(s, v)"));
        REQUIRE(isRelRef("Uses(_, v)"));
        REQUIRE(isRelRef("Uses(s, _)"));
        REQUIRE(isRelRef("Uses(_, _)"));
        REQUIRE(isRelRef("Modifies(s, v)"));
        REQUIRE(isRelRef("Modifies(_, v)"));
        REQUIRE(isRelRef("Modifies(s, _)"));
        REQUIRE(isRelRef("Modifies(_, _)"));
        REQUIRE(isRelRef("Calls(c, \"hello\")"));
        REQUIRE(isRelRef("Calls*(c, \"hello\")"));
        REQUIRE(isRelRef("Next(stmt1, v2)"));
        REQUIRE(isRelRef("Next*(stmt1, v2)"));
        REQUIRE(isRelRef("Affects(stmt1, v)"));
        REQUIRE(isRelRef("Affects(1, v)"));
    }

    SECTION("Invalid Rel names") {
        REQUIRE_FALSE(isRelRef("Follow(s, v)"));
        REQUIRE_FALSE(isRelRef("Following(s, v)"));
        REQUIRE_FALSE(isRelRef("Parenting(s, v)"));
        REQUIRE_FALSE(isRelRef("Parents(s, v)"));
        REQUIRE_FALSE(isRelRef("Use(s, v)"));
        REQUIRE_FALSE(isRelRef("Used(s, v)"));
        REQUIRE_FALSE(isRelRef("Modify(s, v)"));
        REQUIRE_FALSE(isRelRef("Modified(s, v)"));
        REQUIRE_FALSE(isRelRef("Calls(s, v 2)"));
        REQUIRE_FALSE(isRelRef("Calls*(s, v 2)"));
        REQUIRE_FALSE(isRelRef("Next (s, v 2)"));
        REQUIRE_FALSE(isRelRef("Next* (s, v 2)"));
        REQUIRE_FALSE(isRelRef("Affects (s, v 2)"));
        REQUIRE_FALSE(isRelRef("Affects(stmt 1, v)"));
    }
}

TEST_CASE("Test parseRef") {
    std::tuple<std::string, std::string, std::string> result;
    std::string input;

    SECTION("Valid parseRef") {
        // Valid rel, stmtRef / entRef
        input = "Uses(s, v)";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "Uses");
        REQUIRE(std::get<1>(result) == "s");
        REQUIRE(std::get<2>(result) == " v");

        // Valid stmtRef / entRef
        input = "(s, v)";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "");
        REQUIRE(std::get<1>(result) == "s");
        REQUIRE(std::get<2>(result) == " v");

        // Valid parsing of 2 stmtRef / entRef
        input = "(stmt1, v)";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "");
        REQUIRE(std::get<1>(result) == "stmt1");
        REQUIRE(std::get<2>(result) == " v");

        // Valid parsing of 2 int stmtRef
        input = "(2, 4)";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "");
        REQUIRE(std::get<1>(result) == "2");
        REQUIRE(std::get<2>(result) == " 4");

        // Valid parsing of 1 int stmtRef & 1 wildcard
        input = "(2, _)";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "");
        REQUIRE(std::get<1>(result) == "2");
        REQUIRE(std::get<2>(result) == " _");

        // Valid parsing of 1 entRef & 1 wildcard
        input = "(j2, _)";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "");
        REQUIRE(std::get<1>(result) == "j2");
        REQUIRE(std::get<2>(result) == " _");

        // Valid parsing of 1 stmtRef & 1 entRef
        input = "(2, j2)";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "");
        REQUIRE(std::get<1>(result) == "2");
        REQUIRE(std::get<2>(result) == " j2");

        // Valid parsing of 1 stmtRef & 1 entRef with quotes
        input = "(stmt1, \"test2\")";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "");
        REQUIRE(std::get<1>(result) == "stmt1");
        REQUIRE(std::get<2>(result) == " \"test2\"");

        // Valid parsing of wildcard & 1 entRef
        input = "(_, \"test2\")";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "");
        REQUIRE(std::get<1>(result) == "_");
        REQUIRE(std::get<2>(result) == " \"test2\"");

        // Valid parsing of wildcard & complicated entRef
        input = "(_, \"(test2 + 2) * 2\")";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "");
        REQUIRE(std::get<1>(result) == "_");
        REQUIRE(std::get<2>(result) == " \"(test2 + 2) * 2\"");

        // Valid parsing of stmtRef & complicated entRef
        input = "Uses(s, \"(x+y * 5)\")";
        result = parseRef(input);
        REQUIRE(std::get<0>(result) == "Uses");
        REQUIRE(std::get<1>(result) == "s");
        REQUIRE(std::get<2>(result) == " \"(x+y * 5)\"");
    }

    SECTION("Invalid parseRef") {
        // Missing right parenthesis
        input = "(stmt1, v";
        REQUIRE_THROWS_AS(parseRef(input), SyntacticException);

        // Extra comma
        input = "(s, v,)";
        REQUIRE_THROWS_AS(parseRef(input), SyntacticException);
    }
}

TEST_CASE("Test isVarName") {
    SECTION("Valid var name") {
        REQUIRE(isVarName("NAME"));
    }

    SECTION("Invalid var name") {
        REQUIRE_FALSE(isVarName("123"));
        REQUIRE_FALSE(isVarName("_name"));
        REQUIRE_FALSE(isVarName("name!"));
    }
}

TEST_CASE("Test isConstValue") {
    SECTION("Valid constant value") {
        REQUIRE(isConstValue("123"));
    }

    SECTION("Invalid constant value") {
        REQUIRE_FALSE(isConstValue("1a2b3"));
        REQUIRE_FALSE(isConstValue("-123"));
        REQUIRE_FALSE(isConstValue("0.5"));
    }
}

TEST_CASE("Test isExpr") {
    SECTION("Valid expr") {
        REQUIRE(isExpr("x + 2"));
        REQUIRE(isExpr("3 * z"));
        REQUIRE(isExpr("a / b"));
        REQUIRE(isExpr("c % d"));
    }
    SECTION("Invalid expr") {
        REQUIRE_FALSE(isExpr("e + "));
        REQUIRE_FALSE(isExpr("+ f"));
        REQUIRE_FALSE(isExpr("g * 2 /"));
        REQUIRE_FALSE(isExpr("y - _"));
    }
}

TEST_CASE("Test isFactor") {
    SECTION("Valid factor") {
        REQUIRE(isFactor("x"));
        REQUIRE(isFactor("42"));
        REQUIRE(isFactor("(d / 3)"));
        REQUIRE(isFactor("(a + b)"));
    }
    SECTION("Invalid factor") {
        REQUIRE_FALSE(isFactor("()"));
        REQUIRE_FALSE(isFactor("(c * )"));
    }
}

TEST_CASE("Test isTerm") {
    SECTION("Valid term") {
        REQUIRE(isTerm("x * y"));
        REQUIRE(isTerm("a / b"));
        REQUIRE(isTerm("c % d"));
    }
    SECTION("Invalid term") {
        REQUIRE_FALSE(isTerm("g /"));
        REQUIRE_FALSE(isTerm(" / u"));
        REQUIRE_FALSE(isTerm(""));
    }
}

TEST_CASE("Test isExpressionSpec") {
    SECTION("Invalid expression spec") {
        REQUIRE(isExpressionSpec("\"abc\""));
        REQUIRE(isExpressionSpec("_\"def\"_"));
        REQUIRE(isExpressionSpec("_\"def\"_"));
        REQUIRE(isExpressionSpec("_"));
    }

    SECTION("Valid expression spec") {
        REQUIRE_FALSE(isExpressionSpec("_\"ghi\""));
        REQUIRE_FALSE(isExpressionSpec("_\"jkl\"_x"));
    }
}

TEST_CASE("isQuotedExpressionSpec") {
    SECTION("Valid Quoted Expression Spec") {
        REQUIRE(isQuotedExpressionSpec("\"x + 1\""));
        REQUIRE(isQuotedExpressionSpec("'y - 2'"));
    }

    SECTION("Invalid Quoted Expression Spec") {
        REQUIRE_FALSE(isQuotedExpressionSpec("x + 1"));
        REQUIRE_FALSE(isQuotedExpressionSpec("\"z + 3"));
    }
}

TEST_CASE("isUnderscoreQuotedExpressionSpec") {
    SECTION("Valid Underscore Quoted Expression Spec") {
        REQUIRE(isWildcardQuotedExpressionSpec("_\"x + 1\"_"));
        REQUIRE(isWildcardQuotedExpressionSpec("_'y - 2'_"));
    }

    SECTION("Invalid Underscore Quoted Expression Spec") {
        REQUIRE_FALSE(isWildcardQuotedExpressionSpec("_x + 1_"));
        REQUIRE_FALSE(isWildcardQuotedExpressionSpec("_\"z + 3\""));
    }
}

TEST_CASE("Test isPattern") {
    SECTION("Valid pattern") {
        REQUIRE(isPattern("pattern"));
    }

    SECTION("Invalid pattern") {
        REQUIRE_FALSE(isPattern("Pattern"));
    }
}

TEST_CASE("Test isUnderscore") {
    SECTION("Valid underscore") {
        REQUIRE(isUnderscore("_"));
    }

    SECTION("Invalid underscore") {
        REQUIRE_FALSE(isUnderscore("no"));
    }
}

TEST_CASE("Test isAttrName") {
    SECTION("Valid AttrName") {
        REQUIRE(isAttrName("procName"));
        REQUIRE(isAttrName("varName"));
        REQUIRE(isAttrName("value"));
        REQUIRE(isAttrName("stmt#"));
    }

    SECTION("Invalid AttrName") {
        REQUIRE_FALSE(isAttrName("procedureName"));
        REQUIRE_FALSE(isAttrName("var Name"));
        REQUIRE_FALSE(isAttrName("123"));
        REQUIRE_FALSE(isAttrName(" stmt#"));
        REQUIRE_FALSE(isAttrName("stmt# "));
        REQUIRE_FALSE(isAttrName(" stmt# "));
    }
}

TEST_CASE("Test isAttrRef") {
    SECTION("Valid AttrRef") {
        REQUIRE(isAttrRef("x.procName"));
        REQUIRE(isAttrRef("x.varName"));
        REQUIRE(isAttrRef("x.value"));
        REQUIRE(isAttrRef("x.stmt#"));
        REQUIRE(isAttrRef("x.stmt# "));
        REQUIRE(isAttrRef(" x.stmt#"));
        REQUIRE(isAttrRef(" x.stmt# "));
    }

    SECTION("Invalid AttrRef") {
        REQUIRE_FALSE(isAttrRef("x.procedureName"));
        REQUIRE_FALSE(isAttrRef("xvarName"));
        REQUIRE_FALSE(isAttrRef(".procName"));
        REQUIRE_FALSE(isAttrRef("x. procName"));
    }
}

TEST_CASE("Test isElem") {
    SECTION("Valid elem") {
        REQUIRE(isElem("x.procName"));
        REQUIRE(isElem("abc123"));
    }

    SECTION("Invalid elem") {
        REQUIRE_FALSE(isElem("2"));
        REQUIRE_FALSE(isElem(" "));
    }
}

TEST_CASE("Test isTuple") {
    SECTION("Valid tuple") {
        REQUIRE(isTuple("x.procName"));
        REQUIRE(isTuple("<x, x>"));
        REQUIRE(isTuple("<a.stmt#, x>"));
        REQUIRE(isTuple("<x, x.procName>"));
        REQUIRE(isTuple("<a.stmt#, x.procName>"));
        REQUIRE(isTuple("<a.stmt#, x.procName, x>"));
    }

    SECTION("Invalid tuple") {
        REQUIRE_FALSE(isTuple("x, x>"));
        REQUIRE_FALSE(isTuple("<x, x"));
        REQUIRE_FALSE(isTuple("<x x>"));
        REQUIRE_FALSE(isTuple("x, x"));
    }
}

TEST_CASE("Test isResultCl") {
    SECTION("Valid ResultCl") {
        REQUIRE(isResultCl("BOOLEAN"));
        REQUIRE(isResultCl("<x, x>"));
    }
}

TEST_CASE("Test findsStmtRefArgType") {
    SECTION("Valid ArgType") {
        REQUIRE(findsStmtRefArgType("_") == ArgType::WILDCARD);
        REQUIRE(findsStmtRefArgType("h1") == ArgType::SYNONYM);
        REQUIRE(findsStmtRefArgType("4") == ArgType::CONSTANT);
    }
}

TEST_CASE("Test findsEntRefArgType") {
    SECTION("Valid ArgType") {
        REQUIRE(findsEntRefArgType("_") == ArgType::WILDCARD);
        REQUIRE(findsEntRefArgType("h1") == ArgType::SYNONYM);
        REQUIRE(findsEntRefArgType("\"x + 1\"") == ArgType::EXPRESSION);
        REQUIRE(findsEntRefArgType("'y - 2'") == ArgType::EXPRESSION);
    }
}

TEST_CASE("Test findsExpressionSpecArgType") {
    SECTION("Quoted Expression Spec") {
        REQUIRE(findsExpressionSpecArgType("\"x + 1\"") == ArgType::EXPRESSION);
        REQUIRE(findsExpressionSpecArgType("'y - 2'") == ArgType::EXPRESSION);
    }

    SECTION("Quoted Wildcard Expression Spec") {
        REQUIRE(findsExpressionSpecArgType("_\"x + 1\"_") == ArgType::WILDCARD_EXPR);
        REQUIRE(findsExpressionSpecArgType("_'y - 2'_") == ArgType::WILDCARD_EXPR);
    }

    SECTION("Wildcard") {
        REQUIRE(findsExpressionSpecArgType("_") == ArgType::WILDCARD);
    }
}

TEST_CASE("Test findsRefArgType") {
    SECTION("Valid ArgType") {
        REQUIRE(findsRefArgType("\"var2\"") == ArgType::EXPRESSION);
        REQUIRE(findsRefArgType("'Third'") == ArgType::EXPRESSION);
        REQUIRE(findsRefArgType("5") == ArgType::CONSTANT);
        REQUIRE(findsRefArgType("c.procName") == ArgType::ATTRREF);
    }
}

TEST_CASE("Test isWith") {
    SECTION("Valid with") {
        REQUIRE(isWith("with"));
    }

    SECTION("Invalid with") {
        REQUIRE_FALSE(isWith("With"));
    }
}

TEST_CASE("Test isRef") {
    SECTION("Valid ref") {
        REQUIRE(isRef("\"var2\""));
        REQUIRE(isRef("'Third'"));
        REQUIRE(isRef("5"));
        REQUIRE(isRef("c.procName"));
    }

    SECTION("Invalid ref") {
        REQUIRE_FALSE(isRef("var2"));
        REQUIRE_FALSE(isRef("-"));
        REQUIRE_FALSE(isRef("_"));
        REQUIRE_FALSE(isRef("cprocName"));
    }
}

TEST_CASE("Test isAttrCompare") {
    SECTION("Valid attrCompare") {
        REQUIRE(isAttrCompare("\"hello\"=\"var2\""));
        REQUIRE(isAttrCompare("\"hello\" = \"var2\""));
        REQUIRE(isAttrCompare("'hello' = \"var2\""));
        REQUIRE(isAttrCompare("\"hello\" = 'var2'"));
        REQUIRE(isAttrCompare("'hello' = 'var2'"));
        REQUIRE(isAttrCompare("q.procName=\"var2\""));
        REQUIRE(isAttrCompare("\"var2\"=q.procName"));
        REQUIRE(isAttrCompare("q.stmt#=5"));
        REQUIRE(isAttrCompare("12=5"));
    }

    SECTION("Invalid attrCompare") {
        REQUIRE_FALSE(isAttrCompare("'hello' 'var2'"));
        REQUIRE_FALSE(isAttrCompare("12-5"));
        REQUIRE_FALSE(isAttrCompare("c.procName=p.wrongAttrName"));
        REQUIRE_FALSE(isAttrCompare("'hello = var2'"));
    }
}

TEST_CASE("Test validatePatternType") {
    SECTION("Valid patternType") {
        REQUIRE_NOTHROW(validatePatternType(EntityType::ASSIGN, "(s, \"x * y + z\")"));
        REQUIRE_NOTHROW(validatePatternType(EntityType::WHILE, "(s, _)"));
        REQUIRE_NOTHROW(validatePatternType(EntityType::IF, "(s, _, _)"));
    }

    SECTION("Invalid patternType") {
        // Incorrect number of args
        REQUIRE_THROWS(validatePatternType(EntityType::ASSIGN, "(s, \"x * y + z\", _)"));
        REQUIRE_THROWS(validatePatternType(EntityType::WHILE, "(s, _, _)"));
        REQUIRE_THROWS(validatePatternType(EntityType::IF, "(s, _)"));

        // Incorrect arg types
        REQUIRE_THROWS(validatePatternType(EntityType::WHILE, "(s, \"x * y + z\")"));
        REQUIRE_THROWS(validatePatternType(EntityType::IF, "(s, \"x * y + z\", _)"));
        REQUIRE_THROWS(validatePatternType(EntityType::IF, "(s, \"x * y + z\", v)"));
    }
}

TEST_CASE("Test isNot") {
    SECTION("Valid not") {
        REQUIRE(isNot("not"));
    }

    SECTION("Invalid with") {
        REQUIRE_FALSE(isNot("Not"));
    }
}