/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> temp1 = graph.getVertices();
    vector<Edge> temp2 = graph.getEdges();
    int ret = 0;

    for(size_t i = 0; i < temp1.size(); i++){
    	graph.setVertexLabel(temp1[i], "UNEXPLORED");
	}

	for(size_t i = 0; i < temp2.size(); i++){
    	graph.setEdgeLabel(temp2[i].source, temp2[i].dest, "UNEXPLORED");
	}


    ret = graph.getEdgeWeight(temp2[0].source, temp2[0].dest);
    for(size_t i = 0; i < temp1.size(); i++){
        if(graph.getVertexLabel(temp1[i]) == "UNEXPLORED"){
            findMinWeightHelper(graph, temp1[i], ret);
        }
    }

    for(size_t i = 0; i < temp2.size(); i++){
        if(graph.getEdgeWeight(temp2[i].source, temp2[i].dest) == ret){
            graph.setEdgeLabel(temp2[i].source, temp2[i].dest, "MIN");
            break;
        }
    }


    return ret;
}


void GraphTools::findMinWeightHelper(Graph& graph, Vertex v, int& min){
    queue<Vertex> q;
    int ret = min;

    graph.setVertexLabel(v, "VISITED");
    q.push(v);
    while(!q.empty()){
        Vertex temp = q.front();
        q.pop();
        vector<Vertex> vertices = graph.getAdjacent(temp);
        for(size_t i = 0; i < vertices.size(); i++){
            if(graph.getVertexLabel(vertices[i]) == "UNEXPLORED"){
                graph.setEdgeLabel(temp, vertices[i], "DISCOVERY");
                graph.setVertexLabel(vertices[i], "VISITED");
                q.push(vertices[i]);
                if(graph.getEdgeWeight(temp, vertices[i]) < ret){
                    ret = graph.getEdgeWeight(temp, vertices[i]);
                }
            }
            else if(graph.getEdgeLabel(temp, vertices[i]) == "UNEXPLORED"){
                graph.setEdgeLabel(temp, vertices[i], "CROSS");
                if(graph.getEdgeWeight(temp, vertices[i]) < ret){
                    ret = graph.getEdgeWeight(temp, vertices[i]);
                }
            }
        }
    }

    min = ret;
}



/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    vector<Vertex> temp1 = graph.getVertices();
    vector<Edge> temp2 = graph.getEdges();
    int ret = 0;

    for(size_t i = 0; i < temp1.size(); i++){
        graph.setVertexLabel(temp1[i], "UNEXPLORED");
    }

    for(size_t i = 0; i < temp2.size(); i++){
        graph.setEdgeLabel(temp2[i].source, temp2[i].dest, "UNEXPLORED");
    }

    queue<Vertex> q;

    map<Vertex, Vertex> dict;

    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    while(!q.empty()){
        Vertex temp = q.front();
        q.pop();
        vector<Vertex> vertices = graph.getAdjacent(temp);
        for(size_t i = 0; i < vertices.size(); i++){
            if(graph.getVertexLabel(vertices[i]) == "UNEXPLORED"){
                graph.setEdgeLabel(temp, vertices[i], "DISCOVERY");
                graph.setVertexLabel(vertices[i], "VISITED");
                q.push(vertices[i]);
                dict.insert(pair<Vertex, Vertex>(vertices[i], temp));
                
            }
            else if(graph.getEdgeLabel(temp, vertices[i]) == "UNEXPLORED"){
                graph.setEdgeLabel(temp, vertices[i], "CROSS");
                
            }
        }
    }

    while(start != end){
        ret++;
        graph.setEdgeLabel(end, dict[end], "MINPATH");
        end = dict[end];
    }

    return ret;

}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> temp1 = graph.getVertices();
    vector<Edge> temp2 = graph.getEdges();
    DisjointSets dset;
    dset.addelements(temp1.size());
    std::sort(temp2.begin(), temp2.end());

    for(auto & it : temp2){
        if(dset.find(it.source) == dset.find(it.dest)){

        }else{
            graph.setEdgeLabel(it.source, it.dest, "MST");
            dset.setunion(it.source, it.dest);

        }
    }
}

