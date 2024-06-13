import { DataType, ILayer } from "../types.ts";

export class PresentationLayer implements ILayer {
  constructor() {}
  receive(data: DataType): DataType {
    return data;
  }

  send(data: DataType): DataType {
    return data;
  }
}
