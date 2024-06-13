import { DataType, ILayer } from "../../types.ts";
import { EthernetFrameParser } from "./EthernetFrameParser.ts";

export class ConnectionsManager {
  private _connections: Set<Ethernet> = new Set();

  constructor(private readonly maxConnections = 8) {}

  public connect(other: Ethernet) {
    if (this._connections.size === this.maxConnections) return;

    this._connections.add(other);
  }

  public disconnect(other: Ethernet) {
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

export class Ethernet implements ILayer {
  static BROADCAST_ADRESS: MacAddress = [0xff, 0xff, 0xff, 0xff, 0xff, 0xff];

  public readonly connectionsManager = new ConnectionsManager();

  private readonly _arpHandler = new ARPHandler();

  constructor(public readonly macAddress: MacAddress) {}

  receive(frame: DataType) {
    const dataLinkFrame = this.physicalReceive(frame);
    if (!dataLinkFrame) return;

    return this.dataLinkReceive(dataLinkFrame);
  }

  private physicalReceive(frame: DataType) {
    try {
      const parser = new EthernetFrameParser();

      const [da, sa, type, rest, fcs] = parser.parse(frame);

      if (this.isThisMyAddress(da)) {
        return;
      }

      return frame;
    } catch {
      return;
    }
  }

  private dataLinkReceive(frame: DataType) {
    try {
      const parser = new EthernetFrameParser();

      const [da, sa, type, rest, fcs] = parser.parse(frame);

      if (type === EthernetFrameParser.ARPMessageType) {
      } else {
      }

      return frame;
    } catch {
      return;
    }
  }

  send(data: DataType, ip: IP) {
    const adr = this._arpHandler.getMacAdress(ip);

    if (!adr) {
      const arpFrame = this._arpHandler.createARPFrame(ip);

      this.physicalSend(arpFrame, Ethernet.BROADCAST_ADRESS);

      return;
    }

    this.physicalSend(data, adr);
  }

  private dataLinkSend(data: DataType, ip: IP) {}

  private physicalSend(data: DataType, adr: MacAddress) {}

  private isThisMyAddress(adr: MacAddress): boolean {
    if (adr === Ethernet.BROADCAST_ADRESS) return true;

    return adr === this.macAddress;
  }
}
