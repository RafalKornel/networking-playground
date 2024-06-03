import * as application from "./layers/application";
import * as presentation from "./layers/presentation";
import * as session from "./layers/session";
import * as network from "./layers/network";
import * as transport from "./layers/transport";
import * as dataLink from "./layers/data-link";
import * as physical from "./layers/physical";
import { encodeUtf8 } from "./textEncoder";

export function sendMessage(message: string): void {
  const data = encodeUtf8(message);

  physical.down(
    //
    dataLink.down(
      //
      transport.down(
        //
        network.down(
          //
          session.down(
            //
            presentation.down(
              //
              application.down(data)
            )
          )
        )
      )
    )
  );
}

export function digestMessage(data: Uint32Array): void {
  const message = application.up(
    //
    presentation.up(
      //
      session.up(
        //
        network.up(
          //
          transport.up(
            //
            dataLink.up(
              //
              physical.up(data)
            )
          )
        )
      )
    )
  );

  console.log(message.toString());
}
