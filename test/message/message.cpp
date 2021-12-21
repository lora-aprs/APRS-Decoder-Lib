#include <Path.h>
#include <unity.h>

#ifdef NATIVE
int main(int argc, char **argv)
#else
void setup()
#endif
{
  UNITY_BEGIN();
  UNITY_END();
}

void loop() {
}
