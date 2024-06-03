// @ts-nocheck
import { encodeUtf8 } from "../assembly/src/textEncoder"; // Assuming the function is in a separate file

// Test cases
const testCases: { input: string; expected: Uint32Array }[] = [
  // Test case 1: ASCII characters
  { input: "Hello", expected: new Uint32Array([72, 101, 108, 108, 111]) },

  // Test case 2: Latin-1 Supplement characters
  {
    input: "Çüéñ",
    expected: new Uint32Array([195, 135, 195, 188, 195, 169, 195, 177]),
  },

  // Test case 3: Latin Extended-A characters
  {
    input: "ĀāĂă",
    expected: new Uint32Array([196, 128, 196, 129, 196, 130, 196, 131]),
  },

  // Test case 4: Cyrillic characters
  {
    input: "Привет",
    expected: new Uint32Array([
      208, 159, 209, 128, 208, 184, 208, 178, 208, 181, 209, 130,
    ]),
  },

  // Test case 5: Emoji (Smiley face)
  { input: "😊", expected: new Uint32Array([240, 159, 152, 138]) },
];

// Running the test cases
testCases.forEach((testCase, index) => {
  const result = encodeUtf8(testCase.input);
  console.log(
    `Test case ${index + 1}: ${JSON.stringify(
      testCase.input
    )} => ${result.toString()}`
  );
  console.log(`Expected: ${testCase.expected.toString()}`);
  console.log(
    `Result: ${
      result.toString() === testCase.expected.toString() ? "PASS" : "FAIL"
    }`
  );
  console.log();
});
