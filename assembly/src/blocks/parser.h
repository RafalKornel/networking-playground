#ifndef PARSER_H
#define PARSER_H

#include "ethernet.h"
#include <memory>

using namespace std;

EthernetPhysicalFrame parsePhysicalFrame(Payload payload);
EthernetDataLinkFrame parseDataLinkFrame(Payload payload);

EthernetPhysicalFrame
createPhysicalFrame(const EthernetDataLinkFrame &dataLinkFrame);

void printEthernetDataLinkFrame(const EthernetDataLinkFrame &frame);
void printEthernetPhysicalFrame(const EthernetPhysicalFrame &frame);

bool compareEthernetDataLinkFrame(const EthernetDataLinkFrame &frame1,
                                  const EthernetDataLinkFrame &frame2);
bool compareEthernetPhysicalFrame(const EthernetPhysicalFrame &frame1,
                                  const EthernetPhysicalFrame &frame2);

Payload convertEthernetDataLinkFrameToPayload(EthernetDataLinkFrame frame);

#endif // MACRO
