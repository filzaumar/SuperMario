
#include "Game.h"
#include "Camera.h"
#include "Renderer.h"


int main()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(1020, 500), "Super Mario!");

    // Create the renderer
    Renderer renderer(window);

    // Create the camera with a zoom level
    Camera camera(100.f);

    // Clock for frame timing
    sf::Clock deltaClock;

    // Initialize game resources
    Begin();

    // Main game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update game state
        float deltaTime = deltaClock.restart().asSeconds();
        Update(deltaTime);

        // Apply the camera's view to the window
        window.setView(camera.GetView(window.getSize()));

        // Clear the window
        window.clear(sf::Color::Black);

        // Render the scene
        Render(renderer);

        // Display the rendered frame
        window.display();
    }

    return 0;
}
