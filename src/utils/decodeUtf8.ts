
export function decodeUtf8(data: Uint8Array): string {
  let str = "";
  let i = 0;

  while (i < data.length) {
    let value = data[i];

    if (value < 128) {
      // 1-byte sequence
      str += String.fromCharCode(value);
      i++;
    } else if (value < 224) {
      // 2-byte sequence
      let charCode = ((value & 31) << 6) | (data[i + 1] & 63);
      str += String.fromCharCode(charCode);
      i += 2;
    } else if (value < 240) {
      // 3-byte sequence
      let charCode = ((value & 15) << 12) |
        ((data[i + 1] & 63) << 6) |
        (data[i + 2] & 63);
      str += String.fromCharCode(charCode);
      i += 3;
    } else {
      // 4-byte sequence (surrogate pair)
      let charCode = ((value & 7) << 18) |
        ((data[i + 1] & 63) << 12) |
        ((data[i + 2] & 63) << 6) |
        (data[i + 3] & 63);
      charCode -= 65536;
      str +=
        String.fromCharCode((charCode >> 10) + 55296) +
        String.fromCharCode((charCode & 1023) + 56320);
      i += 4;
    }
  }

  return str;
}
