#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{

}

AssetManager::~AssetManager(void)
{

}

void AssetManager::addTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id)
{
	return textures[id];
}

void AssetManager::CreateProjectile(Vector2D pos,Vector2D vel, int range, int speed, std::string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>("assets/fire.png", false);
	projectile.addComponent<ProjectileComponent>(range, speed,vel);
	projectile.addComponent<ColliderComponet>("projectile");
	projectile.addGroup(groupProjectiles);
}