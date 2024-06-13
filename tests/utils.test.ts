import { assertEquals } from "jsr:@std/assert";
import { arrayToHex, decodeUtf8, encodeUtf8 } from "../src/utils.ts";

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

Deno.test(function encodeTest() {
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
      console.log();
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

Deno.test(function arrayToHexTest() {
  assertEquals(arrayToHex([0x08, 0x06]), 0x0806);
  assertEquals(arrayToHex([0x08]), 0x08);
  assertEquals(arrayToHex([0x08, 0xff]), 0x08ff);
});
