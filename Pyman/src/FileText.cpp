/*
 * FileText.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: frosty
 */

#include "FileText.h"

#include <iostream>

FileText::FileText()
{
	length = 0;
}

FileText::FileText(const char* newScript)
{
	script = new char[50];
	setScript(newScript);
	length = 0;
}

const char* FileText::getScript(bool ext) const
{
	if (!ext)
	{		
		return script.substr(0, script.find('.')).c_str();
	}

	return script.c_str();
}

void FileText::setScript(const char* newScript)
{
	if (strcmp(newScript,script.c_str()) != 0)
	{
		script = newScript;
		fstream tStream;
		tStream.open(newScript, fstream::in | fstream::out);
		string temp;

		while(getline(tStream,temp))
			lines.push_back(temp);

		tStream.close();
	}
}

void FileText::save()
{
	printf("***FILE SAVED***\n");
	fstream tStream;
	tStream.open(script, fstream::out);
	tStream.write(getRunnable(),numChars()-1);
	tStream.close();
}

void FileText::insert(const char* c, Cursor& cur)
{
	lines[cur.li].insert(cur.pos,c);
}

int FileText::back(Cursor& cur)
{
	if (cur.li >= 0 && cur.li < int(lines.size()) && cur.pos > 0)
	{
		lines[cur.li].erase(lines[cur.li].begin() + cur.pos - 1);
		cur.pos--;
	}
	else if(cur.pos <= 0 && cur.li > 0)
	{
		int temp = lines[cur.li-1].size();
		mergeLines(cur);
		cur.pos = temp;
		return 1;
	}
	return 0;
}

void FileText::newLine(Cursor& cur)
{
	if (cur.pos == int(lines[cur.li].size()))
	{
		lines.insert(lines.begin() + cur.li + 1,"");
	}
	else
	{
		lines.insert(lines.begin() + cur.li + 1,lines[cur.li].substr(cur.pos));
		lines[cur.li] = lines[cur.li].substr(0,cur.pos);
	}
	cur.li++;
	cur.pos = 0;
}

void FileText::mergeLines(Cursor& cur)
{
	if (cur.li > 0 && cur.li < int(lines.size()))
	{
		lines[cur.li-1] += lines[cur.li];
		lines.erase(lines.begin() + cur.li);
		cur.li--;
		cur.pos = lines[cur.li].size() + 1;
	}
}

void FileText::returnCursor(Cursor& cur)
{
	if (cur.li < 0)
		cur.li = 0;
	else if (cur.li >= int(lines.size()))
		cur.li = lines.size() - 1;

	if (cur.pos > int(lines[cur.li].size()))
	{
		if (cur.li == int(lines.size()) - 1)
			cur.pos = lines[cur.li].size();
		else
			cur.pos = 0;
	}
	else if (cur.pos < 0)
	{
		cur.li--;
		cur.pos = lines[cur.li].size();
	}
}

const char* FileText::getRunnable() const
{
	char* cat = new char[numChars()];
	int vSize = lines.size();

	strcpy(cat,lines[0].c_str());
	for(int i = 1; i < vSize; i++)
	{
		strcat(cat,"\n");
		strcat(cat,lines[i].c_str());
	}

	return cat;
}

const vector<string>& FileText::getLines() const
{
	return lines;
}

unsigned int FileText::numChars() const
{
	unsigned int length = 0;
	int vSize = lines.size();
	for(int i = 0; i < vSize; i++)
		length += lines[i].length() + 1;
	return length;
}

FileText::~FileText()
{
}

