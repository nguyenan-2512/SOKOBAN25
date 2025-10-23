#pragma once
#include "GameObject.h"
#include <string>

class Teleport : public GameObject {
private:
    int teleportID;  // ID để nhóm các cổng với nhau (cùng ID = liên kết)
    bool isActive;
    const sf::Texture* activeTexture;
    const sf::Texture* inactiveTexture;

public:
    Teleport(int x, int y, int tileSize, int id);
    void draw(sf::RenderWindow& window) override;

    int getTeleportID() const { return teleportID; }
    void setTeleportID(int id) { teleportID = id; }

    void setActive(bool active);
    bool getIsActive() const { return isActive; }

    void setActiveTexture(const sf::Texture& texture);
    void setInactiveTexture(const sf::Texture& texture);
    void updateTexture();
};