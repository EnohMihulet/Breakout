#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "../headers/balls.h"
#include "../headers/blocks.h"
#include "../headers/platform.h"

namespace Breakout {

    Ball::Ball() 
        : m_circle(sf::CircleShape(ballRadius)), m_velocity{getRandomVelocity()}, m_nextPos(sf::Vector2f(0, 0))
    {
        m_circle.setOrigin(sf::Vector2f(ballRadius, ballRadius));
        m_circle.setPosition(sf::Vector2f(halfScreenWidth, screenHeight - 60));
        m_circle.setFillColor(ballColor);
    }

    Ball::Ball(sf::Vector2f startVel, sf::Vector2f startPos) 
        : m_circle(sf::CircleShape(ballRadius)), m_velocity(startVel), m_nextPos(sf::Vector2f(0, 0))
    {
        m_circle.setOrigin(ballRadius, ballRadius);
        m_circle.setPosition(startPos);
        m_circle.setFillColor(ballColor);
    }

    void Ball::hitWall() {
        // Ball bounces if it hits the two sides or top of the screen;
        if (m_nextPos.x <= ballRadius) {
            m_velocity = ballSpeed * normalizedVector(reflectionVector(m_velocity, {1, 0}));
            m_circle.setPosition(ballRadius + 0.1f, m_circle.getPosition().y);
        }
        if (m_nextPos.x >= screenWidth - ballRadius) {
            m_velocity = ballSpeed * normalizedVector(reflectionVector(m_velocity, {-1, 0}));
            m_circle.setPosition(screenWidth - ballRadius - 0.1f, m_circle.getPosition().y);
        }
        if (m_nextPos.y <= ballRadius) {
            m_velocity = ballSpeed * normalizedVector(reflectionVector(m_velocity, {0, 1}));
            m_circle.setPosition(m_circle.getPosition().x, ballRadius + 0.1f);
        }
    }

    void Ball::hitPlatform(const sf::RectangleShape& platform) {
        if (m_circle.getGlobalBounds().intersects(platform.getGlobalBounds()) && m_velocity.y > 0) {
            m_velocity = ballSpeed * normalizedVector(reflectionVector(m_velocity, {0, -1}));

            float offset = (m_circle.getPosition().x - platform.getPosition().x) / (platformWidth / 2.f);
            m_velocity.x += offset * 150.f;
            m_velocity = (m_velocity / magnitude(m_velocity)) * ballSpeed;

            float platformTop = platform.getPosition().y;
            m_circle.setPosition(m_circle.getPosition().x, platformTop - ballRadius - 0.1f);  // push above surface
        }
    }

    int Ball::hitBottom() {
        if (m_nextPos.y > screenHeight + ballRadius) {
            return deadBall;
        }
        return success;
    }

    int Ball::hitBlock(std::vector<Block>& blocks) {
        for (size_t i = 0; i < blocks.size(); ++i) {
            auto& block = blocks[i];
            sf::FloatRect b = block.getRect().getGlobalBounds();

            // 1) Find closest point on block to the *future* circle center
            float left   = b.left;
            float right  = b.left + b.width;
            float top    = b.top;
            float bottom = b.top  + b.height;

            float closestX = std::max(left,  std::min(m_nextPos.x, right));
            float closestY = std::max(top,   std::min(m_nextPos.y, bottom));

            // 2) Compute vector from closest point back to circle center
            float dx = m_nextPos.x - closestX;
            float dy = m_nextPos.y - closestY;
            float dist2 = dx*dx + dy*dy;

            // 3) Test intersection (squared)
            if (dist2 <= ballRadius * ballRadius) {
                // 4) Build collision normal
                float dist = std::sqrt(dist2);
                sf::Vector2f normal;
                normal = { dx / dist, dy / dist };

                // 5) Reflect velocity
                m_velocity = ballSpeed * normalizedVector(reflectionVector(m_velocity, normal));

                // Add side‐offset when hitting top/bottom
                if (std::abs(normal.y) > 0.5f) {
                    float offset = (m_nextPos.x - block.getRect().getPosition().x) / (blockWidth / 2.f);
                    m_velocity.x += offset * 100.f;
                    m_velocity = (m_velocity / magnitude(m_velocity)) * ballSpeed;
                }

                // 6) Snap ball *outside* the block
                sf::Vector2f contact{ closestX, closestY };
                m_circle.setPosition(contact + normal * (ballRadius + 0.1f));

                return i;
            }
        }
        return success;
    }

    int Ball::move(const sf::RectangleShape& platform, std::vector<Block>& blocks, const float dt) {
        m_nextPos = m_circle.getPosition() + m_velocity * dt;

        hitWall();
        hitPlatform(platform);
        int blockIndex = hitBlock(blocks);
        if (blockIndex != success)
            return blockIndex;

        if (hitBottom() == deadBall)
            return deadBall;

        // Move with the updated velocity
        m_circle.setPosition(m_circle.getPosition() + m_velocity * dt);
        return success;
    };
}