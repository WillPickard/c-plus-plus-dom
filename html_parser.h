//html_parser.h
#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <stack>
#include <vector>
#include <queue>
#include <string>
#include <string.h> //strlen
#include <stdlib.h> //malloc


class HTMLParser
{
	private:
		const char * raw_html;

		int raw_html_len;

		//the current index into the raw_html
		int _i;

		//stack of previous indices
		std::stack<int> prevIndices;

		//stack of indices that we already used
		std::stack<int> forwardIndices;

	public:
		HTMLParser(const std::string);
		HTMLParser(const char *);

		void rewind(int);
		void fastforward(int);

		std::vector<char> tagname(const char *) const;
		std::vector<char> tagname(const std::string) const;

		int cmpTags(const char *, const char *) const;
		int cmpTags(const std::string, const std::string) const;

		std::vector<char> nextTag();
		std::vector<char> next();

		signed char getTagType(const char *) const;
		signed char getTagType(const std::string) const;

		bool isOpenTag(const char *) const;
		bool isOpenTag(const std::string) const;

		bool isCloseTag(const char *) const;
		bool isCloseTag(const std::string) const;

		bool isTag(const char *) const;
		bool isTag(const std::string) const;

		bool isFullTag(const char *) const;
		bool isFullTag(const std::string) const;

		bool hasMore() const;

		bool isEscapeSequence(const char) const;
		
		const char * getRawHTML() const;
		int getCurrentIndex() const;
		int getRawHTMLLength() const;

		void setRawHTML(const char *);
		void setCurrentIndex(int);
		void setRawHTMLLength(int);

		static const signed char tag_type_none;
		static const signed char tag_type_tag;
		static const signed char tag_type_open;
		static const signed char tag_type_closed;
		static const signed char tag_type_full;
		//static const int OPEN_ONLY; //return only the opentag
		//static const int 
};

		const signed char HTMLParser::tag_type_none		= 0; //not a tag
		const signed char HTMLParser::tag_type_tag 		= 1; //is a tag
		const signed char HTMLParser::tag_type_open 	= 3; //is a tag and is an open tag
		const signed char HTMLParser::tag_type_closed 	= 5; //is a tag and is a closed tag
		const signed char HTMLParser::tag_type_full		= 9; //is a tag and is a full tag

#endif