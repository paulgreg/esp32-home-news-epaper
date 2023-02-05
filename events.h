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
  int size = json.length();
  for (int i = 0; i < size && i < MAX_EVENTS; i++) {
    events->isToday[i] = json[i]["isToday"];
    sprintf(events->date[i], "%s", (const char*) json[i]["dateStart"]);
    sprintf(events->calendar[i], "%s", (const char*) json[i]["calendar"]);
    sprintf(events->summary[i], "%s", (const char*) json[i]["summary"]);
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
    date[ 6] = str[11];
    date[ 7] = str[12];
    date[ 8] = str[13];
    date[ 9] = str[14];
    date[10] = str[15];
    date[11] = '\0';
  }
}
