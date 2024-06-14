import { assertEquals } from "jsr:@std/assert/assert-equals";
import { EthernetFrameParser } from "../src/blocks/Ethernet/EthernetFrameParser.ts";
import {
  hexToArray,
  hexToDataFrame,
  hexToMacAdress,
} from "../src/utils/utils.ts";

Deno.test("EthernetFrameParser", function () {
  const da = hexToMacAdress(0xaabbccddeeff);
  const sa = hexToMacAdress(0xdddddddddddd);
  const type = 0x0806;
  const frame = hexToDataFrame(0xaabbcc);
  const fcs = hexToArray(0xaabb);

  const packet = new Uint8Array([
    ...da,
    ...sa,
    ...hexToArray(type, 4),
    ...frame,
    ...fcs,
  ]);

  const parser = new EthernetFrameParser();
  const result = parser.parse(packet);

  const [r_da, r_sa, r_type, r_frame, r_fcs] = result;

  assertEquals(r_da, da);
  assertEquals(r_sa, sa);
  assertEquals(r_type, type);
  assertEquals(r_frame, frame);
  assertEquals(r_fcs, fcs);
});
