#pragma once
#include <string>
#include <vector>

class StoryFlag
{
public:
	StoryFlag();

	//	Getter
	int GetSceneAmount() const;
	std::vector<bool> GetFlag() const;
	bool GetKillFlag() const;
	bool GetSelectedKillFlag() const;
	bool GetReated() const;
	bool GetCleared() const;

	// Setter
	void SetFlag(int number);
	void SetKillFlag(bool kill);
	void SetReated();
	void SetCleared();

private:
	std::vector<bool> mStoryFlag;
	int mSceneAmount = 6;
	bool mKill;
	bool mSelectedKill;
	bool mRepeated;
	bool mCleared;
};