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
