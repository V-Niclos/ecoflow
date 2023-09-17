#include <unity.h>
#include <Arduino.h>
#include <ClsRelayOnOff.h>
#include <Debug.h>


void test_relays();

int main( int argc, char **argv)  {
   UNITY_BEGIN();

   test_relays();
   UNITY_END();
}