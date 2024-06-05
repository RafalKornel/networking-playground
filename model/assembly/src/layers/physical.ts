import { DataType, ILayer } from "../types";

export class PhysicalLayer implements ILayer {
  constructor() {}
  up(data: DataType): DataType {
    return data;
  }

  down(data: DataType): DataType {
    return data;
  }
}
