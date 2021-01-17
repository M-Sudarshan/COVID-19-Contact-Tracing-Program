/*
    Avi Fischer 20836726
    Sudarshan Maramganty 20837062
*/

#ifndef FINAL_ASSIGNMENT_HPP
#define FINAL_ASSIGNMENT_HPP

#include <string>
#include <vector>

class Graph
{
    struct GraphNode {
        std::string identifier;
        std::string firstName;
        bool isPositive;
        std::string testDate;

        std::vector<GraphNode*> connectedNodes;
        std::vector<unsigned int> connectedWeights;
        std::vector<std::string> contactLocations;

        friend bool operator==(GraphNode &lhs, GraphNode &rhs){
            return lhs.identifier == rhs.identifier;
        }

        friend bool operator!=(GraphNode &lhs, GraphNode &rhs){
            return lhs.identifier != rhs.identifier;
        }

        GraphNode(std::string identifier, std::string firstName, bool isPositive, std::string testDate) {
            this->identifier = identifier;
            this->firstName = firstName;
            this->isPositive = isPositive;
            this->testDate = testDate;
        }

        GraphNode() {}

    };

public:
    std::vector<GraphNode*> nodes;
    GraphNode* get_pointer_to_node(std::string identifier);
    bool add_node(GraphNode val, std::vector<std::string> connectedPeople, std::vector<unsigned int> connectedWeights, std::vector<std::string> contactLocations);
    bool load_graph(std::string file_name);
    bool store_graph(std::string file_name);
    int find_largest_cluster_with_two_positives() const;
    int count_virus_positive_contacts(std::string person_id);
    int getPointerIndex(GraphNode* node);
    bool cluster_positive_check(std::vector<GraphNode*> clusters) const;

    friend bool check_if_node_in_visited(GraphNode* node, std::vector<GraphNode*>);
    friend class FinalAssignmentTest;
};

#endif