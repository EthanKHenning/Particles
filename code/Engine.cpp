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

void Engine::input()
{
    Event event;
    Vector2i mouseLocation;
    while (m_Window.pollEvent(event))
        {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            m_Window.close();
        }
            if (event.type == sf::Event::Closed) m_Window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    //create loop to construct particles 
                    cout << "the left button was pressed" << endl;

                    //veryComplex.setCenter(clickPos);
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                mouseLocation = {event.mouseMove.x, event.mouseMove.y};

                //veryComplex.setMouseLocation(mouseLocation);
            }
        }

}
