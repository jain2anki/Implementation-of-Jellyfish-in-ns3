#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SecondScriptExample");
funcUs(){
  
}
int 
main (int argc, char *argv[])
{
  bool verbose = true;
  // uint32_t nCsma = 3;

  uint32_t nTopOfRackSwitch=5;
  // uint32_t nPort , uint32_t nServer; 
  NodeContainer m_switches; 
  NodeContainer switches[4]; 
  m_switches.Create (nTopOfRackSwitch);
  // m_servers.Create (nTopOfRackSwitch*nServer);
  std::vector< std::pair<uint32_t,uint32_t>> edges;
  edges.push_back({1,0});
  edges.push_back({1,2});
  edges.push_back({1,3});
  edges.push_back({1,4});
  CsmaHelper switchToSwitch;
  switchToSwitch.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  switchToSwitch.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));
  for(uint32_t i = 0; i < edges.size(); ++i) {
    std::pair<uint32_t,uint32_t> edge = edges[i];
    NodeContainer temp;
    temp.Add(m_switches.Get(edge.first));
    temp.Add(m_switches.Get(edge.second));
    switchToSwitch.Install(temp);
    switches[i]=temp;
  }

  CommandLine cmd;
  cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

  cmd.Parse (argc,argv);

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }


  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}