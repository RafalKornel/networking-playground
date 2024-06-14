import { DataType } from "../types.ts";

export function arrayToHex(arr: number[]): number {
  if (!arr.length) return 0;

  const hexString = arr
    .map((num) => num.toString(16).padStart(2, "0"))
    .join("");

  const hexNumber = parseInt(hexString, 16);

  return hexNumber;
}

export function hexToArray(hex: number, byteSize?: number): number[] {
  const hexString = hex.toString(16); // Convert to hexadecimal string
  const result: number[] = [];

  const hexStringDefaultPad =
    hexString.length % 2 === 0 ? hexString.length : hexString.length + 1;

  const padLength = byteSize ? byteSize * 2 : hexStringDefaultPad;

  const paddedHexString = hexString.padStart(padLength, "0");

  for (let i = 0; i < paddedHexString.length; i += 2) {
    const byteStr = paddedHexString.slice(i, i + 2);
    result.push(parseInt(byteStr, 16));
  }

  return result;
}

export function selectBytes(
  data: DataType,
  asType: "number",
  ...indices: number[]
): number;
export function selectBytes(
  data: DataType,
  asType: "array",
  ...indices: number[]
): number[];
export function selectBytes(
  data: DataType,
  asType: unknown,
  ...indices: number[]
) {
  const result: number[] = [];

  indices.sort((a, b) => a - b);

  for (const index of indices) {
    const currentValue = data.at(index);

    if (currentValue === undefined) continue;

    result.push(currentValue);
  }

  if (asType === "number") {
    return arrayToHex(result);
  } else {
    return result;
  }
}

export function getIndices(start: number, length: number) {
  return new Array(length).fill(0).map((_, i) => start + i);
}
