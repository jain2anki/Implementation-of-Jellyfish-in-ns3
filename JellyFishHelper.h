
#ifndef JELLY_FISH_HELPER_H
#define JELLY_FISH_HELPER_H

#include <string>
#include "ns3/csma-module.h"
// #include "ipv4-address-helper.h"
// #include "ipv6-address-helper.h"
// #include "internet-stack-helper.h"
// #include "ipv4-interface-container.h"
// #include "ipv6-interface-container.h"
using namespace ns3;
// namespace ns3 {

class JellyFishHelper
{
public:
  JellyFishHelper(uint32_t nTopOfRackSwitch, uint32_t nPort, uint32_t nServer,
                              CsmaHelper switchToSwitch, CsmaHelper switchToServer);
  ~JellyFishHelper ();
  uint32_t  SwitchCount () const;
std::vector<std::pair<int,int>> edgeSet(int switches, int ports, int switchPorts);
private:
  NodeContainer          m_servers;
  NetDeviceContainer     server_deices;
  NodeContainer          m_switches;
  NetDeviceContainer     switch_devices;
};

// } // namespace ns3
#endif /* JELLY_FISH_HELPER_H */
