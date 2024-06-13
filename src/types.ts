export type DataType = Uint32Array;

export interface ILayer {
  up(data: DataType): DataType;
  down(data: DataType): DataType;
}

export interface IComposer {
  add(layer: ILayer): IComposer;

  propagateDown(data: DataType): DataType;
  propagateUp(data: DataType): DataType;
}
