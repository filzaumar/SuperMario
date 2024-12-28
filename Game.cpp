#include "Game.h"
#include "Animation.h"

Map map(1.0f); //map with cell size 
Camera camera(15.625f); // Create the camera with a zoom level
Mario mario;
std::vector<Object*>objects{};
sf::Text coinText("Coins", font);
sf::Text gameOverText("GAME\nOVER!", font);
sf::Text winText("YOU\nWIN!", font);
sf::Font font;

void Begin()
{

    // Load the texture
    for (auto& file : std::filesystem::directory_iterator("./resources/textures/"))
    {
        if (file.is_regular_file() && file.path().extension() == ".png" || file.path().extension()==".jpg")
        {
            Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
            if (!Resources::textures[file.path().filename().string()].loadFromFile(file.path().string())) {
                std::cout << "Failed to load texture: " << file.path().filename() << std::endl;
            }
            else {
                std::cout << "Successfully loaded texture: " << file.path().filename() << std::endl;
                std::cout << mario.position.x  << mario.position.y<< std::endl;
            }
        }
    }

 

    // Initialize text properties
    if (!font.loadFromFile("resources/font/PixelOperator.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    coinText.setFont(font);
    coinText.setFillColor(sf::Color::White);
    coinText.setOutlineColor(sf::Color::Black);
    coinText.setOutlineThickness(1.0f);
    coinText.setScale(0.1f, 0.1f);

    gameOverText.setFont(font);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(1.0f);
    gameOverText.setScale(0.1f, 0.1f);
   
    winText.setFont(font);
    winText.setFillColor(sf::Color::Yellow);
    winText.setOutlineColor(sf::Color::Black);
    winText.setOutlineThickness(1.0f);
    winText.setScale(0.1f, 0.1f);

    //Phisics Init() after loading resources
    Physics::Init();

    sf::Image image;
    image.loadFromFile("resources/image/map.png");
    
    

    mario.position = map.InitFromImage(image, objects);
    {
        std::cout << "maarioooo" << mario.position.x << mario.position.y << std::endl;
    }
    mario.Begin();
    for (auto& object : objects)
    {
        object->Begin();
    }


}

void Update(float deltaTime)
{
    Physics::Update(deltaTime);
    mario.Update(deltaTime, objects);
    for (auto& object : objects)
    {
        object->Update(deltaTime);
    }

    camera.position = mario.position;   
}

void Render(Renderer& renderer)
{
    renderer.Draw(Resources::textures["sky.jpg"], camera.position, camera.GetViewSize());
    map.Draw(renderer);
    mario.Draw(renderer);

    for (auto& object : objects)
    {
        object->Render(renderer);
    }
       
    Physics::DebugDraw(renderer);
}

void RenderUI(Renderer& renderer)
{
    coinText.setPosition(-camera.GetViewSize() /2.0f + sf::Vector2f(2.0f,1.0f));
    coinText.setString("Coins: " + std::to_string(mario.getCoinCount()));
    renderer.target.draw(coinText);

    if (mario.isDead) {
        // Rendering game-over text
        std::cout << "Before updating position: "
            << gameOverText.getPosition().x << ", "
            << gameOverText.getPosition().y << std::endl;
        gameOverText.setCharacterSize(200.0f);
        sf::FloatRect textBounds = gameOverText.getLocalBounds();
        sf::Vector2f viewCenter = -camera.GetViewSize() / 2.0f + camera.GetViewSize() / 2.0f;

        float xPos = viewCenter.x - (textBounds.width * gameOverText.getScale().x) / 2.0f;
        float yPos = viewCenter.y - (textBounds.height * gameOverText.getScale().y) / 2.0f;

        gameOverText.setPosition(xPos, yPos - 8.0f);
        std::cout << "After updating position: "
            << gameOverText.getPosition().x << ", "
            << gameOverText.getPosition().y << std::endl;
        renderer.target.draw(gameOverText);
    }
    else if (mario.getCoinCount() == 28) {
        // Rendering win text
        winText.setCharacterSize(200.0f);
        sf::FloatRect textBounds = winText.getLocalBounds();
        sf::Vector2f viewCenter = -camera.GetViewSize() / 2.0f + camera.GetViewSize() / 2.0f;

        float xPos = viewCenter.x - (textBounds.width * winText.getScale().x) / 2.0f;
        float yPos = viewCenter.y - (textBounds.height * winText.getScale().y) / 2.0f;

        winText.setPosition(xPos, yPos - 8.0f);
        renderer.target.draw(winText);
    }
}
