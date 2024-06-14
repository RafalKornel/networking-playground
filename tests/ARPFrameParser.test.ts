import { assertEquals } from "jsr:@std/assert/assert-equals";
import { ARPFrameParser } from "../src/blocks/Ethernet/ARPFrameParser.ts";
import { hexToArray } from "../src/utils/utils.ts";

Deno.test("ARPFrameParser", function ARPFrameParserTest() {
  const parser = new ARPFrameParser();

  const hardwareType = hexToArray(0x01, 2);
  const protocolType = hexToArray(0x80, 2);

  const hardwareLength = hexToArray(0x06);
  const protocolLength = hexToArray(0x04);

  const operation = hexToArray(0x01, 2);

  const senderHardwareAddress = [
    0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  ] as MacAddress;
  const senderProtocolAddress = [192, 168, 1, 1] as IPv4;

  const targetHardwareAddress = [
    0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
  ] as MacAddress;
  const targetProtocolAddress = [192, 168, 1, 2] as IPv4;

  const frame = new Uint8Array([
    ...hardwareType,
    ...protocolType,
    ...hardwareLength,
    ...protocolLength,
    ...operation,
    ...senderHardwareAddress,
    ...senderProtocolAddress,
    ...targetHardwareAddress,
    ...targetProtocolAddress,
  ]);

  console.log(frame);
  console.log(frame.length);

  assertEquals(parser.parse(frame), [
    1,
    0x80,
    6,
    4,
    1,
    senderHardwareAddress,
    senderProtocolAddress,
    targetHardwareAddress,
    targetProtocolAddress,
  ]);
});
