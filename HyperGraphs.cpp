#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
#include <string>

using namespace std;

struct Vertex
{
	int value;						//Contains the value of the current vertex
	vector<Vertex *> adjacencyList; //Contains addresses to the adjacent vertices of the vertex, equal to the value of n
	int noOfAdjacentVertices;		//Number of adjacent vertices

	Vertex(int value = -1, int n = 0) //Constructor
	{
		this->value = value;
		noOfAdjacentVertices = n; // Each vertex will have n number of adjacent vertices
		adjacencyList.clear();
	}

	void addAdjacentVertex(Vertex &v)
	{
		//Finding the available location to add the address of adjacent vertices
		for (int i = 0; i < this->adjacencyList.size(); i++)
		{
			if (adjacencyList[i]->value == v.value)
				return; //Returns if the Vertex is already present in the Adjacency List
		}
		adjacencyList.push_back(&v);
	}
};

struct HyperGraph
{
	vector<Vertex> vertices; //List of Vertices in the HyperGraph
	int noOfVertices;		 //Contains Number of vertices
	int dimension;

	HyperGraph(int n = 0)
	{
		/*
		As per definition, a hypergraph with n dimensions contains 2n number of vertices,
		each vertex has n number of adjacent vertices.
		*/
		this->noOfVertices = (int)pow(2, n);
		this->dimension = n;

		//populating the list of vertices where i indicates the number of value
		for (int i = 0; i < noOfVertices; i++)
			vertices.push_back(Vertex(i, dimension));

		//Constructing the actual graph
		constructGraph();
	}

	void constructGraph()
	{
		//constructing the graph
		for (int i = 0; i < this->noOfVertices; i++)
		{
			for (int j = 0; j < this->noOfVertices; j++)
			{
				//checking if the vertex is adjacent to other. 
				if (i != j && differAtOneBitPos(i, j))
				{
					//vertex is adjacent, so adding them in their adjacency lists.
					vertices[i].addAdjacentVertex(vertices[j]);
					vertices[j].addAdjacentVertex(vertices[i]);
				}
			}
		}
	}

	void convertToBinary(int n)
	{
		for (int i = this->dimension; i >= 0; i--)
		{
			int k = n >> i;
			if (k & 1)
				cout << "1";
			else
				cout << "0";
		}
	}

	void print()
	{
		for (int i = 0; i < this->noOfVertices; i++)
		{
			convertToBinary(vertices[i].value);
			cout << ": ";
			for (int j = 0; j < vertices[i].noOfAdjacentVertices; j++)
			{
				this->convertToBinary(vertices[i].adjacencyList[j]->value);
				cout << "\t";
			}
			cout << endl;
		}
	}

	// function to check if x is power of 2
	bool isPowerOfTwo(unsigned int x)
	{
		// First x in the below expression is
		// for the case when x is 0
		return x && (!(x & (x - 1)));
	}

	// function to check whether the two numbers
	// differ at one bit position only
	bool differAtOneBitPos(unsigned int a, unsigned int b)
	{
		return isPowerOfTwo(a ^ b);
	}

	int countSetBits(int n)
	{
		int count = 0;
		while (n)
		{
			n &= (n - 1);
			count++;
		}
		return count;
	}

	int findMinDist(int start, int end)
	{
		return countSetBits(start ^ end);
	}
};

int main()
{
	int n;
	cout << "Dimensions of Hyper Graph: ";
	cin >> n;
	HyperGraph hp(n);
	hp.print();
	string start, end;
	cout << "Minimum Distance Between Nodes: " << endl
		 << "Please Enter starting position: ";
	cin >> start;
	cout << "Please Enter ending position: ";
	cin >> end;
	cout << "The distance between nodes is: " << hp.findMinDist(stoi(start, 0, 2), stoi(end, 0, 2));
	return 0;
}