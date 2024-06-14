import { assertEquals } from "jsr:@std/assert";
import {
  getIndices,
  hexToArray,
  selectBytes,
  arrayToHex,
} from "../src/utils/index.ts";

Deno.test("arrayToHex - regular", function arrayToHexTest() {
  assertEquals(arrayToHex([0x8, 0x6]), 0x86);
  assertEquals(arrayToHex([0x8]), 0x8);
  assertEquals(arrayToHex([0x8, 0xff]), 0x8ff);
  assertEquals(arrayToHex([0x00, 0xff]), 0x00ff);
  assertEquals(arrayToHex([0x08, 0x00]), 0x80);

  assertEquals(arrayToHex([]), 0);
});

Deno.test("arrayToHex - hexSize param", function arrayToHexTest() {
  assertEquals(arrayToHex([0x08, 0x06], 2), 0x0806);
  assertEquals(arrayToHex([0x08], 2), 0x08);
  assertEquals(arrayToHex([0x08, 0xff], 2), 0x08ff);
  assertEquals(arrayToHex([0x00, 0xff], 2), 0x00ff);
  assertEquals(arrayToHex([0x08, 0x00], 2), 0x0800);

  assertEquals(arrayToHex([], 2), 0);

  assertEquals(arrayToHex([0x800, 0x006], 3), 0x800006);
  assertEquals(arrayToHex([0x8], 3), 0x008);
  assertEquals(arrayToHex([0x080, 0xff0], 3), 0x080ff0);

  assertEquals(arrayToHex([], 3), 0);
});

Deno.test("hexToArray - regular", function () {
  assertEquals(hexToArray(0x0102), [1, 0, 2]);
  assertEquals(hexToArray(0x1010), [1, 0, 1, 0]);
  assertEquals(hexToArray(0xffff), [15, 15, 15, 15]);

  assertEquals(hexToArray(0x0000), [0]);
  assertEquals(hexToArray(0x00), [0]);
  assertEquals(hexToArray(0x0000ff), [15, 15]);
  assertEquals(hexToArray(0xff00), [15, 15, 0, 0]);
});

Deno.test("hexToArray - hexSize and byteSize param", function () {
  assertEquals(hexToArray(0x0002, 4), [0, 0, 0, 2]);
  assertEquals(hexToArray(0x0002, 2), [0, 2]);
  assertEquals(hexToArray(0x0000, 4), [0, 0, 0, 0]);
  assertEquals(hexToArray(0x1000, 4), [1, 0, 0, 0]);
  assertEquals(hexToArray(0x1000, 2), [1, 0, 0, 0]);
  assertEquals(hexToArray(0x1000, 2), [1, 0, 0, 0]);
  assertEquals(hexToArray(0x0000, 2), [0, 0]);
  assertEquals(hexToArray(0x0000, 4), [0, 0, 0, 0]);
  assertEquals(hexToArray(0x0000ff, 3), [0, 15, 15]);
  assertEquals(hexToArray(0x0000ff, 2), [15, 15]);
  assertEquals(hexToArray(0x0000ff, 4), [0, 0, 15, 15]);
  assertEquals(hexToArray(0x0000ff, 1), [15, 15]);
});

Deno.test("selectBytes - number", function selectBytesTest() {
  const data = new Uint8Array(hexToArray(0xaabbccdd00));

  assertEquals(selectBytes(data, "number", 0, 1), 0xaa);
  assertEquals(selectBytes(data, "number", 0, 2), 0xab);
  assertEquals(selectBytes(data, "number", 0, 1, 2), 0xaab);
  assertEquals(selectBytes(data, "number", 0, 2, 1), 0xaab);
  assertEquals(selectBytes(data, "number", 0), 0xa);
  assertEquals(selectBytes(data, "number", 1), 0xa);
  assertEquals(selectBytes(data, "number", 2), 0xb);
  assertEquals(selectBytes(data, "number", 3, 4), 0xbc);
  assertEquals(selectBytes(data, "number", 10), 0);
  assertEquals(selectBytes(data, "number", 11), 0);
});

Deno.test("selectBytes - array", function () {
  const data = new Uint8Array(hexToArray(0xaabbccdd00));

  assertEquals(selectBytes(data, "array", 0, 1), [0xa, 0xa]);
  assertEquals(selectBytes(data, "array", 0, 2), [0xa, 0xb]);
  assertEquals(selectBytes(data, "array", 0, 1, 2), [0xa, 0xa, 0xb]);
  assertEquals(selectBytes(data, "array", 0, 2, 1), [0xa, 0xa, 0xb]);
  assertEquals(selectBytes(data, "array", 0), [0xa]);
  assertEquals(selectBytes(data, "array", 1), [0xa]);
  assertEquals(selectBytes(data, "array", 2), [0xb]);
  assertEquals(selectBytes(data, "array", 3, 4), [0xb, 0xc]);
  assertEquals(selectBytes(data, "array", 11), []);
});

Deno.test("getIndices", function () {
  assertEquals(getIndices(0, 2), [0, 1]);
  assertEquals(getIndices(10, 5), [10, 11, 12, 13, 14]);
});
