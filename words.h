#define LANG_LEN 5
#define TRANS_LEN 50
#define NB_LANG 6

struct Words {
  char languages[NB_LANG][LANG_LEN];
  char translations[NB_LANG][TRANS_LEN];
};

/* word-of-the-day.json
{"languages":["en:","fr:","sp:","it:","po:","jp:"],"translations":["toe","doigt","punter\\xeda","mignolo","ponta",""]}
*/

boolean fillWordsFromJson(JSONVar json, Words* data) {
  if (!json.hasOwnProperty("languages")) {
    Serial.println("fillWordsFromJson: languages not found");
    return false;
  }
  if (!json.hasOwnProperty("translations")) {
    Serial.println("fillWordsFromJson: translations not found");
    return false;
  }

  for (int i = 0; i < NB_LANG; i++) {
    sprintf(data->languages[i], "%s", (const char*) json["languages"][i]);
    sprintf(data->translations[i], "%s", (const char*) json["translations"][i]);
    decodeEscapeSequences(data->translations[i]);
  }
  
  return true;
}