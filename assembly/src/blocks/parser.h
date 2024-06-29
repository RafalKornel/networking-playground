#if !defined(PARSER_H)
#define PARSER_H
#include "ethernet.h"
#include <memory>

using namespace std;

EthernetPhysicalFrame parsePhysicalFrame(unique_ptr<uint8_t[]> buffer);
EthernetDataLinkFrame parseDataLinkFrame(unique_ptr<uint8_t[]> buffer,
                                         int length);

#endif // MACRO
