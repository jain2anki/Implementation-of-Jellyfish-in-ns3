#include <bits/stdc++.h>
#include<time.h>



std::vector<std::pair<int,int> > getEdgeSet(int switches,int ports,int switchPorts)
{
	std::vector<int> vec; // vector for storing switch numbers 
	int i;
	for(i=0;i<switches;i++)
		vec.push_back(i);
	std::vector<int> randomSwitches;
	srand(time(0));

	// forming a clique by randomly selecting switchPorts+1 number of switches  

	for(i=0;i<=switchPorts;i++)
	{
		int siz = vec.size();
		int index = rand()%siz;
		randomSwitches.push_back(vec[index]);
		vec.erase(vec.begin()+index);
	}

	std::vector<int> remainingSwitches = vec; // storing left over switches

	//storing edges of the clique 
	std::vector<std::pair<int,int> >edgeSet;
	for(int i=0;i<=switchPorts;i++)
	{
		for(int j=i+1;j<=switchPorts;j++)
		{
			edgeSet.push_back(std::make_pair(randomSwitches[i],randomSwitches[j]));
		}
	}

	int remainingPort=-1; // stores remaining port on any switch if any


	// adding remaining switches to the clique
	for(int i=0;i<remainingSwitches.size();i++)
	{
		std::vector<std::pair<int,int> >additionalEdges;
		int currPorts = switchPorts;
		
		// if remainingPort is there, join that switch with current switch
		if(remainingPort!=-1)
		{
			additionalEdges.push_back(std::make_pair(remainingPort,remainingSwitches[i]));
			currPorts--;
		}

		//reamove an edge and store the additional two edges 

		for(int j=1;j<currPorts;j+=2)
		{
			int siz = edgeSet.size();
			int index = rand()%siz;
			int node1 = edgeSet[index].first;
			int node2 = edgeSet[index].second;
			additionalEdges.push_back(std::make_pair(node1,remainingSwitches[i]));
			additionalEdges.push_back(std::make_pair(node2,remainingSwitches[i]));
			edgeSet.erase(edgeSet.begin()+index);			
		}

		// update the remaining Port switch if any port is left

		if(currPorts%2 == 1)
		{
			remainingPort = remainingSwitches[i];
		}

		// Move the additional edges to the edge set

		for(int j=0;j<additionalEdges.size();j++)
		{
			edgeSet.push_back(additionalEdges[j]);
		}
	}

	return edgeSet;
}

int main()
{
	int n,k,r;
	std::cin>>n>>k>>r;
	std::vector<std::pair<int,int> > v = getEdgeSet(n,k,r);

	for(int i=0;i<v.size();i++)
	{
		std::cout<<v[i].first<<" "<<v[i].second<<std::endl;
	}

	return 0;
}