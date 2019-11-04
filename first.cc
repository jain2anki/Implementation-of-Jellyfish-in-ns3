/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "JellyFish.cc"

using namespace ns3;

//NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);
  
  // Time::SetResolution (Time::NS);
  // LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  // LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);


  uint32_t nTopOfRackSwitch=10;
  uint32_t nPort = 8;
  uint32_t nServer = 3;
  // NodeContainer m_switches; 
  // m_switches.Create (nTopOfRackSwitch);

  CsmaHelper csma1;
  csma1.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma1.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));


  CsmaHelper csma2;
  csma2.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma2.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  JellyFishHelper jelly = JellyFishHelper(nTopOfRackSwitch, nPort, nServer, csma1, csma2);

  // std::vector< std::pair<uint32_t,uint32_t>> edges;
  // edges.push_back({1,0});
  // edges.push_back({1,2});
  // edges.push_back({0,2});
  // edges.push_back({1,3});
  // for(uint32_t i = 0; i < edges.size(); ++i) {
  //   std::pair<uint32_t,uint32_t> edge = edges[i];
  //   NodeContainer temp;
  //   temp.Add(m_switches.Get(edge.first));
  //   temp.Add(m_switches.Get(edge.second));
  //   csma.Install(temp);
  //   // switches[i]=temp;
  // }

  // CsmaHelper csma;
  // csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  // csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));


  // InternetStackHelper stack;
  // stack.Install (nodes);

  // Ipv4AddressHelper address;
  // address.SetBase ("10.1.1.0", "255.255.255.0");

  // Ipv4InterfaceContainer interfaces = address.Assign (devices);

  // UdpEchoServerHelper echoServer (9);

  // ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
  // serverApps.Start (Seconds (1.0));
  // serverApps.Stop (Seconds (10.0));

  // UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  // echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  // echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  // echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  // ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  // clientApps.Start (Seconds (2.0));
  // clientApps.Stop (Seconds (10.0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
