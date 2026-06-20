#pragma once
#include<vector>

class StageGenerator
{
private :
	StageGenerator();
	StageGenerator& operator = (const StageGenerator& other) = delete;
	StageGenerator(const StageGenerator& other) = delete;

public:

	enum STAGEDATA
	{
		DATA_NONE = -1,
		DATA_MARIO,
		DATA_BLOCK_BRICK,
		DATA_BLOCK_FLOOR,
		DATA_BLOCK_QUESTION,
		DATA_BLOCK_HARD,
		DATA_BLOCK_HIDDEN,
		DATA_PIPE,
		DATA_GOOMBA,
		DATA_KOOPA_TROOPA,
	};

	static inline StageGenerator* getInstance()
	{
		static StageGenerator instance;
		return &instance;
	}

	void generateStage(std::vector<std::vector<int>> mapDataBuffer);
};