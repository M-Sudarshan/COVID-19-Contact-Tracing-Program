/*
    Avi Fischer 20836726
    Sudarshan Maramganty 20837062
*/


#include "final_assignment.hpp"

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

Graph::GraphNode* Graph::get_pointer_to_node(std::string identifier)
{
    for(int i = 0; i < this->nodes.size(); i ++)
    {
        if(this->nodes[i]->identifier == identifier)
            return this->nodes[i];
    }
    return nullptr;
}

bool Graph::add_node(Graph::GraphNode val, std::vector<std::string> connectedPeople, std::vector<unsigned int> connectedWeights, std::vector<std::string> contactLocations)
{
    Graph::GraphNode *toAdd = new GraphNode(val);
    toAdd->connectedWeights = connectedWeights;
    toAdd->contactLocations = contactLocations;

    std::vector<Graph::GraphNode*> connectedNodes;

    for(int i = 0; i < connectedPeople.size(); i++)
    {
        Graph::GraphNode* person = this->get_pointer_to_node(connectedPeople[i]);
        if(person == nullptr)
            return false;
        connectedNodes.push_back(person);
    }

    toAdd->connectedNodes = connectedNodes;

    for(int i = 0; i < toAdd->connectedNodes.size(); i ++)
    {
        toAdd->connectedNodes[i]->connectedNodes.push_back(toAdd);
        toAdd->connectedNodes[i]->connectedWeights.push_back(toAdd->connectedWeights[i]);
        toAdd->connectedNodes[i]->contactLocations.push_back(toAdd->contactLocations[i]);
    }

    this->nodes.push_back(toAdd);

    return true;
}

bool Graph::load_graph(std::string file_name)
{
    std::ifstream input(file_name);
    
    if(!input.is_open())
        return true;

    std::string line;
    while(getline(input, line)){
        if(line.size() != 0 && line.at(0) != '#')
        {
            std::string identifier = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            std::string firstName = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);
            bool isPositive = line.substr(0, line.find(",")) == "1" ? true : false;
            line = line.substr(line.find(",") + 1);
            std::string testDate = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1);

            Graph::GraphNode *newNode = new Graph::GraphNode(identifier, firstName, isPositive, testDate);

            std::vector<std::string>connectedPeople;
            std::vector<unsigned int>connectedWeights;
            std::vector<std::string>contactLocations;

            while(line.size() != 0){
                connectedPeople.push_back(line.substr(0, line.find(",")));
                line = line.substr(line.find(",") + 1);
                connectedWeights.push_back(std::stoi(line.substr(0, line.find(","))));
                line = line.substr(line.find(",") + 1);
                contactLocations.push_back(line.substr(0, line.find(",")));
                line = line.substr(line.find(",") + 1);
            }

            if(! add_node(*newNode, connectedPeople, connectedWeights, contactLocations))
                return true;
        }
    }

    return false;
}

bool check_if_node_in_visited(Graph::GraphNode* node, std::vector<Graph::GraphNode*> visited)
{
    for(int i = 0; i < visited.size(); i ++)
    {
        if(*node == *visited[i])
            return true;
    }
    return false;
}

bool Graph::store_graph(std::string file_name)
{
    std::ofstream output(file_name);
    if(! output.is_open())
        return true;
    
    std::vector<Graph::GraphNode*> visited;

    std::queue<Graph::GraphNode*> nodeQueue;

    // implementing breadth first search
    for(int j = 0; j < this->nodes.size(); j ++) {
        nodeQueue.push(nodes[j]);
        if(! check_if_node_in_visited(this->nodes[j], visited)) {
            while(! nodeQueue.empty()) {
                if(! check_if_node_in_visited(nodeQueue.front(), visited))
                {
                    // writing information to file
                    output << nodeQueue.front()->identifier << "," << nodeQueue.front()->firstName << ",";
                    output << (nodeQueue.front()->isPositive ? "1":"0") << "," << nodeQueue.front()->testDate << ",";

                    // pushing unvisited nodes to the queue
                    for(int i = 0; i < nodeQueue.front()->connectedNodes.size(); i ++)
                    {
                        if(! check_if_node_in_visited(nodeQueue.front()->connectedNodes[i], visited))
                        {
                            nodeQueue.push(nodeQueue.front()->connectedNodes[i]);
                        } else {
                            output << nodeQueue.front()->connectedNodes[i]->identifier << ",";
                            output << nodeQueue.front()->connectedWeights[i] << ",";
                            output << nodeQueue.front()->contactLocations[i] << ",";
                        }
                    }
                    output << std::endl;
                    visited.push_back(nodeQueue.front());
                }
                nodeQueue.pop();
            }
        }
    }

    output.close();

    return false;
}

int Graph::count_virus_positive_contacts(std::string person_id){
    Graph::GraphNode* start = get_pointer_to_node(person_id);
    std::vector<Graph::GraphNode*> visited;
    std::stack<Graph::GraphNode*> nodeStack;
    int count = 0;

    // if the person does not exist in the graph, returns -1 
    if(start == nullptr)
        return -1;

    nodeStack.push(start);

    // implements depth first traversal
    while(! nodeStack.empty())
    {
        if(! check_if_node_in_visited(nodeStack.top(), visited)){
            // increases count if the current node is positive and not the root node
            if(nodeStack.top()->isPositive && nodeStack.top()->identifier != person_id)
                count ++;

            for(int i = 0; i < nodeStack.top()->connectedNodes.size(); i ++)
            {
                if(! check_if_node_in_visited(nodeStack.top()->connectedNodes[i], visited))
                    nodeStack.push(nodeStack.top()->connectedNodes[i]);
            }
            visited.push_back(nodeStack.top());
        }
        nodeStack.pop();
    }

    return count;
}

int Graph::find_largest_cluster_with_two_positives() const
{
    std::vector<Graph::GraphNode*> visited;
    int biggest_cluster_size = -1;
    std::queue<Graph::GraphNode*> nodeQueue;

    // iterating through all nodes stored in the graph, if the node is not visited does breadth first traversal
    for(int i = 0; i < this->nodes.size(); i ++)
    {
        if(! check_if_node_in_visited(this->nodes[i], visited))
        {
            nodeQueue.push(this->nodes[i]);
            std::vector<Graph::GraphNode*> cluster;
            // breadth first traversal, reads all nodes into the cluster
            while(! nodeQueue.empty())
            {
                if(! check_if_node_in_visited(nodeQueue.front(), visited))
                {
                    // adds neighbours to queue
                    for(int j = 0; j < nodeQueue.front()->connectedNodes.size(); j ++)
                    {
                        if(! check_if_node_in_visited(nodeQueue.front()->connectedNodes[j], visited))
                        {
                            nodeQueue.push(nodeQueue.front()->connectedNodes[j]);
                        }
                    }
                    visited.push_back(nodeQueue.front());
                    cluster.push_back(nodeQueue.front());
                }
                nodeQueue.pop();
            }
            bool more_than_two = cluster_positive_check(cluster);
            int cluster_size = cluster.size();
            // increases biggest size variable if there are two or more cases in the cluster
            if(biggest_cluster_size < cluster_size && more_than_two)
                biggest_cluster_size = cluster.size();
        }
    }

    return biggest_cluster_size;
}

bool Graph::cluster_positive_check(std::vector<Graph::GraphNode*> clusters) const{
    int count = 0;
     for(int i = 0; i < clusters.size(); i ++)
    {
        if(clusters[i]->isPositive){
            count++;
        } 
    }
    if (count>=2){return true;}
    else{return false;} 
}
