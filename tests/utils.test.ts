import { assertEquals } from "jsr:@std/assert";
import {
  getIndices,
  hexToArray,
  selectBytes,
  decodeUtf8,
  encodeUtf8,
  arrayToHex,
} from "../src/utils/index.ts";

const createUint32Array = (data: number[]): Uint8Array => new Uint8Array(data);

// Test cases
const testCases: { stringData: string; rawData: Uint8Array }[] = [
  // Test case 1: ASCII characters
  { stringData: "Hello", rawData: createUint32Array([72, 101, 108, 108, 111]) },

  // Test case 2: Latin-1 Supplement characters
  {
    stringData: "Çüéñ",
    rawData: createUint32Array([195, 135, 195, 188, 195, 169, 195, 177]),
  },

  // Test case 3: Latin Extended-A characters
  {
    stringData: "ĀāĂă",
    rawData: createUint32Array([196, 128, 196, 129, 196, 130, 196, 131]),
  },

  // Test case 4: Cyrillic characters
  {
    stringData: "Привет",
    rawData: createUint32Array([
      208, 159, 209, 128, 208, 184, 208, 178, 208, 181, 209, 130,
    ]),
  },

  // Test case 5: Emoji (Smiley face)
  { stringData: "😊", rawData: createUint32Array([240, 159, 152, 138]) },
];

const VERBOSE = false;

Deno.test("encodeUtf8", function encodeTest() {
  testCases.forEach((testCase, index) => {
    const result = encodeUtf8(testCase.stringData);
    const rawDataString = testCase.rawData.toString();
    const returnValueString = result.toString();

    assertEquals(returnValueString, rawDataString);

    if (VERBOSE) {
      const resultMessage =
        returnValueString === rawDataString ? "PASS" : "FAIL";

      console.log(
        `Test case ${index + 1}: ${resultMessage} | ${
          testCase.stringData
        } => ${returnValueString}`
      );

      console.log(`Expected: ${rawDataString}`);
      console.log(`Returned: ${returnValueString}`);
    }
  });
});

Deno.test(function decodeTest() {
  testCases.forEach((testCase, index) => {
    const result = decodeUtf8(testCase.rawData);
    const rawDataString = testCase.rawData.toString();

    assertEquals(result, testCase.stringData);

    if (VERBOSE) {
      const resultMessage = result === testCase.stringData ? "PASS" : "FAIL";

      console.log(
        `Test case ${
          index + 1
        }: ${resultMessage} | ${rawDataString} => ${result}`
      );

      console.log(`Expected: ${testCase.stringData}`);
      console.log(`Returned: ${result}`);
      console.log();
    }
  });
});

Deno.test("arrayToHex", function arrayToHexTest() {
  assertEquals(arrayToHex([0x08, 0x06]), 0x0806);
  assertEquals(arrayToHex([0x08]), 0x08);
  assertEquals(arrayToHex([0x08, 0xff]), 0x08ff);
  assertEquals(arrayToHex([0x00, 0xff]), 0x00ff);
  assertEquals(arrayToHex([0x08, 0x00]), 0x0800);

  assertEquals(arrayToHex([]), 0);
});

Deno.test("hexToArray", function () {
  assertEquals(hexToArray(0x0102), [1, 2]);
  assertEquals(hexToArray(0x1010), [16, 16]);
  assertEquals(hexToArray(0x0002, 2), [0, 2]);
  assertEquals(hexToArray(0x0000, 2), [0, 0]);
  assertEquals(hexToArray(0x0000), [0]);
  assertEquals(hexToArray(0x00), [0]);
  assertEquals(hexToArray(0x0000ff), [255]);
  assertEquals(hexToArray(0x0000ff, 3), [0, 0, 255]);
  assertEquals(hexToArray(0xff00), [255, 0]);
});

Deno.test("selectBytes", function selectBytesTest() {
  const data = new Uint8Array([0xaa, 0xbb, 0xcc, 0xdd, 0x00]);

  assertEquals(selectBytes(data, "number", 0, 1), 0xaabb);
  assertEquals(selectBytes(data, "number", 0, 2), 0xaacc);
  assertEquals(selectBytes(data, "number", 0, 1, 2), 0xaabbcc);
  assertEquals(selectBytes(data, "number", 0, 2, 1), 0xaabbcc);
  assertEquals(selectBytes(data, "number", 0), 0xaa);
  assertEquals(selectBytes(data, "number", 1), 0xbb);
  assertEquals(selectBytes(data, "number", 2), 0xcc);
  assertEquals(selectBytes(data, "number", 3, 4), 0xdd00);
  assertEquals(selectBytes(data, "number", 10), 0);

  assertEquals(selectBytes(data, "array", 0, 1), [0xaa, 0xbb]);
  assertEquals(selectBytes(data, "array", 0, 2), [0xaa, 0xcc]);
  assertEquals(selectBytes(data, "array", 0, 1, 2), [0xaa, 0xbb, 0xcc]);
  assertEquals(selectBytes(data, "array", 0, 2, 1), [0xaa, 0xbb, 0xcc]);
  assertEquals(selectBytes(data, "array", 0), [0xaa]);
  assertEquals(selectBytes(data, "array", 1), [0xbb]);
  assertEquals(selectBytes(data, "array", 2), [0xcc]);
  assertEquals(selectBytes(data, "array", 3, 4), [0xdd, 0x00]);
  assertEquals(selectBytes(data, "array", 10), []);
});

Deno.test("getIndices", function () {
  assertEquals(getIndices(0, 2), [0, 1]);
  assertEquals(getIndices(10, 5), [10, 11, 12, 13, 14]);
});
