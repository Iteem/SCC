#include "player.h"

const float Speed = 100.f; //pixel per second

Player::Player() :
timer(0)
{
    bubbleImage.LoadFromFile("data/bubble.png");
    bubble.SetImage(bubbleImage);
    bubble.Resize(80, 80);
    bubble.SetOrigin(bubbleImage.GetWidth() / 2, bubbleImage.GetHeight() / 2);
    bubble.SetPosition(400, 200);
}

void Player::update(float elapsedTime, float mouseX)
{
    //for a minimal and soft up and down of the bubble
    timer += 4 * elapsedTime;
    timer = timer - (static_cast<int>(timer) / 8) * 8;

    float tmp;
    if(timer < 4)
    {
        tmp = timer - 2;
        tmp *= tmp;
        tmp -= 4;
    }
    else
    {
        tmp = timer - 6;
        tmp *= -tmp;
        tmp += 4;
    }

    bubble.SetY(tmp + 200);

    //move bubble
    tmp = mouseX - bubble.GetPosition().x;
    if(tmp > Speed  * elapsedTime)
        tmp = Speed  * elapsedTime;
    else if(tmp < -Speed  * elapsedTime)
        tmp = -Speed  * elapsedTime;
    bubble.Move(tmp, 0);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(bubble);
}
