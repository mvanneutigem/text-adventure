#include "FileReader.h"
#include <iostream>
#include <fstream>
#include "NPC.h"
#include "Phone.h"
#include "Container.h"

using namespace std;


FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

void FileReader::readInput(int startpos, int& endpos, string line, string& save, char separater)
{
	endpos = int(line.find(separater, endpos));
	if (endpos != line.npos)
	{
		save = line.substr(startpos, endpos - startpos);
	}
}

void FileReader::readItems(const string& filename)
{
	auto retry = true;
	while (retry)
	{
		ifstream filestream;
		filestream.open(filename);
		if (!filestream.is_open())
		{
			cout << "File was not opened succesfully :(\n";
		}
		else
		{
			retry = false;
			string name;
			string keyword;
			string description;
			string NrOFLocations;
			auto isCarryable = false;
			vector<int> locationsIndex;

			string line;
			auto counter = -1;
			while (!filestream.eof()) {
				getline(filestream, line);

				auto identifier = int(line.find("|"));
				if (identifier != line.npos)
				{
					auto endpos = 0;
					readInput(0, endpos, line, name, '|');
					++endpos;

					readInput(endpos, endpos, line, keyword, '|');
					++endpos;
					readInput(endpos, endpos, line, description, '|');
					++endpos;
					readInput(endpos, endpos, line, NrOFLocations, '|');
					unsigned int nr = stoi(NrOFLocations);
					if (nr != 0)
					{
						isCarryable = false;
						for (unsigned int i = 0; i < nr; ++i)
						{
							string location;
							++endpos;
							readInput(endpos, endpos, line, location, '|');
							locationsIndex.push_back(stoi(location));
						}

					}
					else
					{
						isCarryable = true;
					}

					++counter;
					if (name == "the whiteboard")
					{
						m_Items.push_back(new Container(name, keyword, description, locationsIndex));
					}
					else
					{
						auto i = new Item(name, keyword, description, isCarryable, locationsIndex);
						m_Items.push_back(i);
					}
					
					locationsIndex.clear();
				}
			}

		}
		filestream.close();
	}
}

void FileReader::readNPCs(const std::string& filename)
{
	auto retry = true;
	while (retry)
	{
		ifstream filestream;
		filestream.open(filename);
		if (!filestream.is_open())
		{
			cout << "File was not opened succesfully :(\n";
		}
		else
		{
			retry = false;
			string name;
			vector<NPC::Dialogue> dialogueArr;

			string line;
			auto counter = -1;
			while (!filestream.eof()) {
				getline(filestream, line);

				auto identifier = int(line.find("|"));
				if (identifier != line.npos)
				{
					auto endpos = 0;
					string trigger;
					readInput(0, endpos, line, trigger, '|');
					if (trigger != "name")
						break;
					name = line.substr(trigger.size() + 1);

					bool end = false;
					while(!end)
					{
						getline(filestream, line);
						auto endpos2 = 0;
						string trigger2;
						readInput(0, endpos2, line, trigger2, '|');
						if (stoi(trigger2) < 0)
							end = true;
						NPC::Dialogue d;
						d.text = line.substr(trigger2.size() + 1);
						d.ID = stoi(trigger2);
						dialogueArr.push_back(d);
					}

					auto i = NPC(name, dialogueArr);
					m_NPCs.push_back(i);
					dialogueArr.clear();
				}
			}

		}
		filestream.close();
	}
}

void FileReader::readVerbs(const string& filename)
{
	readWordIntoVector(filename, m_Verbs);
}

void FileReader::readNouns(const string& filename)
{
	readWordIntoVector(filename, m_Nouns);
}

void FileReader::readWordIntoVector(const string& filename, vector<word>& words)
{
	auto retry = true;
	while (retry)
	{
		ifstream filestream;
		filestream.open(filename);
		if (!filestream.is_open())
		{
			cout << "File was not opened succesfully :(\n";
		}
		else
		{
			retry = false;
			string line;
			auto counter = -1;
			while (!filestream.eof()) {
				getline(filestream, line);
				int splitter = line.find('|');
				auto ID = line.substr(0, splitter);
				auto wordStr = line.substr(splitter + 1);
				FileReader::word w;
				w.ID = stoi(ID);
				w.wordStr = wordStr;
				words.push_back(w);
			}

		}
		filestream.close();
	}
}

void FileReader::readLocations(const string& filename)
{
	auto retry = true;
	while (retry)
	{
		ifstream filestream;
		filestream.open(filename);
		if (!filestream.is_open())
		{
			cout << "File was not opened succesfully :(\n";
		}
		else
		{
			retry = false;
			string name;
			string left;
			string right;
			string forward;
			string back;
			string longDesc;
			string keyword;

			string line;
			auto counter = -1;
			while (!filestream.eof()) {
				getline(filestream, line);

				int identifier = int(line.find("|"));
				if (identifier != line.npos)
				{
					int endpos = 0;
					readInput(0, endpos, line, name, '|');
					++endpos;
					readInput(endpos, endpos, line, keyword, '|');
					++endpos;
					readInput(endpos, endpos, line, longDesc, '|');
					++endpos;
					readInput(endpos, endpos, line, left, '|');
					++endpos;
					readInput(endpos, endpos, line, right, '|');
					++endpos;
					readInput(endpos, endpos, line, forward, '|');
					++endpos;
					back = line.substr(endpos);
					++counter;
					Location* location = nullptr;
					if (m_Locations.size() < 14)
					{
						location = new Location(name, keyword, longDesc, stoi(left), stoi(right), stoi(forward), stoi(back), true);
					}
					else
					{
						location = new Location(name, keyword, longDesc, stoi(left), stoi(right), stoi(forward), stoi(back));
					}
					m_Locations.push_back(*location);
					delete location;
				}
			}

		}
		filestream.close();
	}
}

std::vector<Item*>& FileReader::getItems()
{
	return  m_Items;
}

const std::vector<Location>& FileReader::getLocations() const
{
	return m_Locations;
}

const std::vector<FileReader::word>& FileReader::getVerbs() const
{
	return m_Verbs;
}

const std::vector<FileReader::word>& FileReader::getNouns() const
{
	return m_Nouns;
}

const std::vector<NPC>& FileReader::getNPCs() const
{
	return m_NPCs;
}
