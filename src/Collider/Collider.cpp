#include "Collider.hpp"  
	
Collider::Collider()
{

}

Collider::Collider(int x, int y, int w, int h)
{
	mCollisionRect = {x,y,w,h};
}
	
Collider::~Collider()
{
	
}

bool Collider::isColliding(SDL_Rect& otherRect) 
{
   
    bool isColliding = true;

    const SDL_Rect& self = mCollisionRect;

    int leftSelf = self.x;
    int rightSelf = self.x + self.w;
    int upperSelf = self.y;
    int lowerSelf = self.y + self.h;

    int leftOther = otherRect.x;
    int rightOther = otherRect.x + otherRect.w;
    int upperOther = otherRect.y;
    int lowerOther = otherRect.y + otherRect.h;

    
    // if any of the axes is not touching
    
    // no overlap on x
    if(leftSelf >= rightOther || rightSelf <= leftOther)
    {
        isColliding = false;
    }

    // no overlap on y
    if(upperSelf >= lowerOther || lowerSelf <= upperOther)
    {
        isColliding = false;
    }



    return isColliding;
}

void Collider::setCollisionRect(SDL_Rect& rect) 
{

    mCollisionRect = {rect.x, rect.y, rect.w, rect.h };
    

}