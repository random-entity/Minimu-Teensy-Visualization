long startTime;
long stepTime;

long callInterval = (long)1e8; // nanoseconds

float getStepTimeInSec() {
  return (stepTime - startTime) * 1e-9;
}

void initTimers() {
  startTime = System.nanoTime();
  stepTime = startTime;
}
