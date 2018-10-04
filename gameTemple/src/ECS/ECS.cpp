#include "ECS.hpp"

void ECS::Entity::addGroup(Group group) noexcept
{
	groupBitSet_[group] = true;
	manager_.addToGroup(this, group);
}