#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>	
#include <cstdlib> 
#include "SimpleGraph.h"

using namespace std;

void Welcome();
string Graph_name();
SimpleGraph load_graph(const string& graph_name);
void update(SimpleGraph& graph);

const double kPi = 3.14159265358979323;

// Main method
int main() {
    Welcome();

    string graph_name = Graph_name();
    cout << graph_name << endl;


    SimpleGraph graph = load_graph(graph_name);

    cout << "init" << endl;
    InitGraphVisualizer(graph);
    DrawGraph(graph);

	    int index = 0;
	    string s;
	    while (true)
	    {
	    	update(graph);
	    	DrawGraph(graph);
	    	// index++;
	    	// cin >> s;
	    	// cout << index << endl;
	    }

    return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;
}

string Graph_name()
{
	cout << "Please enter the graph name: " << endl;

	string s;
	cin >> s;
	return s;
}

SimpleGraph load_graph(const string& graph_name)
{
	ifstream ifs;

	ifs.open(graph_name, ifstream::in);
	
	SimpleGraph graph;
	string line;

	getline(ifs, line);
	istringstream line_stream(line);
	int n;
	line_stream >> n;

	for (int i = 0; i < n; i++)
	{
		Node node;
		node.x = cos(2 * kPi * i / n);
		node.y = sin(2 * kPi * i / n);
		cout << node.x << endl;
		graph.nodes.push_back(node);
	}
	cout <<graph.nodes.size() << endl;

	
	size_t x, y;
	while(getline(ifs, line))
	{	
		
		istringstream stream(line);
		stream >> x;
		stream >> y;
		cout << x << " " << y << endl;
		Edge edge;
		edge.start = x;
		edge.end = y;
		graph.edges.push_back(edge);
		
	}
	cout << graph.edges.size() << endl;
	return graph;	
}

void update(SimpleGraph& graph)
{
	double k = 1e-3;
	double katt = 1e-3	;
	int n = graph.nodes.size();
	std::vector<Node> delta(n);

	for(Node deltas : delta) {
        deltas.x = 0.0;
        deltas.y = 0.0;
    }

	for (int i=0; i < n-1; i++)
		for (int j=i+1; j < n; j++)
		{
			double x0, y0, x1, y1;
			x0 = graph.nodes[i].x;
			y0 = graph.nodes[i].y;
			x1 = graph.nodes[j].x;
			y1 = graph.nodes[j].y;
 			
			double frepl = k / sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
			double theta = atan2(y1 - y0, x1 - x0);
			delta[i].x -= frepl * cos(theta);
			delta[i].y -= frepl * sin(theta);
			delta[j].x += frepl * cos(theta);
			delta[j].y += frepl * sin(theta);
 			
		}

	for (auto& edge: graph.edges)
	{
		int i = edge.start;
		int j = edge.end;

		double x0, y0, x1, y1;
		x0 = graph.nodes[i].x;
		y0 = graph.nodes[i].y;
		x1 = graph.nodes[j].x;
		y1 = graph.nodes[j].y;

		double f = katt * (pow(x1 - x0, 2) + pow(y1 - y0, 2));
		double theta = atan2(y1 - y0, x1 - x0);
		delta[i].x += f * cos(theta);
		delta[i].y += f * sin(theta);
		delta[j].x -= f * cos(theta);
		delta[j].y -= f * sin(theta);
	}

	for (int i=0; i < n; i++)
	{
		double rx = (rand() - RAND_MAX / 2) / (double)RAND_MAX;
		double ry = (rand() - RAND_MAX / 2) / (double)RAND_MAX;

		graph.nodes[i].x += delta[i].x;
		graph.nodes[i].y += delta[i].y;

		// graph.nodes[i].x += rx / 10000;
		// graph.nodes[i].y += ry / 10000;
	}
}
