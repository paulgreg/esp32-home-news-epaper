/* events.json
[
  { "calendar":"","dateStart":"2021-09-25T00:00:00.000Z","summary":"", location: ""},
]
*/

struct Events {
  unsigned int size;
  boolean isToday[MAX_EVENTS];
  char date[MAX_EVENTS][25];
  char calendar[MAX_EVENTS][25];
  char summary[MAX_EVENTS][256];
};

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

void fillEventsFromJson(JSONVar json, Events* events) {
  int size = json.length();
  for (int i = 0; i < size && i < MAX_EVENTS; i++) {
    events->isToday[i] = json[i]["isToday"];
    sprintf(events->date[i], "%s", (const char*) json[i]["dateStart"]);
    sprintf(events->calendar[i], "%s", (const char*) json[i]["calendar"]);
    sprintf(events->summary[i], "%s", (const char*) json[i]["summary"]);
    decodeEscapeSequences(events->calendar[i]);
    decodeEscapeSequences(events->summary[i]);
    events->size = i + 1;
  }
}

void extractDate (char* str, char* date) { // str is like 2021-09-25T00:00:00
  date[ 0] = str[8];
  date[ 1] = str[9];
  date[ 2] = '/';
  date[ 3] = str[5];
  date[ 4] = str[6];
  if (str[11] == '0' && str[12] == '0' && str[14] == '0' && str[15] == '0') {
    date[ 5] = '\0';
  } else {
    date[ 5] = ' ';
    date[ 6] = '-';
    date[ 7] = ' ';
    date[ 8] = str[11];
    date[ 9] = str[12];
    date[10] = str[13];
    date[11] = str[14];
    date[12] = str[15];
    date[13] = '\0';
  }
}
