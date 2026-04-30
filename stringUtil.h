
void decodeEscapeSequences(char* str) {
  char buffer[256];
  int i = 0, j = 0;
  while (str[i] != '\0') {
    if (str[i] == '\\' && str[i+1] == 'x') {
      // Found an escape sequence like \xeda
      char hex[3] = { str[i+2], str[i+3], '\0' };  // Extract the 2 hex digits after \x
      int value = strtol(hex, NULL, 16);  // Convert hex to integer
      buffer[j++] = (char) value;  // Store the corresponding character
      i += 4;  // Skip over \x and the 2 hex digits
    } else {
      buffer[j++] = str[i++];
    }
  }
  buffer[j] = '\0';  // Null-terminate the buffer
  strcpy(str, buffer);  // Copy the processed string back into the original buffer
}
