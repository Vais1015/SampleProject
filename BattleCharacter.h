#pragma once
#include "Actor.h"
#include "SE.h"
#include <string>

/********************************************/
//	�O���[�o���ϐ�
//	��_�@mWeakPoint�ɑ�����ė��p�@�r�b�g���Z
const unsigned int STRIKE = (1 << 0);
const unsigned int SHOOT = (1 << 1);
const unsigned int FIRE = (1 << 2);
const unsigned int WATER = (1 << 3);
const unsigned int WINDOW = (1 << 4);
const unsigned int THUNDER = (1 << 5);
const unsigned int LIGHT = (1 << 6);
const unsigned int DARK = (1 << 7);
/*****************************************/

class BattleCharacter : public Actor
{
public:
	struct Status {
		int HP;
		int SP;
		int OffensivePower;
		int DefensivePower;
		int Speed;
		unsigned int Weakness;
		bool Alive;
		std::string Name;
	};

	struct Arts
	{
		std::string ArtsName;
		float Power;
		const unsigned int Attribute;
		SE* se;
	};

	BattleCharacter(class Game* , class BattleScene*);
	virtual ~BattleCharacter();

	virtual void UpdateActor(float deltaTime) override;

	void RecvDamage(int damage);

	//	Getter
	Status GetStatus() const;
	float GetCoolDown() const;
	float GetFromPreviousAttack() const;

	//	Setter
	void SetHitWeakness(bool hit);
	void SetDisplayedHitWeakness(bool displayed);
	//	later
	//friend class BattleScene;

protected:
	class BattleScene* mBattleScene;

	class SpriteComponent* mCharacterImg;
	class BattleHP* mCharacterHP;

	Status mStatus;
	std::vector<Arts> mArts;

	//	Sprite�p
	Vector2 mPos;
	float mScale = 2.0f;
	int mDrawOrder = 120;

	//	�Z���o���Ă�����܂ł̎��ԁE�P�ʕb�ESpeed50�̂Ƃ��T�b
	float mCoolDown = 5.0f;
	float mFromAttack;

	//	RecastTime�����J�o���[����܂ł̑����A���x�������Ƒ����Ȃ�ASpeed50�̂Ƃ�1
	float mRTRecoverySpd;

	//	��_�Ƀq�b�g����Ǝ��̋Z���o���܂Ń��J�o���[�X�s�[�h���x���Ȃ�
	float mSlowDown = 0.5f;
	bool mHitWeakness;
	bool mDisplayedHitWeaknessMsg;
};