export module fps;

#include <GLFW/glfw3.h>
import <iostream>;

export class FpsCounter {
    public:

        FpsCounter() {
            glfwSwapInterval(0);
        }
	    void update() {
            // Measure speed
            double currentTime = glfwGetTime();

            // Update Delta Time
            m_deltaTime = currentTime - m_lastFrame;
            m_lastFrame = currentTime;

            m_frameCount++;
            // If a second has passed.
            if (currentTime - m_previousTime >= 1.0)
            {
                // Display the frame count here any way you want.
                std::cout << "FPS: " << m_frameCount << std::endl;

                m_frameCount = 0;
                m_previousTime = currentTime;
            }
	    }

        float getDeltaTime() const { 
            return m_deltaTime;
        }

    private:
        double m_previousTime = glfwGetTime();
        int m_frameCount = 0;

        float m_deltaTime = 0.0f;	// Time between current frame and last frame
        float m_lastFrame = 0.0f; // Time of last frame
		

	
};