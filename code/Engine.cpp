#include "Engine.h"

Engine::Engine() {
    m_Window.create(VideoMode::getDesktopMode(), "Particles");
}

void Engine::run() {
    Clock clock1;
    clock1.getElapsedTime();
    Time time;

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while(m_Window.isOpen()){
        time = clock1.restart();
        input();
        update(time.asSeconds());
        draw();
    }
}

void Engine::input()
{
    Event event;
    Vector2i mouseLocation;
    while (m_Window.pollEvent(event)) {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            m_Window.close();
        }
        if (event.type == sf::Event::Closed) m_Window.close();
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                mouseLocation = Mouse::getPosition();

                //create loop to construct particles
                for (int i = 0; i < 5; i++)
                {
                    int numPoints = rand() % 26 + 25;
                    Particle mainP(m_Window, numPoints, mouseLocation);
                }
                cout << "the left button was pressed" << endl;
            }
        }
    }
}


//ttl means time to live
void Engine::update(float dsAsSeconds) {
    int x = 0;
    for (Particle currParticle : m_particles){
        if (currParticle.getTTL() > 0.0)
        {
            currParticle.update(dsAsSeconds);
            x++;
            currParticle = m_particles[x];
        }
        else
        {
            m_particles.erase(m_particles.begin() + x);
            if (x < m_particles.size())
            {
                currParticle = m_particles[x];
            }
        }
    }
}

void Engine::draw()
{
    m_Window.clear();

    for (Particle currParticle : m_particles)
    {
        m_Window.draw(currParticle);
    }

    m_Window.display();
}
