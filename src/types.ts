export type DataType = Uint8Array;

export interface ILayer {
  receive(data: DataType): DataType | void;
  send(data: DataType, ...args: unknown[]): DataType | void;
}

export interface IComposer {
  add(layer: ILayer): IComposer;

  propagateDown(data: DataType): DataType;
  propagateUp(data: DataType): DataType;
}
