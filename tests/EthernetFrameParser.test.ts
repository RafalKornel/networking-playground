import { assertEquals } from "jsr:@std/assert/assert-equals";
import { EthernetFrameParser } from "../src/blocks/Ethernet/EthernetFrameParser.ts";

Deno.test(function parse() {
  const da = [0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc] as MacAddress;
  const sa = [0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd] as MacAddress;
  const type = 0x0806;
  const frame = new Uint8Array([0xaa, 0xbb, 0xcc]);
  const fcs = [0x11, 0x22, 0x33, 0x44];

  const packet = new Uint8Array([...da, ...sa, ...[0x08, 0x06], ...frame, ...fcs]);

  const parser = new EthernetFrameParser();
  const result = parser.parse(packet);

  const [r_da, r_sa, r_type, r_frame, r_fcs] = result;

  assertEquals(da, r_da);
  assertEquals(sa, r_sa);
  assertEquals(type, r_type);
  assertEquals(frame, r_frame);
  assertEquals(fcs, r_fcs);
});
