#include <rapidjson/document.h>
#include <rapidjson/writer.h>
 	#include <rapidjson/stringbuffer.h.
  #include <iostream>
using namespace rapidjson;
using namespace std;

int main() {
const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
  Document d;
  d.Parse(json);
Value& s = d["stars"];
s.SetInt(s.GetInt() + 1);
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
   d.Accept(writer);
cout << buffer.GetString() <<endl;
   	return 0;
}

