/*
 * FileText.h
 *
 * Created on: Mar 26, 2014
 * Author: frosty
 * Abstract:	This class handles "text" in "files". There 
 *				may be possible optimizations, and anyone
 *				qualified to make those optimizations 
 *				probably doesn't need documentation.
 */

#ifndef FILETEXT_H_
#define FILETEXT_H_

#include <fstream>
#include <string>
#include <vector>

typedef struct Cursor {
	int li;
	int pos;
} Cursor;

using namespace std;

////
//MODIFY WITH SLATE
////

class FileText {
public:
	FileText();
	FileText(const char* newScript);

	const char* getScript(bool ext) const;
    void setScript(const char* newScript);

	void save();

	const char* getRunnable() const;
	unsigned int numChars() const;

	const vector<string>& getLines() const;

	virtual ~FileText();

protected:
	void returnCursor(Cursor& cur);
	void mergeLines(Cursor& cur);
	void newLine(Cursor& cur);
	void insert(const char* c, Cursor& cur);
	int back(Cursor& cur);

private:
    string script;
    vector<string> lines;
    unsigned int length;
};

#endif /* FILETEXT_H_ */
