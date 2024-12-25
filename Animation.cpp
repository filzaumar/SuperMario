#include "Animation.h"
void Animation::Update(float deltaTime)
{
    time += deltaTime;
    //std::cout << "Animation time: " << time << "/" << length << std::endl;
}

sf::Texture Animation::GetTexture()
{
        // Reset time if it's over the length of the animation
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
                // If it's the first frame, return the first texture
                if (i == 0) {
                    return frames[0].texture;
                }
                else {
                    // Return the texture of the previous frame
                    return frames[i - 1].texture;
                }
            }
        }

        // If time is equal to or exceeds the length of the animation, return the last frame
        return frames.back().texture;

        // Error Handling
        throw std::runtime_error("No valid texture found for animation frame.");
    

   /* if (frames.empty()) {
            std::cerr << "Error: Animation has no frames." << std::endl;
            return sf::Texture();
        }
        for (const auto& frame : frames) {
            if (time >= frame.time) {
                std::cout << "Returning texture with size: "
                    << frame.texture.getSize().x << " "
                    << frame.texture.getSize().y << std::endl;
                return frame.texture;
            }
        }
        return frames.front().texture;
    */
    }

    