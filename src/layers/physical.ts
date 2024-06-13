import { DataType, ILayer } from "../types.ts";

export class Bridge {}

export class PhysicalLayer implements ILayer {
  constructor(private readonly macAdress: MacAddress) {}

  receive(frame: DataType) {
    const da = frame.subarray(0, MacAdressByteLength + 1);
    const sa = frame.subarray(
      MacAdressByteLength + 1,
      2 * MacAdressByteLength + 1
    );

    if (this.isThisMyAddress(da)) {
      return;
    }

    return frame;
  }

  send(frame: DataType) {
    return frame;
  }


  private isThisMyAddress(adr: Uint8Array): boolean {
    if (adr.length !== this.macAdress.length) return false;

    for (let i = 0; i < adr.length; i++) {
      if (adr[i] !== this.macAdress[i]) return false;
    }

    return true;
  }
}
