#include "Teleport.h"

Teleport::Teleport(int x, int y, int tileSize, int id)
    : GameObject(x, y, tileSize),
    teleportID(id),
    isActive(true),
    activeTexture(nullptr),
    inactiveTexture(nullptr) {
}

void Teleport::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Teleport::setActive(bool active) {
    isActive = active;
    updateTexture();
}

void Teleport::setActiveTexture(const sf::Texture& texture) {
    activeTexture = &texture;
    if (isActive) {
        sprite.setTexture(texture);
    }
}

void Teleport::setInactiveTexture(const sf::Texture& texture) {
    inactiveTexture = &texture;
    if (!isActive) {
        sprite.setTexture(texture);
    }
}

void Teleport::updateTexture() {
    if (isActive && activeTexture) {
        sprite.setTexture(*activeTexture);
    }
    else if (!isActive && inactiveTexture) {
        sprite.setTexture(*inactiveTexture);
    }
}