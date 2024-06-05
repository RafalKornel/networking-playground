import { encodeUtf8, decodeUtf8 } from "../assembly/src/utils";

// TS-ignore due to the fact, that in this file, we use regular typescript, but in `/assembly` we use
// Assemblyscript flavour
const createUint32Array = (data: number[]): Uint32Array =>
  // @ts-expect-error
  new Uint32Array(data);

// Test cases
const testCases: { stringData: string; rawData: Uint32Array }[] = [
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

console.log("\n\nEncoder: ");
testCases.forEach((testCase, index) => {
  const result = encodeUtf8(testCase.stringData);
  const rawDataString = testCase.rawData.toString();
  const returnValueString = result.toString();

  const resultMessage = returnValueString === rawDataString ? "PASS" : "FAIL";

  console.log(
    `Test case ${index + 1}: ${resultMessage} | ${
      testCase.stringData
    } => ${returnValueString}`
  );

  if (VERBOSE) {
    console.log(`Expected: ${rawDataString}`);
    console.log(`Returned: ${returnValueString}`);
    console.log();
  }
});

console.log("\n\nDecoder: ");
testCases.forEach((testCase, index) => {
  const result = decodeUtf8(testCase.rawData);
  const rawDataString = testCase.rawData.toString();

  const resultMessage = result === testCase.stringData ? "PASS" : "FAIL";

  console.log(
    `Test case ${index + 1}: ${resultMessage} | ${rawDataString} => ${result}`
  );

  if (VERBOSE) {
    console.log(`Expected: ${testCase.stringData}`);
    console.log(`Returned: ${result}`);
    console.log();
  }
});
