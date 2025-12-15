#include "GameplayTags/CCTags.h"

namespace CCTags
{
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Projectile,"CCTags.SetByCaller.Projectile", "Tag for SetByCaller magnitude for projectiles");
	}
	
	namespace CCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven,"CCTags.CCAbilities.ActivateOnGiven", "Tag for Abilities that should activate immediately on given");
		
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary,"CCTags.CCAbilities.Player.Primary", "Tag for the Primary Ability");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary,"CCTags.CCAbilities.Player.Secondary", "Tag for the Secondary Ability");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary,"CCTags.CCAbilities.Player.Tertiary", "Tag for the Tertiary Ability");
		}
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack,"CCTags.CCAbilities.Enemy.Attack", "Enemy Attack Tag");
		}
		
	}
	
	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored,"CCTags.Events.KillScored", "Tag for KillScored event");
		
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact,"CCTags.Events.Player.HitReact", "Tag for the Player hit react event");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death,"CCTags.Events.Player.Death", "Tag for Player death event");
		}
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact,"CCTags.Events.Enemy.HitReact", "Tag for the enemy hit react event");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack,"CCTags.Events.Enemy.EndAttack", "Tag for an enemy ending an attack");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MeleeTraceHit,"CCTags.Events.Enemy.MeleeTraceHit", "Tag for the enemy melee trace hit");
		}
	}
}