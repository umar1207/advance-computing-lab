#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;

// Global semaphore to control access to chopsticks
sem_t* globalSemaphore;
sem_t* chopsticks;

int main() {
    const char* semaphoreNames[5] = {"chopstick01", "chopstick11", "chopstick21", "chopstick31", "chopstick41"};

    // Create a global semaphore
    globalSemaphore = sem_open("/globalSemaphore", O_CREAT | O_EXCL, 0666, 1);
    if (globalSemaphore == SEM_FAILED) {
        cout << "NOT ABLE TO CREATE THE GLOBAL SEMAPHORE\n";
        return 1;
    }

    chopsticks = sem_open("/chopsticks", O_CREAT | O_EXCL, 0666, 5);
    if (chopsticks == SEM_FAILED) {
        cout << "NOT ABLE TO CREATE THE CHOPSTICKS SEMAPHORE\n";
        return 1;
    }

    for (int i = 0; i < 5; ++i) {
        pid_t p = fork();
        if (p == -1) {
            cout << "Not able to create child process\n";
            return 2;
        }
        if (p == 0) {
            int t = 2;
            while (t--) {
                cout << "philosopher " << i << " is Thinking....\n";
                usleep(1000000);
                cout << "philosopher " << i << " is Hungry....\n";

                // Philosopher waits for access to globalSemaphore
                sem_wait(globalSemaphore);

                // Philosopher picks up both chopsticks
                sem_wait(chopsticks);
                cout << "Philosopher " << i << " picks up one chopstick\n";
                sem_wait(chopsticks);
                cout << "Philosopher " << i << " picks up another chopstick\n";

                cout << "Philosopher " << i << " is eating...\n";
                usleep(100000);

                // globalSemaphore released
                sem_post(globalSemaphore);

                // Philosopher puts down both chopsticks
                sem_post(chopsticks);
                cout << "Philospher " << i << " puts down one chopstick\n";
                sem_post(chopsticks);
                cout << "Philospher " << i << " puts down another chopstick\n";

            }
            return 0;
        }
    }

    // parent waits for the child to finish
    for (int i = 0; i < 5; ++i) {
        wait(NULL);
    }

    // Cleanup (closing and unlinking semaphores)
 
    if (sem_close(chopsticks) == -1) {
        cout << "not properly closed\n";
    }
    if (sem_unlink("/chopsticks") == -1) {
        cout << "not properly unlinked\n";
    }

    // // Close and unlink the global semaphore
    if (sem_close(globalSemaphore) == -1) {
        cout << "not properly closed\n";
    }
    if (sem_unlink("/globalSemaphore") == -1) {
        cout << "not properly unlinked\n";
    }

    return 0;
}