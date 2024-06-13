import { Composer } from "./composer.ts";

import { ApplicationLayer } from "./layers/application.ts";
import { PresentationLayer } from "./layers/presentation.ts";
import { SessionLayer } from "./layers/session.ts";
import { NetworkLayer } from "./layers/network.ts";
import { TransportLayer } from "./layers/transport.ts";
import { DataLinkLayer } from "./layers/data-link.ts";
import { PhysicalLayer } from "./layers/physical.ts";
import { decodeUtf8, encodeUtf8 } from "./utils.ts";

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
