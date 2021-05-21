#pragma once
#include "Actor.h"
#include <string>

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
		std::string Name;
	};

	enum class Condition {
		ALIVE,
		DEAD
	};

	struct Arts {
		std::string ArtsName;
		float Power;
		const unsigned int Attribute;
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

	class SpriteComponent* mCharacterImage;
	class BattleHP* mCharacterHP;

	Status mStatus;
	Condition mCondition;

	//	技を出してから放つまでの時間・単位秒・Speed50のとき５秒
	float mCoolDown = 5.0f;
	float mFromPreviousAttack;
	//	RecastTimeをリカバリーするまでの速さ、速度が高いと早くなる、Speed50のとき1
	float mRTRecoverySpd;
	//	弱点にヒットすると次の技を出すまでリカバリースピードが遅くなる
	float mSlowDown = 0.7f;
	bool mHitWeakness;
	bool mDisplayedHitWeakness;

	//	弱点　mWeakPointに代入して利用　ビット演算
	const unsigned int STRIKE = (1 << 0);
	const unsigned int SHOOT = (1 << 1);
	const unsigned int FIRE = (1 << 2);
	const unsigned int WATER = (1 << 3);
	const unsigned int WINDOW = (1 << 4);
	const unsigned int THUNDER = (1 << 5);
	const unsigned int LIGHT = (1 << 6);
	const unsigned int DARK = (1 << 7);
};