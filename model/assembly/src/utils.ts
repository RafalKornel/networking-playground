export function encodeUtf8(str: string): Uint32Array {
  const utf8: i32[] = [];

  for (let i = 0; i < str.length; i++) {
    let charCode = str.charCodeAt(i);

    if (charCode < 0x80) {
      utf8.push(charCode);
    } else if (charCode < 0x800) {
      utf8.push(0xc0 | (charCode >> 6));
      utf8.push(0x80 | (charCode & 0x3f));
    } else if (charCode < 0xd800 || charCode >= 0xe000) {
      utf8.push(0xe0 | (charCode >> 12));
      utf8.push(0x80 | ((charCode >> 6) & 0x3f));
      utf8.push(0x80 | (charCode & 0x3f));
    } else {
      i++;
      // Surrogate pair
      charCode =
        0x10000 + (((charCode & 0x3ff) << 10) | (str.charCodeAt(i) & 0x3ff));
      utf8.push(0xf0 | (charCode >> 18));
      utf8.push(0x80 | ((charCode >> 12) & 0x3f));
      utf8.push(0x80 | ((charCode >> 6) & 0x3f));
      utf8.push(0x80 | (charCode & 0x3f));
    }
  }

  const result = new Uint32Array(utf8.length);
  for (let i = 0; i < utf8.length; i++) {
    result[i] = utf8[i];
  }
  return result;
}

export function decodeUtf8(data: Uint32Array): string {
  let str = "";
  let i = 0;

  while (i < data.length) {
    let value = data[i];

    if (value < 0x80) {
      // 1-byte sequence
      str += String.fromCharCode(value);
      i++;
    } else if (value < 0xe0) {
      // 2-byte sequence
      let charCode = ((value & 0x1f) << 6) | (data[i + 1] & 0x3f);
      str += String.fromCharCode(charCode);
      i += 2;
    } else if (value < 0xf0) {
      // 3-byte sequence
      let charCode =
        ((value & 0x0f) << 12) |
        ((data[i + 1] & 0x3f) << 6) |
        (data[i + 2] & 0x3f);
      str += String.fromCharCode(charCode);
      i += 3;
    } else {
      // 4-byte sequence (surrogate pair)
      let charCode =
        ((value & 0x07) << 18) |
        ((data[i + 1] & 0x3f) << 12) |
        ((data[i + 2] & 0x3f) << 6) |
        (data[i + 3] & 0x3f);
      charCode -= 0x10000;
      str +=
        String.fromCharCode((charCode >> 10) + 0xd800) +
        String.fromCharCode((charCode & 0x3ff) + 0xdc00);
      i += 4;
    }
  }

  return str;
}
