#include "TestWrapper.h"

#include "PKB/PKB.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
    if (wrapper == 0)
        wrapper = new TestWrapper;
    return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
    // create any objects here as instance variables of this class
    // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
    SPA spa = SPA(pkb);
    spa.parse(filename);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results) {
    // store the answers to the query in the results list (it is initially empty)
    // each result must be a string.
    SPA spa = SPA(pkb);
    vector<string> queryResults = spa.evaluate(query);
    for (const std::string& result : queryResults) {
        results.push_back(result);
    }
}
