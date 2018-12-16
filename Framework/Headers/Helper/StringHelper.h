#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../Type/OTypes.h"
namespace lun {
	class StringHelper {
	public:
		//Checks whether a ends with b
		//@param std::string source
		//@param std::string suffix
		//@return bool endsWith
		static bool endsWith(std::string source, std::string suffix);

		//Checks whether a starts with b
		//@param std::string source
		//@param std::string prefix
		//@return bool startsWith
		static bool startsWith(std::string source, std::string prefix);

		//Combines the array by putting the seperator in between elements
		//@param std::vector<std::string> &array
		//@param std::string seperator
		//@return std::string result
		static std::string combine(std::vector<std::string> &array, std::string seperator);

		//Gets the string in lowercase
		//@param std::string source
		//@return std::string source as lowercase
		static std::string toLowerCase(std::string source);

		//@param std::string source1
		//@param std::string source2
		//@return source1 == source2 when lowercase
		static bool equalsIgnoreCase(std::string source1, std::string source2);

		//@param std::string source1
		//@param std::string source2
		//@return endsWith(source1, source2) when lowercase
		static bool endsWithIgnoreCase(std::string source1, std::string source2);

		//@param std::string source1
		//@param std::string source2
		//@return startsWith(source1, source2) when lowercase
		static bool startsWithIgnoreCase(std::string source1, std::string source2);
		

		//Counts character occurences in string
		//@param std::string source
		//@param char c
		static u32 count(std::string source, char c);

		//Counts string occurences in string
		//@param std::string source
		//@param std::string seeking
		static u32 count(std::string source, std::string seeking);

		//Splits a string by a character
		//@param std::string source
		//@param char seperator
		static std::vector<std::string> split(std::string source, char seperator);

		//Splits a string by a sub string
		//@param std::string source
		//@param std::string seperator
		static std::vector<std::string> split(std::string text, std::string seperator);
		
		//Finds the needle in the haystack
		//@param std::vector<std::string> &haystack
		//@param std::string needle
		//@param std::vector<u32> &locations		output of locations
		//@optional bool trim, whether or not every line has to be trimmed before checking (default = false)
		//@return bool hasAny
		static bool find(std::vector<std::string> &haystack, std::string needle, std::vector<u32> &locations, bool trim=false);

		//Finds the needle in the haystack
		//@param std::vector<std::string> &haystack
		//@param std::string needle start line
		//@param std::string needle end line
		//@param std::vector<u32> &locations		output of locations
		//@optional bool trim, whether or not every line has to be trimmed before checking (default = false)
		//@return bool hasAny
		static bool find(std::vector<std::string> &haystack, std::string needleStart, std::string needleEnd, std::vector<u32> &locations, bool trim=false);

		//Remove all referenced needles from the haystack
		//@param std::vector<std::string> &haystack
		//@param std::vector<std::string> &needles
		//@optional bool trim; whether or not every line has to be trimmed before checking (default = false)
		static std::vector<std::string> erase(std::vector<std::string> &haystack, std::vector<std::string> &needles, bool trim=false);


		//Gets rid of everything before index start in source
		//@param std::string source
		//@param u32 start
		//@return std::string result = source.at(>=start)
		static std::string substring(std::string source, u32 start);

		//Gets the string at [st,en>
		//Gets rid of everything before index start and after index end in source ([start, end>)
		//@param std::string source
		//@param u32 start
		//@param u32 end
		//@return std::string result = source.at(>=start, <end)
		static std::string substring(std::string source, u32 start, u32 end);
		

		//Gets the string contents of a file
		static std::string fromFile(std::string filePath);		
		
		//Grabs the path without file and extension
		static std::string grabPath(std::string filePath);

		//Grabs the path without extension
		static std::string grabFileNoExt(std::string filePath);

		//Grabs the file name with extension
		static std::string grabFile(std::string filePath);


		//Gets rid of whitespace before and after the string; turn on 'dubbleWhitespace' to get rid of double whitespace
		//@param std::string source
		//@optional bool doubleWhitespace (whether or not it replaces double whitespace & tabs)
		//@return std::string result; source without trailing (whitespace & tabs on front and back)
		static std::string trim(std::string source, bool doubleWhitespace = false);
		

		//Puts a string and number together
		//@param u32 number
		//@param std::string prefix
		//@param std::string suffix
		//@return std::string result = prefix + i + suffix
		static std::string numstring(u32 number, std::string prefix, std::string suffix);

		//Parses an unsigned int from string (If string<0 it will return UINT_MAX)
		//@param std::string source
		//@return u32 representation
		static u32 parseInt(std::string source);

		//Parses a signed int from string
		//@param std::string source
		//@return i32 representation
		static i32 parseSInt(std::string s);

		//Parses a double from string
		//@param std::string source
		//@return f64 double
		static f64 parseDouble(std::string source);

		//Splits the words from numbers
		//@param std::string source
		//@return std::vector<std::string> split
		static std::vector<std::string> splitStringNum(std::string source);

		//Checks whether or not the string is a number
		//@param std::string source
		//@return bool isNumber
		static bool isNumber(std::string source);


		//Whether or not the string only contains characters found in keyset
		//@param std::string source
		//@param std::string keyset
		static bool containsOnly(std::string source, std::string keyset);

		//Whether or not the string contains a character
		//@param std::string source
		//@param char c
		static bool contains(std::string source, char c);


		//Whether or not the string starts with a character or doesn't contain the character at all (and there's just 1 occurence of the char)
		//@param std::string source
		//@param char c
		static bool isFirstOrDoesntExist(std::string source, char c);


		//End of line
		//@return \r\n on UNIX and \n on Windows
		static std::string lineEnd();


		//Numbers
		static std::string keysetNumbers;
		static std::string keysetAlpha;
		static std::string keysetalpha;
		static std::string keysetalphaAlpha;
		static std::string keysetalphaAlphaNumbers;
		static std::string keysetalphaNumbers;
		static std::string keysetAlphaNumbers;
	};
}