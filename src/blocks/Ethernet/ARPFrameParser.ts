import { DataType } from "../../types.ts";

type ARPFrameType = [
  hardwareType: byte,
  protocolType: number,
  hardwareAdressLength: 6,
  protocolAdressLength: 4,
  operation: 1 | 2,
  senderHardwareAddress: MacAddress,
  senderProtocolAdress: IP,
  targetHardwareAdress: MacAddress,
  targetProtocolAdress: IP
];

class ARPFrameParser {
  //     ARP Packet:
  // - Hardware Type: 1 (Ethernet)
  // - Protocol Type: 0x0800 (IPv4)
  // - Hardware Address Length: 6
  // - Protocol Address Length: 4
  // - Operation: 1 (ARP Request)
  // - Sender Hardware Address: AA:BB:CC:DD:EE:01
  // - Sender Protocol Address: 192.168.1.2
  // - Target Hardware Address: 00:00:00:00:00:00
  // - Target Protocol Address: 192.168.1.3
  parse(frame: DataType): ARPFrameType {
    throw new Error("Missing implementation");
  }
}
