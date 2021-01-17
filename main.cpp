/*
    Avi Fischer 20836726
    Sudarshan Maramganty 20837062
*/


#include "final_assignment_test.hpp"

int main()
{
    FinalAssignmentTest tester;
    if(tester.test1())
        std::cout << "Test 1 passed 😊";
    else
        std::cout << "Test 1 Failed 😢";

    std::cout << std::endl << std::endl;

    if(tester.test2())
        std::cout << "Test 2 passed 😊";
    else
        std::cout << "Test 2 Failed 😢";
        
    std::cout << std::endl << std::endl;

    if(tester.test3())
        std::cout << "Test 3 passed 😊";
    else
        std::cout << "Test 3 Failed 😢";

    std::cout << std::endl << std::endl;

    if(tester.test4())
        std::cout << "Test 4 passed 😊";
    else
        std::cout << "Test 4 Failed 😢";
    
    std::cout << std::endl << std::endl;
    return 0;
}