#include "StoryFlag.h"
#include <regex>
#include <stdio.h>

StoryFlag::StoryFlag()
	:mKill(false)
	,mSelectedKill(false)
	,mRepeated(false)
	,mCleared(false)
{
	for (int i = 0; i < mSceneAmount; ++i)
		mStoryFlag.push_back(false);
}

//	Getter
int StoryFlag::GetSceneAmount() const 
{
	return mSceneAmount; 
}

std::vector<bool> StoryFlag::GetFlag() const
{
	return mStoryFlag; 
}

bool StoryFlag::GetKillFlag() const
{
	return mKill;
}

bool StoryFlag::GetSelectedKillFlag() const
{
	return mSelectedKill;
}

bool StoryFlag::GetReated() const
{
	return mRepeated;
}

bool StoryFlag::GetCleared() const
{
	return mCleared;
}

//	Setter
void StoryFlag::SetFlag(int number)
{
	mStoryFlag[number] = true;
}

void StoryFlag::SetKillFlag(bool kill)
{
	mKill = kill;

	SetSelectedKillFlag(true);
}

void StoryFlag::SetSelectedKillFlag(bool sellected)
{
	mSelectedKill = sellected;
}

void StoryFlag::SetReated()
{
	mRepeated = true;
}

void StoryFlag::SetCleared()
{
	mCleared = true;
}

void StoryFlag::ResetFlags()
{
	for (auto i : mStoryFlag)
	{
		i = false;
	}

	SetKillFlag(false);
	SetSelectedKillFlag(false);
	mRepeated = false;
}
