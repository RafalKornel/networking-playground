import { DataType, ILayer } from "../types.ts";

export class SessionLayer implements ILayer {
  constructor() {}
  receive(data: DataType): DataType {
    return data;
  }

  send(data: DataType): DataType {
    return data;
  }
}
