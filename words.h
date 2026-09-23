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

  if (json["languages"].length() < NB_LANG || json["translations"].length() < NB_LANG) {
    Serial.println("fillWordsFromJson: invalid languages/translations length");
    return false;
  }

  for (int i = 0; i < NB_LANG; i++) {
    const char* lang = (const char*) json["languages"][i];
    const char* translation = (const char*) json["translations"][i];

    snprintf(data->languages[i], sizeof(data->languages[i]), "%s", lang != nullptr ? lang : "");
    snprintf(data->translations[i], sizeof(data->translations[i]), "%s", translation != nullptr ? translation : "");
    decodeEscapeSequences(data->translations[i]);
  }
  
  return true;
}
