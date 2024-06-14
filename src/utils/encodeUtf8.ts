export function encodeUtf8(str: string): Uint8Array {
  const utf8: i32[] = [];

  for (let i = 0; i < str.length; i++) {
    let charCode = str.charCodeAt(i);

    if (charCode < 128) {
      utf8.push(charCode);
    } else if (charCode < 2048) {
      utf8.push(192 | (charCode >> 6));
      utf8.push(128 | (charCode & 63));
    } else if (charCode < 55296 || charCode >= 57344) {
      utf8.push(224 | (charCode >> 12));
      utf8.push(128 | ((charCode >> 6) & 63));
      utf8.push(128 | (charCode & 63));
    } else {
      i++;
      // Surrogate pair
      charCode =
        65536 + (((charCode & 1023) << 10) | (str.charCodeAt(i) & 1023));
      utf8.push(240 | (charCode >> 18));
      utf8.push(128 | ((charCode >> 12) & 63));
      utf8.push(128 | ((charCode >> 6) & 63));
      utf8.push(128 | (charCode & 63));
    }
  }

  const result = new Uint8Array(utf8.length);
  for (let i = 0; i < utf8.length; i++) {
    result[i] = utf8[i];
  }
  return result;
}
