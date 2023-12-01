#ifndef DAG_H
#define DAG_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Vertex {
private:
public:
     std::string question;
     std::string choices;
     char correct_answer;
     std::string response_correct;
     std::string response_incorrect;

     Vertex(const std::string& question, const std::string& choices, const char& correct_answer, const std::string& response_correct, const std::string& response_incorrect);
};

class Edge {
private:
public:
   Vertex* fromVertex;
   Vertex* toVertex;
    
   Edge(Vertex* from, Vertex* to);
};

class DAG
{
private:
     // Maps a vertex to a List of all edges that start from that vertex
     std::unordered_map<Vertex*, std::vector<Edge*>*> fromEdges;

     // Maps a vertex to an ArrayList of all edges that go to that vertex
     std::unordered_map<Vertex*, std::vector<Edge*>*> toEdges;

     Vertex* firstVertex; // "head" of the graph

public:    
     DAG();

     virtual ~DAG();

     Vertex* addVertex(std::string question, std::string choices, char correct_answer, std::string response_correct, std::string response_incorrect) ;

     Edge* addDirectedEdge(Vertex* fromVertex, Vertex* toVertex);

     // unused
     std::pair<Edge*, Edge*> addUndirectedEdge(Vertex* vertexA, Vertex* vertexB) ;

     // Returns an unordered_set of all of this graph's edges
     std::unordered_set<Edge*> getEdges() const;

     // Returns a vector of edges with the specified fromVertex
     const std::vector<Edge*>* getEdgesFrom(Vertex* fromVertex) const;

     // Returns a vector of edges with the specified toVertex
     const std::vector<Edge*>* getEdgesTo(Vertex* toVertex) const;

     // Returns a vector of all of this graph's vertices
     std::vector<Vertex*> getVertices() const;

     // Returns first vector (root?) of the graph
     Vertex* getFirstVertex();

     // Returns true if this graph has an edge from fromVertex to toVertex
     bool hasEdge(Vertex* fromVertex, Vertex* toVertex) const;

     // removes all edges in the graph and shuffles vertices, then updates adjacency list to make vertices into a randomized list
     // only run after adding the "random vertices"
     void shuffleToList();

     // Adds an edge such that if the question is answered wrong for the parent vertex,
     // the question for the 2nd vertex parameter is given to the user instead.
     // If the 1st edge in the adjacency list is filled, then the 2nd edge is used.
     // Otherwise, the 1st edge 
     void addWrongAnsEdge(Vertex* parent_vertex, Vertex* wrong_ans_vertex);

};

#endif // DAG_H
