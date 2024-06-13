import { DataType } from "../../types.ts";
import { arrayToHex } from "../../utils.ts";

export type EthernetFrameType = [
  da: MacAddress,
  sa: MacAddress,
  type: number,
  frame: DataType,
  fcs: [byte, byte, byte, byte]
];

const MAC_ADDRESS_BYTE_LENGTH = 6;

export class EthernetFrameParser {
  static ARPMessageType = 0x0806;

  public parse(frame: DataType): EthernetFrameType {
    const da = this.parseMacAdress(frame.subarray(0, MAC_ADDRESS_BYTE_LENGTH));
    const sa = this.parseMacAdress(
      frame.subarray(MAC_ADDRESS_BYTE_LENGTH, 2 * MAC_ADDRESS_BYTE_LENGTH)
    );

    const type = this.parseType(
      frame.subarray(
        2 * MAC_ADDRESS_BYTE_LENGTH,
        2 * MAC_ADDRESS_BYTE_LENGTH + 2
      )
    );

    const rest = frame.subarray(
      2 * MAC_ADDRESS_BYTE_LENGTH + 2,
      frame.length - 4
    );

    const fcs = this.parseFCS(frame.subarray(frame.length - 4));

    return [da, sa, type, rest, fcs];
  }

  private parseMacAdress(maybeAdr: DataType): MacAddress {
    if (maybeAdr.length !== MAC_ADDRESS_BYTE_LENGTH) {
      throw new Error(`Incorrect Mac adress: ${maybeAdr.toLocaleString()}`);
    }

    return [...maybeAdr] as unknown as MacAddress;
  }

  private parseFCS(fcs: DataType) {
    if (fcs.length !== 4) {
      throw new Error(`Invalid length of FCS: expected 4, got ${fcs.length}`);
    }

    return [...fcs] as unknown as [byte, byte, byte, byte];
  }

  private parseType(type: DataType) {
    if (type.length !== 2) {
      throw new Error(`Invalid type`);
    }

    return arrayToHex([...type]);
  }
}
