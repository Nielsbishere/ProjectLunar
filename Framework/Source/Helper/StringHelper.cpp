#include "../../Headers/Helper/StringHelper.h"
#include <sstream>
#include <algorithm>

using namespace std;
using namespace lun;

//Ends & starts with

bool StringHelper::endsWith(string source, string suffix) {
	if (source.size() < suffix.size())return false;
	return source.substr(source.size() - suffix.size()) == suffix;
}

bool StringHelper::startsWith(string source, string prefix) {
	if (source.size() < prefix.size())return false;
	return source.substr(0, prefix.size()) == prefix;
}

string StringHelper::toLowerCase(string source) {
	string res = source;
	for (u32 i = 0; i < source.size(); ++i)
		if (source[i] >= 'A' && source[i] <= 'Z')
			res[i] = source[i] - 'A' + 'a';
	return res;
}

bool StringHelper::equalsIgnoreCase(string source1, string source2) {
	return toLowerCase(source1) == toLowerCase(source2);
}

bool StringHelper::endsWithIgnoreCase(string source1, string source2) {
	return endsWith(toLowerCase(source1), toLowerCase(source2));
}

bool StringHelper::startsWithIgnoreCase(string source1, string source2) {
	return startsWith(toLowerCase(source1), toLowerCase(source2));
}

//Count

u32 StringHelper::count(std::string source, char c) {
	return (u32)std::count(source.begin(), source.end(), c);
}

u32 StringHelper::count(std::string source, std::string seeking) {
	if(seeking.size() == 0)
		return 0;

	u32 count = 0;
	for (u32 offset = (u32)source.find(seeking); offset != std::string::npos; offset = (u32)source.find(seeking, offset + (u32)seeking.length()))
		++count;

	return count;
}

//Split

vector<string> StringHelper::split(string text, string delims) {
	vector<string> tokens(count(text, delims) + 1);
	size_t off = 0;
	size_t doff;
	string t = text;
	u32 offs = 0;
	while ((doff = text.find_first_of(delims[0], off)) != string::npos) {
		string subt = text.substr(doff, delims.size());
		if (subt != delims) {
			off = doff + 1;
			continue;
		}
		tokens[offs] = t.substr(0, doff - off);
		++offs;

		t = text.substr(doff + delims.size());
		off = doff + delims.size();
	}
	tokens[offs] = t.substr(0, doff - off);

	return tokens;
}

vector<string> StringHelper::split(string s, char c) {
	u32 i = 0;
	vector<string> res(count(s, c));
	string curr;
	u32 offset = 0;
	while (i < s.size()) {
		char cur = s[i];
		if (cur == c) {
			res[offset] = curr;
			++offset;
			curr = "";
		}
		else
			curr += cur;
		++i;
	}
	res[offset] = curr;
	return res;
}

//Combine

string StringHelper::combine(vector<string> &array, string seperator) {
	if (array.size() == 0)return "";

	//Get length of new string
	u32 strSize = ((u32)array.size() - 1) * (u32)seperator.size();
	for (u32 i = 0; i < array.size(); ++i)
		strSize += (u32)array[i].size();

	//Create new string
	std::string result = std::string(strSize, ' ');
	u32 offset = 0;
	for (u32 i = 0; i < array.size(); ++i) {
		if (array[i].size() != 0) {
			memcpy((void*)((char*)(result.c_str()) + offset), (void*)array[i].c_str(), array[i].size());
			offset += (u32)array[i].size();
		}
		if (i != array.size() - 1 && seperator.size() != 0) {
			memcpy((void*)((char*)(result.c_str()) + offset), (void*)seperator.c_str(), seperator.size());
			offset += (u32)seperator.size();
		}
	}
	return result;
}

//Files

string StringHelper::fromFile(string path) {
	ifstream str(path);
	if (!str.good()) {
		printf("Failed to get a file as a string\n");
		return "";
	}
	return string(istreambuf_iterator<char>(str), istreambuf_iterator<char>());
}

string StringHelper::grabPath(string filePath) {
	vector<string> str = split(filePath, '/');
	if (str.size() == 1) return "";
	str.erase(str.end());
	return combine(str, "/");
}

string StringHelper::grabFileNoExt(string filePath) {
	vector<string> str = split(filePath, '.');
	if (str.size() == 1) return filePath;
	string st;
	for (u32 i = 0; i < str.size() - 1; ++i)
		st = st + str[i] + (i != str.size() - 2 ? "." : "");
	return st;
}

string StringHelper::grabFile(string filePath) {
	vector<string> str = split(filePath, '/');
	return str[str.size() - 1];
}

//Substring

string StringHelper::substring(string source, u32 start) {
	return source.substr(start);
}

string StringHelper::substring(string source, u32 start, u32 end) {
	return source.substr(start, end);
}

//Number to string and vice versa

string StringHelper::numstring(u32 number, string prefix, string suffix) {
	stringstream ss;
	ss << prefix << number << suffix;
	return ss.str();
}

u32 StringHelper::parseInt(string source) {
	i32 i = stoi(source);
	if (i < 0) return UINT32_MAX;
	return *(u32*)(&i);
}

i32 StringHelper::parseSInt(string source) {
	return stoi(source);
}

f64 StringHelper::parseDouble(std::string source) {
	return stod(source);
}

vector<string> StringHelper::splitStringNum(string source) {
	vector<string> str = vector<string>();
	string prev = "";
	bool isNum = false;
	for (u32 i = 0; i < source.size(); ++i) {
		char c = source[i];
		if (c >= 0x30 && c <= 0x39) {
			if (!isNum && prev != "") {
				str.push_back(prev);
				prev = "";
			}
			isNum = true;
		}
		else {
			if (isNum && prev != "") {
				str.push_back(prev);
				prev = "";
			}
			isNum = false;
		}
		prev = prev + source[i];
	}
	if (prev != "")
		str.push_back(prev);
	return str;
}

bool StringHelper::isNumber(string s) {
	for (u32 i = 0; i < s.size(); ++i)
		if (s[i] < 0x30 || s[i] > 0x39)return false;
	return true;
}

//Trim a string

string StringHelper::trim(string source, bool doubleWhitespace) {
	if (source.size() == 0 || source == " ")return "";
	u32 UNDEF = 0xFFFFFFFF;
	u32 st=UNDEF, e=UNDEF;
	for (u32 i = 0; i < source.size(); ++i) {
		if (source[i] != ' ' && source[i] != '\t') {
			st = i;
			break;
		}
	}
	for (u32 i = (u32)source.size(); i > 0; --i) {
		if (source[i - 1] != ' ' && source[i - 1] != '\t') {
			e = i;
			break;
		}
	}
	if (st == UNDEF || e == UNDEF)return "";
	source = source.substr(st, e);
	if (!doubleWhitespace) {
		u32 nd = 0;
		bool b = false;
		for (u32 i = (u32)source.size(); i > 0; --i) {
			if (!b) {
				if (source[i - 1] == ' ' || source[i - 1] == '\t') {
					nd = i;
					b = true;
				}
			}
			else {
				if (!(source[i - 1] == ' ' || source[i - 1] == '\t')) {
					if (i + 1 != nd) 
						source = StringHelper::substring(source, 0, i) + " " + StringHelper::substring(source, nd);
					b = false;
				}
			}
		}
	}
	return source;
}

//Find lines that match the criteria

bool StringHelper::find(vector<string> &haystack, string needleStart, string needleEnd, vector<u32> &locations, bool trim){
	vector<u32> starts, ends;
	find(haystack, needleStart, starts, trim);
	find(haystack, needleEnd, ends, trim);
	if (starts.size() != ends.size() || starts.size() == 0)return false;
	for (u32 i = 0; i < starts.size(); ++i){
		locations.push_back(starts[i]);
		locations.push_back(ends[i]);
	}
	return true;
}

bool StringHelper::find(vector<string> &haystack, string needle, vector<u32> &locations, bool tr){
	u32 fsize = (u32)locations.size();
	for (u32 i = 0; i < haystack.size(); ++i) {
		if ((tr && trim(haystack[i]) == needle) || (!tr && haystack[i] == needle))
			locations.push_back(i);
	}
	return locations.size() != fsize;
}

//Remove lines from a file

vector<string> StringHelper::erase(vector<string> &haystack, vector<string> &needles, bool tr){
	vector<string> res;
	for (u32 i = 0; i < haystack.size(); ++i){
		bool contains = false;
		for (u32 j = 0; j < needles.size(); ++j)
			if ((!tr && haystack[i] == needles[j]) || (tr && trim(haystack[i]) == needles[j])){
				contains = true;
				break;
			}
		if (!contains)
			res.push_back(haystack[i]);
	}
	return res;
}

//Cross platform line ending

string StringHelper::lineEnd() {
	stringstream ss;
	ss << endl;
	return ss.str();
}

//

bool StringHelper::containsOnly(std::string source, std::string keyset) {
	for (u32 i = 0; i < source.size(); ++i) 
		if (!contains(keyset, source[i]))
			return false;
	return true;
}

bool StringHelper::contains(std::string str, char c) {
	for (u32 i = 0; i < str.size(); ++i)
		if (str[i] == c)
			return true;
	return false;
}

bool StringHelper::isFirstOrDoesntExist(std::string source, char c) {
	return count(source, c) == 0 || (count(source, c) == 1 && source.size() > 0 && source[0] == c);
}

//Keysets

std::string StringHelper::keysetNumbers = "0123456789";
std::string StringHelper::keysetAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string StringHelper::keysetalpha = "abcdefghijklmnopqrstuvwxyz";
std::string StringHelper::keysetalphaAlpha = keysetalpha + keysetAlpha;
std::string StringHelper::keysetalphaAlphaNumbers = keysetalphaAlpha + keysetNumbers;
std::string StringHelper::keysetAlphaNumbers = keysetAlpha + keysetNumbers;
std::string StringHelper::keysetalphaNumbers = keysetalpha + keysetNumbers;