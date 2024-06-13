import { DataType, IComposer, ILayer } from "./types.ts";

export class Composer implements IComposer {
  /** Direction of layers: at index 0 is LOWEST layer, every layer with higher index is above */
  private _layers: ILayer[] = [];

  add(layer: ILayer): IComposer {
    this._layers.push(layer);

    return this;
  }

  propagateDown(data: DataType): DataType {
    let currData = data;

    for (let i = this._layers.length - 1; i >= 0; i--) {
      const layerReponse = this._layers[i].send(currData);
      if (!layerReponse) break;

      currData = layerReponse;
    }

    return currData;
  }

  propagateUp(data: DataType): DataType {
    let currData = data;

    for (let i = 0; i < this._layers.length; i++) {
      const layerReponse = this._layers[i].receive(currData);
      if (!layerReponse) break;

      currData = layerReponse;
    }

    return currData;
  }
}
