import { DataType, ILayer } from "../types";

export class TransportLayer implements ILayer {
  constructor() {}
  up(data: DataType): DataType {
    return data;
  }

  down(data: DataType): DataType {
    return data;
  }
}
