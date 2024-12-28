
#include "Game.h"
#include "Camera.h"
#include "Renderer.h"


int main()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(1020, 500), "Super Mario!");
   
    // Create the renderer
    Renderer renderer(window);


    // Clock for frame timing
    sf::Clock deltaClock;

    window.setFramerateLimit(60); //Shouldnt go below 60 for 2d games
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
        window.clear();

        // Apply the camera's view to the window
        window.setView(camera.GetView(window.getSize()));

        // Render the scene
        Render(renderer);
        window.setView(camera.GetUIView());
        RenderUI(renderer);

 

       

        // Display the rendered frame
        window.display();
    }

    return 0;
}
