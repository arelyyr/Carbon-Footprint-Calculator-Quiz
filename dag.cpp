#include "dag.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>

Vertex::Vertex(const std::string& question, const std::string& choices, const char& correct_answer, const std::string& response_correct, const std::string& response_incorrect)
{
    this->question = question;
    this->choices = choices;
    this->correct_answer = correct_answer;
    this->response_correct = response_correct;
    this->response_incorrect = response_incorrect;
}


Edge::Edge(Vertex* from, Vertex* to)
{
    fromVertex = from;
    toVertex = to;
}

DAG::DAG()
{
    firstVertex = nullptr;
}

DAG::~DAG() 
{
    // Get the set of vertices and the set of edges
    std::unordered_set<Vertex*> distinctVertices;
    std::unordered_set<Edge*> distinctEdges;
    for (auto& keyValue : fromEdges) 
    {
        distinctVertices.insert(keyValue.first);
        for (Edge* edge : *keyValue.second) 
        {
            distinctEdges.insert(edge);
        }
        delete keyValue.second;
    }
    for (auto& keyValue : toEdges) 
    {
        distinctVertices.insert(keyValue.first);
        for (Edge* edge : *keyValue.second) 
        {
            distinctEdges.insert(edge);
        }
        delete keyValue.second;
    }
        
    // Clear each map
    fromEdges.clear();
    toEdges.clear();
        
    // Free each edge and each vertex
    for (Edge* edge : distinctEdges) 
    {
        delete edge;
    }
    for (Vertex* vertex : distinctVertices) 
    {
        delete vertex;
    }
}

Vertex* DAG::addVertex(std::string question, std::string choices, char correct_answer, std::string response_correct, std::string response_incorrect) 
{
    // Create the new Vertex object
    Vertex* newVertex = new Vertex(question, choices, correct_answer, response_correct, response_incorrect);
        
    // Every vertex must exist as a key in both maps
    fromEdges[newVertex] = new std::vector<Edge*>();
    toEdges[newVertex] = new std::vector<Edge*>();

    if (firstVertex == nullptr)
    {
        firstVertex = newVertex;
    }
        
    return newVertex;
    }

Edge* DAG::addDirectedEdge(Vertex* fromVertex, Vertex* toVertex) 
{
    // Don't add the same edge twice
    if (hasEdge(fromVertex, toVertex)) 
    {
        return nullptr;
    }
    
    // Create the Edge object
    Edge* newEdge = new Edge(fromVertex, toVertex);
    
    // Add the edge to the appropriate list in both maps
    fromEdges[fromVertex]->push_back(newEdge);
    toEdges[toVertex]->push_back(newEdge);

    if (getEdgesFrom(fromVertex)->size() > 2) {std::cout << "fromVertex has too many edges (>2)\n";} // delete this later
    
    return newEdge;
}

// unused
std::pair<Edge*, Edge*> DAG::addUndirectedEdge(Vertex* vertexA, Vertex* vertexB) 
{
    return std::pair<Edge*, Edge*>(
        addDirectedEdge(vertexA, vertexB),
        addDirectedEdge(vertexB, vertexA));
}

// Returns an unordered_set of all of this graph's edges
std::unordered_set<Edge*> DAG::getEdges() const 
{
    std::unordered_set<Edge*> edgesSet;
    for (auto& keyValue : fromEdges) 
    {
        std::vector<Edge*>* edges = keyValue.second;
        for (Edge* edge : *edges) 
        {
            edgesSet.insert(edge);
        }
    }
    return edgesSet;
}

// Returns a vector of edges with the specified fromVertex
const std::vector<Edge*>* DAG::getEdgesFrom(Vertex* fromVertex) const {
    return fromEdges.at(fromVertex);
}

// Returns a vector of edges with the specified toVertex
const std::vector<Edge*>* DAG::getEdgesTo(Vertex* toVertex) const {
    return toEdges.at(toVertex);
}

// Returns a vector of all of this graph's vertices
std::vector<Vertex*> DAG::getVertices() const 
{
    std::vector<Vertex*> vertices;
    for (auto& keyValue : fromEdges) 
    {
        vertices.push_back(keyValue.first);
    }
    return vertices;
}

Vertex* DAG::getFirstVertex() { return firstVertex; }

// Returns true if this graph has an edge from fromVertex to toVertex
bool DAG::hasEdge(Vertex* fromVertex, Vertex* toVertex) const 
{
    if (0 == fromEdges.count(fromVertex)) 
    {
        // fromVertex is not in this graph
        return false;
    }
    
    // Search the list of edges for an edge that goes to toVertex
    std::vector<Edge*>& edges = *fromEdges.at(fromVertex);
    for (Edge* edge : edges) {
        if (edge->toVertex == toVertex) 
        {
            return true;
        }
    }
    return false;
}

void DAG::shuffleToList()
{
    // get vector of vertices
    std::vector<Vertex*> vertices = getVertices();

    if (vertices.size() <= 1) { return; }  // no adjacent vertices

    // clear adjacency list
    for (auto it = fromEdges.begin(); it != fromEdges.end(); ++it) {
        // clear the vector associated with the key in fromEdges
        it->second->clear();
    }
    for (auto it = toEdges.begin(); it != toEdges.end(); ++it) {
        // clear the vector associated with the key in toEdges
        it->second->clear();
    }

    // shuffle vector
    random_shuffle(vertices.begin(), vertices.end());

    // update firstVertex
    firstVertex = vertices.front();

    // connect vertices in order
    for (int i = 0; i < (int)vertices.size() - 1; ++i) {
        addDirectedEdge(vertices[i], vertices[i+1]);
    }

}

void DAG::addWrongAnsEdge(Vertex* parent_vertex, Vertex* wrong_ans_vertex)
{
    // add parent vertex's 2nd edge to be wrong q vertex
    if (!hasEdge(parent_vertex, wrong_ans_vertex)) // Don't add the same edge twice
    { 
        // add wrong answer vertex's 1st edge to be the same as the 1st edge of parent vertex if it exists
        if (!fromEdges[parent_vertex]->empty())
        {
            Vertex* next_vertex = fromEdges[parent_vertex]->at(0)->toVertex; // seg faults here
            addDirectedEdge(wrong_ans_vertex, next_vertex);
        }

        // Create the Edge object
        Edge* newEdge = new Edge(parent_vertex, wrong_ans_vertex);

        // note: case when adding to last vertex in the graph sets it to index 0 instead
        // Add the edge to the appropriate list in both maps (should be at index 1)
        fromEdges[parent_vertex]->push_back(newEdge);
        toEdges[wrong_ans_vertex]->push_back(newEdge);

        if (getEdgesFrom(parent_vertex)->size() > 2) {std::cout << "parent_vertex has too many edges (>2)\n";} // delete this later
    }
}

