#include "Engine.h";
using namespace std;
using namespace sf;

Engine::Engine() 
{
    m_Window.create(VideoMode::getDesktopMode(), "Particles");
}