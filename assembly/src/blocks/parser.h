#if !defined(PARSER_H)
#define PARSER_H
#include "ethernet.h"
#include <memory>

using namespace std;

EthernetPhysicalFrame parsePhysicalFrame(Payload payload);
EthernetDataLinkFrame parseDataLinkFrame(Payload payload);

#endif // MACRO
