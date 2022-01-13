long startTime;
long stepTime;
long stepTimePrev;

long callInterval = (long)1e8; // nanoseconds

void initTimers() {
  startTime = System.nanoTime();
  stepTimePrev = startTime;
  stepTime = startTime;
}