#include "GameplayTags/CCTags.h"

namespace CCTags
{
	namespace CCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven,"CCTags.CCAbilities.ActivateOnGiven", "Tag for Abilities that should activate immediately on given");
		
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary,"CCTags.CCAbilities.Player.Primary", "Tag for the Primary Ability");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary,"CCTags.CCAbilities.Player.Secondary", "Tag for the Secondary Ability");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary,"CCTags.CCAbilities.Player.Tertiary", "Tag for the Tertiary Ability");
		}
	}
	
	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact,"CCTags.Events.Enemy.HitReact", "Tag for the enemy hit react event");
		}
	}
}