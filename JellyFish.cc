#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "JellyFishHelper.h"


// namespace ns3 {
using namespace ns3;



JellyFishHelper::JellyFishHelper(uint32_t nTopOfRackSwitch, uint32_t nPort, uint32_t nServer,
                              CsmaHelper switchToSwitch, CsmaHelper switchToServer) {
  m_switches.Create(nTopOfRackSwitch);
  m_servers.Create(nTopOfRackSwitch * nServer);

  std::vector<std::pair<int,int>> edges = edgeSet(nTopOfRackSwitch, nPort, nPort - nServer);

  NodeContainer temp;

  for(uint32_t i = 0; i < edges.size(); ++i) {
    std::pair<uint32_t,uint32_t> edge = edges[i];
    temp.Add(m_switches.Get(edge.first));
    temp.Add(m_switches.Get(edge.second));
    switchToSwitch.Install(temp);
  }


}

JellyFishHelper::~JellyFishHelper() {

}

std::vector<std::pair<int,int>> JellyFishHelper::edgeSet(int switches, int ports, int switchPorts) {
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
  for(int i=0;i<(int)remainingSwitches.size();i++)
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

    for(int j=0;j<(int)additionalEdges.size();j++)
    {
      edgeSet.push_back(additionalEdges[j]);
    }
  }

  return edgeSet;
}

// }

















// NS_LOG_COMPONENT_DEFINE ("SecondScriptExample");
// funcUs(){
  
// }
// int 
// main (int argc, char *argv[])
// {
//   bool verbose = true;
//   // uint32_t nCsma = 3;

//   uint32_t nTopOfRackSwitch=5;
//   // uint32_t nPort , uint32_t nServer; 
//   NodeContainer m_switches; 
//   NodeContainer switches[4]; 
//   m_switches.Create (nTopOfRackSwitch);
//   // m_servers.Create (nTopOfRackSwitch*nServer);
//   std::vector< std::pair<uint32_t,uint32_t>> edges;
//   edges.push_back({1,0});
//   edges.push_back({1,2});
//   edges.push_back({1,3});
//   edges.push_back({1,4});
//   CsmaHelper switchToSwitch;
//   switchToSwitch.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
//   switchToSwitch.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));
//   for(uint32_t i = 0; i < edges.size(); ++i) {
//     std::pair<uint32_t,uint32_t> edge = edges[i];
//     NodeContainer temp;
//     temp.Add(m_switches.Get(edge.first));
//     temp.Add(m_switches.Get(edge.second));
//     switchToSwitch.Install(temp);
//     switches[i]=temp;
//   }

//   CommandLine cmd;
//   cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
//   cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

//   cmd.Parse (argc,argv);

//   if (verbose)
//     {
//       LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
//       LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
//     }


//   Simulator::Run ();
//   Simulator::Destroy ();
//   return 0;
// }