import { DataType } from "../../types.ts";
import { getIndices, selectBytes } from "../../utils/utils.ts";

type ARPFrameType = [
  hardwareType: number,
  protocolType: number,
  hardwareAdressLength: number,
  protocolAdressLength: number,
  operation: number,
  senderHardwareAddress: MacAddress,
  senderProtocolAdress: IP,
  targetHardwareAdress: MacAddress,
  targetProtocolAdress: IP
];

export class ARPFrameParser {
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
    const hardwareType = selectBytes(frame, "number", 0, 1);
    const protocolType = selectBytes(frame, "number", 2, 3);
    const hardwareLength = selectBytes(frame, "number", 4);
    const protocolLength = selectBytes(frame, "number", 5);

    const packetExpectedLength = 8 + 2 * hardwareLength + 2 * protocolLength;

    if (frame.length !== packetExpectedLength) {
      throw new Error(
        `Invalid packet. Expected ${packetExpectedLength} bytes, received ${frame.length}`
      );
    }

    const operation = selectBytes(frame, "number", 6, 7);

    let needle = 8;

    const senderHardwareAddress = selectBytes(
      frame,
      "array",
      ...getIndices(needle, hardwareLength)
    );
    needle += hardwareLength;

    const senderProtocolAdress = selectBytes(
      frame,
      "array",
      ...getIndices(needle, protocolLength)
    );
    needle += protocolLength;

    const targetHardwareAddress = selectBytes(
      frame,
      "array",
      ...getIndices(needle, hardwareLength)
    );
    needle += hardwareLength;

    const targetProtocolAddress = selectBytes(
      frame,
      "array",
      ...getIndices(needle, protocolLength)
    );

    return [
      hardwareType,
      protocolType,
      hardwareLength,
      protocolLength,
      operation,
      senderHardwareAddress as unknown as MacAddress,
      senderProtocolAdress as unknown as IPv4,
      targetHardwareAddress as unknown as MacAddress,
      targetProtocolAddress as unknown as IPv4,
    ];
  }
}
