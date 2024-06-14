import { DataType, ILayer } from "../../types.ts";
import { EthernetFrameParser } from "./EthernetFrameParser.ts";

export class ConnectionsManager {
  private _connections: Set<EthernetDataLink> = new Set();

  constructor(private readonly maxConnections = 8) {}

  public connect(other: EthernetDataLink) {
    if (this._connections.size === this.maxConnections) return;

    this._connections.add(other);
  }

  public disconnect(other: EthernetDataLink) {
    this._connections.delete(other);
  }
}

class ARPHandler {
  private _arpTable: Map<IP, MacAddress> = new Map();

  public createARPFrame(ip: IP): DataType {
    return new Uint8Array([]);
  }

  public getMacAdress(ip: IP): MacAddress | undefined {
    return this._arpTable.get(ip);
  }
}

export class Router {}

// TODO
// - ARP
// - router implementation
// - write tests
// - write integration screnario

export class EthernetPhysical implements ILayer {
  constructor(public readonly macAddress: MacAddress) {}

  receive(data: Uint8Array): void | Uint8Array {
    try {
      const parser = new EthernetFrameParser();

      const [da, sa, type, frame, fcs] = parser.parse(data);

      if (this.isThisMyAddress(da)) {
        return;
      }

      return data;
    } catch {
      return;
    }
  }

  send(data: Uint8Array, ...args: unknown[]): void | Uint8Array {
    return data;
  }

  private isThisMyAddress(adr: MacAddress): boolean {
    if (adr === EthernetDataLink.BROADCAST_ADRESS) return true;

    return adr === this.macAddress;
  }
}

export class Ethernet implements ILayer {
  private readonly _dataLinkLayer: EthernetDataLink;
  private readonly _physicalLayer: EthernetPhysical;

  constructor(public readonly macAddress: MacAddress) {
    this._dataLinkLayer = new EthernetDataLink(macAddress);
    this._physicalLayer = new EthernetPhysical(macAddress);
  }

  receive(data: Uint8Array): void | Uint8Array {
    const physicalFrame = this._physicalLayer.receive(data);
    if (!physicalFrame) return;

    return this._dataLinkLayer.receive(physicalFrame);
  }

  send(data: Uint8Array, ip: IP): void | Uint8Array {
    const adr = this._dataLinkLayer.arpHandler.getMacAdress(ip);

    if (!adr) {
      const arpFrame = this._dataLinkLayer.arpHandler.createARPFrame(ip);

      this._physicalLayer.send(arpFrame, EthernetDataLink.BROADCAST_ADRESS);

      return;
    }

    this._physicalLayer.send(data, adr);
  }
}

class EthernetDataLink implements ILayer {
  static BROADCAST_ADRESS: MacAddress = [0xff, 0xff, 0xff, 0xff, 0xff, 0xff];

  public readonly arpHandler = new ARPHandler();

  constructor(public readonly macAddress: MacAddress) {}

  receive(frame: DataType) {
    try {
      const parser = new EthernetFrameParser();

      const [da, sa, type, rest, fcs] = parser.parse(frame);

      if (type === EthernetFrameParser.ARPMessageType) {
        return;
      } 

      
      
      return frame;
    } catch {
      return;
    }
  }

  send(data: DataType, ip: IP) {
    return data;
  }
}
