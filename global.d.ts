export {};

declare global {
  type hex =
    | "0"
    | "1"
    | "2"
    | "3"
    | "4"
    | "5"
    | "6"
    | "7"
    | "8"
    | "9"
    | "a"
    | "b"
    | "c"
    | "d"
    | "e"
    | "f";

  type i32 = number;
  type bit = 0 | 1;
  type byte = number; // 8 bit
  type hexByte = `${hex}${hex}`;

  type MacAddress = readonly [byte, byte, byte, byte, byte, byte];

  type IPv4 = [byte, byte, byte, byte];

  type IP = IPv4;
}
