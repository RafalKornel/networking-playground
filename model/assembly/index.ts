import { Composer } from "./src/composer";

import { ApplicationLayer } from "./src/layers/application";
import { PresentationLayer } from "./src/layers/presentation";
import { SessionLayer } from "./src/layers/session";
import { NetworkLayer } from "./src/layers/network";
import { TransportLayer } from "./src/layers/transport";
import { DataLinkLayer } from "./src/layers/data-link";
import { PhysicalLayer } from "./src/layers/physical";
import { decodeUtf8, encodeUtf8 } from "./src/utils";

export function run(): boolean {
  const composer = new Composer()
    .add(new PhysicalLayer())
    .add(new DataLinkLayer())
    .add(new NetworkLayer())
    .add(new TransportLayer())
    .add(new SessionLayer())
    .add(new PresentationLayer())
    .add(new ApplicationLayer());

  const message = "hello";

  const rawData = composer.propagateDown(encodeUtf8(message));

  const retrievedMessage = composer.propagateUp(rawData);

  return message === decodeUtf8(retrievedMessage);
}

function abort(message: usize, fileName: usize, line: u32, column: u32): void {}
