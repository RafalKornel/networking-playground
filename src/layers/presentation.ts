import { DataType, ILayer } from "../types.ts";

export class PresentationLayer implements ILayer {
  constructor() {}
  up(data: DataType): DataType {
    return data;
  }

  down(data: DataType): DataType {
    return data;
  }
}
