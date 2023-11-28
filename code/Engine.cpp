#include "Engine.h";

Engine::Engine() {
    m_Window.create(VideoMode::getDesktopMode(), "Particles");
}

void Engine::run() {
    Clock time;
    time.getElapsedTime();

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while(m_Window.isOpen()){
        time.restart();
        Engine::input();
        Engine::update;
        Engine::draw();
    }
}