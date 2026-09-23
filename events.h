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

void fillEventsFromJson(JSONVar json, Events* events) {
  events->size = 0;
  int size = json.length();
  for (int i = 0; i < size && i < MAX_EVENTS; i++) {
    const char* date = (const char*) json[i]["dateStart"];
    const char* calendar = (const char*) json[i]["calendar"];
    const char* summary = (const char*) json[i]["summary"];

    events->isToday[i] = json[i]["isToday"];
    snprintf(events->date[i], sizeof(events->date[i]), "%s", date != nullptr ? date : "");
    snprintf(events->calendar[i], sizeof(events->calendar[i]), "%s", calendar != nullptr ? calendar : "");
    snprintf(events->summary[i], sizeof(events->summary[i]), "%s", summary != nullptr ? summary : "");
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
