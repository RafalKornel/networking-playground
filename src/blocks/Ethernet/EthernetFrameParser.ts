import { DataType } from "../../types.ts";
import { getIndices } from "../../utils/utils.ts";
import { arrayToHex, selectBytes } from "../../utils/utils.ts";

export type EthernetFrameType = [
  da: MacAddress,
  sa: MacAddress,
  type: number,
  frame: DataType,
  fcs: DataType
];

const MAC_ADDRESS_BYTE_LENGTH = 6;

export class EthernetFrameParser {
  static ARPMessageType = 0x0806;

  public parse(frame: DataType): EthernetFrameType {
    const da = this.parseMacAdress(
      selectBytes(frame, "array", 0, 1, 2, 3, 4, 5)
    );
    const sa = this.parseMacAdress(
      selectBytes(frame, "array", 6, 7, 8, 9, 10, 11)
    );

    const type = selectBytes(frame, "number", 12, 13);

    const l = frame.length;

    const rest = selectBytes(frame, "Uint8Array", ...getIndices(14, l - 4));

    const fcs = selectBytes(frame, "Uint8Array", l - 4, l - 3, l - 2, l - 1);

    return [da, sa, type, rest, fcs];
  }

  private parseMacAdress(maybeAdr: DataType | number[]): MacAddress {
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
