#pragma once

class Component
{
private:
	virtual void Collide() {}
	virtual void Render() {}


};

class Collider : public Component
{
	

};

class Renderer : public Component
{


};

