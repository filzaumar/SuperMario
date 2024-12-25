#include "Game.h"
#include "Animation.h"

Map map(1.0f); //map with cell size 
Camera camera(15.625f); // Create the camera with a zoom level
Mario mario;
int score = 0;
std::vector<Object*>objects{};

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
    map.Draw(renderer);
    mario.Draw(renderer);

    for (auto& object : objects)
    {
        object->Render(renderer);
    }
    
    Physics::DebugDraw(renderer);
}