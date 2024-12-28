#include "Animation.h"
void Animation::Update(float deltaTime)
{
    time += deltaTime;
    //std::cout << "Animation time: " << time << "/" << length << std::endl;
}

sf::Texture Animation::GetTexture()
{
        // Reset time if its over the length of the animation
        while (time > length) {
            time -= length;
        }

        // If there are no frames, throw an error
        if (frames.empty()) {
            throw std::runtime_error("No frames in animation");
        }


        float currentCumulativeTime = 0;
        for (size_t i = 0; i < frames.size(); ++i) {
            currentCumulativeTime += frames[i].time;
            if (time < currentCumulativeTime) {
                // Return the current frame's texture
                return frames[i].texture;
            }
        }

        // If time is equal to or exceeds the length of the animation, return the last frame
        return frames.back().texture;

    
        throw std::runtime_error("No valid texture found for animation frame.");
    
    }

    