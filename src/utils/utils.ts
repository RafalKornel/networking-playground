import { DataType } from "../types.ts";

const BYTE_SIZE_IN_HEX = 2;

export function arrayToHex(arr: number[], hexSize?: number): number {
  if (!arr.length) return 0;

  const hexString = arr
    .map((num) => num.toString(16).padStart(hexSize || BYTE_SIZE_IN_HEX, "0"))
    .join("");

  const hexNumber = parseInt(hexString, 16);

  return hexNumber;
}

export function hexToArray(hex: number, hexSize: number = 1): number[] {
  const hexString = hex.toString(16);
  const result: number[] = [];

  const paddedHexString = hexString.padStart(hexSize, "0");

  // console.log(hexString, paddedHexString);

  for (let i = 0; i < paddedHexString.length; i += BYTE_SIZE_IN_HEX) {
    const byteStr = paddedHexString.slice(i, i + BYTE_SIZE_IN_HEX);
    result.push(parseInt(byteStr, 16));
  }

  return result;
}

export function hexToDataFrame(hex: number, hexSize?: number): DataType {
  const array = hexToArray(hex, hexSize);

  return new Uint8Array(array);
}

export function hexToMacAdress(hex: number): MacAddress {
  return hexToArray(hex, 6) as unknown as MacAddress;
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
  asType: "Uint8Array",
  ...indices: number[]
): Uint8Array;
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
  }

  if (asType === "Uint8Array") {
    return new Uint8Array(result);
  }

  return result;
}

export function getIndices(start: number, length: number) {
  return new Array(length).fill(0).map((_, i) => start + i);
}
