export module fps;

#include <GLFW/glfw3.h>
import <iostream>;

export class FpsCounter {
	double previousTime = glfwGetTime();
	int frameCount = 0;
    public:

        FpsCounter() {
            glfwSwapInterval(0);
        }
	    void Update() {
            // Measure speed
            double currentTime = glfwGetTime();
            frameCount++;
            // If a second has passed.
            if (currentTime - previousTime >= 1.0)
            {
                // Display the frame count here any way you want.
                std::cout << frameCount << std::endl;

                frameCount = 0;
                previousTime = currentTime;
            }
	    }
		

	
};