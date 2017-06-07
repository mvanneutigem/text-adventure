#pragma once
#include <vector>
#include "FileReader.h"
#include "Parser.h"

class Location;
class StateMachine;

class Game
{
public:
	Game();
	~Game();

	void Start(StateMachine* machine);
	void Update();
	bool m_ExitGame = false;
	static int m_CurrentlocationID;
	static Parser::commandType m_CommandType;
	static int m_TalkID;
	static StateMachine* m_statemachine;
	static int m_ItemID;
	FileReader m_Reader;

private:
	
	Parser parser;

	int m_LastLocationID = -1;

	enum class direction {
		left = 1,
		right,
		forward,
		back
	};
	void handleMovement(const direction direction, int& currentLocation, const std::vector<Location> locations);
	void HandleTalking();
	void HanleUsage();
	void HandleInspection();
	void ShowCurrentLocation();
};

