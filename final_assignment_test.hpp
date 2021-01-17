/*
    Avi Fischer 20836726
    Sudarshan Maramganty 20837062
*/

#ifndef FINAL_ASSIGNMENT_TEST_HPP
#define FINAL_ASSIGNMENT_TEST_HPP

#include "final_assignment.cpp"

#include <iostream>
#include <vector>
#include <fstream>

#define ASSERT_TRUE(x) if(!x) return false;
#define ASSERT_FALSE(x) if(x) return false;

class FinalAssignmentTest {
public:
    bool test1() {
        std::cout << "Test 1: Reading from a file" << std::endl << std::endl;
        Graph g;

        std::cout << "Reading a blank file" << std::endl;
        ASSERT_FALSE(g.load_graph("blank.txt"));
        ASSERT_TRUE(g.nodes.size() == 0);
        std::cout << "Test Passed" << std::endl << std::endl;

        std::cout << "Reading a valid graph" << std::endl;
        ASSERT_FALSE(g.load_graph("small_graph.txt"));
        ASSERT_TRUE((g.nodes.size() == 3));
        ASSERT_FALSE((g.get_pointer_to_node("0001") == nullptr));
        ASSERT_FALSE((g.get_pointer_to_node("0002") == nullptr));
        ASSERT_FALSE((g.get_pointer_to_node("0003") == nullptr));
        std::cout << "Test Passed" << std::endl << std::endl;

        Graph g2;
        std::cout << "Reading a big valid graph" << std::endl;
        ASSERT_FALSE(g2.load_graph("big_graph.txt"));
        ASSERT_TRUE((g2.nodes.size() == 15));
        std::cout << "Test Passed" << std::endl << std::endl;

        std::cout << "Opening a nonexistent file" << std::endl;
        ASSERT_TRUE(g.load_graph("nonexistent.txt"))
        std::cout << "Test Passed" << std::endl << std::endl;

        return true;
    }

    bool file_text_matches(std::string fileName, std::string text) {
        std::ifstream input(fileName);
        if(! input.is_open())
            return false;
        std::string contents = "";
        std::string line;
        while(getline(input, line))
        {
            contents.append(line);
        }
        return contents == text;
    }

    bool test2() {
        std::cout << "Test 2: Writing to file" << std::endl << std::endl;
        Graph g;

        std::cout << "Writing a graph with one node to a file" << std::endl;
        g.add_node(Graph::GraphNode("0001", "Avi", true, "03/08/2020"), std::vector<std::string>(), std::vector<unsigned int>(), std::vector<std::string>());
        ASSERT_FALSE(g.store_graph("output.txt"));
        ASSERT_TRUE(file_text_matches("output.txt", "0001,Avi,1,03/08/2020,"));
        std::cout << "Test passed" << std::endl << std::endl;

        std::cout << "Writing a graph with multiple nodes to a file" << std::endl;
        Graph g2;
        ASSERT_FALSE(g2.load_graph("small_graph.txt"));
        ASSERT_FALSE(g2.store_graph("output.txt"));
        ASSERT_TRUE(file_text_matches("output.txt", "0001,Avi,0,03/08/2020,0002,Sudarshan,0,03/08/2020,0001,2,park,0003,Igor,0,03/08/2020,0002,5,park,0001,1,park,"));
        std::cout << "Test passed" << std::endl << std::endl;

        std::cout << "Writing a graph with multiple clusters to a file" << std::endl;
        Graph g3;
        ASSERT_FALSE(g3.load_graph("big_graph.txt"));
        ASSERT_FALSE(g3.store_graph("output.txt"));
        ASSERT_TRUE(file_text_matches("output.txt", "0001,Avi,1,03/08/2020,0002,Sudarshan,0,03/08/2020,0001,2,DC,0003,Igor,1,03/08/2020,0002,5,park,0001,1,DC,0004,Joe,1,03/08/2020,0005,Bob,1,03/08/2020,0004,1,DC,0007,Sam,0,03/08/2020,0004,1,DC,0005,1,DC,0008,Alex,1,03/08/2020,0004,1,park,0005,1,park,0006,Sarah,0,03/08/2020,0005,1,DC,0007,1,DC,0008,1,park,0009,A,0,03/08/2020,0010,B,1,03/08/2020,0009,1,park,0011,C,0,03/08/2020,0009,1,cafe,0010,1,park,0012,D,0,03/08/2020,0009,1,restaurant,0010,1,park,0011,1,park,0013,E,0,03/08/2020,0009,1,park,0010,1,park,0012,1,park,0014,F,0,03/08/2020,0010,1,park,0015,G,0,03/08/2020,0012,3,park,0014,1,park,"));
        std::cout << "Test passed" << std::endl << std::endl;

        return true;
    }

    bool test3() {
        std::cout << "Test 3: Counting number of positive contacts" << std::endl << std::endl;

        std::cout << "Testing with an id not in graph" << std::endl;
        Graph g;
        ASSERT_FALSE(g.load_graph("small_graph.txt"));
        ASSERT_TRUE((g.count_virus_positive_contacts("0010") == -1));
        std::cout << "Test passed" << std::endl << std::endl;

        std::cout << "Testing with Id in graph" << std::endl;
        Graph g2;
        ASSERT_FALSE(g2.load_graph("small_graph.txt"));
        ASSERT_TRUE((g2.count_virus_positive_contacts("0001") == 0));
        std::cout << "Test passed" << std::endl << std::endl;

        std::cout << "Testing with Id in graph and multiple clusters" << std::endl;
        Graph g3;
        ASSERT_FALSE(g3.load_graph("big_graph.txt"));
        ASSERT_TRUE((g3.count_virus_positive_contacts("0007") == 3));
        std::cout << "Test passed" << std::endl << std::endl;

        std::cout << "One positive contact exists but it's the starting person" << std::endl;
        g.load_graph("small_graph2.txt");
        ASSERT_TRUE(g.count_virus_positive_contacts("0004") == 0);
        std::cout << "Test Passed" << std::endl << std::endl;
        
        return true;
    }

    bool test4() {
        std::cout << "Test 4: Finding largest cluster size with multiple cases" << std::endl << std::endl;
        Graph g;
        
        std::cout << "No clusters" << std::endl;
        ASSERT_TRUE(g.find_largest_cluster_with_two_positives() == -1);
        std::cout << "Test Passed" << std::endl << std::endl;

        std::cout << "One cluster but <2 positive tests" << std::endl;
        g.load_graph("small_graph.txt");
        ASSERT_TRUE(g.find_largest_cluster_with_two_positives() == -1);
        std::cout << "Test Passed" << std::endl << std::endl;

        std::cout << "Multiple clusters with multiple cases" << std::endl;
        Graph g2;
        g2.load_graph("big_graph.txt");
        ASSERT_TRUE((g2.find_largest_cluster_with_two_positives() == 5));
        std::cout << "Test Passed" << std::endl << std::endl;

        return true;

    }
};

#endif
