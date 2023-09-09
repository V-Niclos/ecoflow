#ifndef MAINSETUPTASKS_H
#define MAINSETUPTASKS_H

#include "mainTaskNetTime.h"
#include "mainTaskRelays.h"
void fncMainSetupTask()
{
  //Serial.println("fncSetupTask ");
                      /* pin task to core 0 */

  /* pin task to core 1 */

  xTaskCreatePinnedToCore(
      g_MainTaskNetTime,     /* Task function. */
      "g_MainTaskNetTime", /* name of task. */
      10000,                        /* Stack size of task */
      NULL,                         /* parameter of the task */
      1,                            /* priority of the task */
      &g_MainTaskNetTimeHandle,  /* Task handle to keep track of created task */
      1);                           /* pin task to core 1 */

  xTaskCreatePinnedToCore(
      g_MainTaskRelays,     /* Task function. */
      "g_MainTaskRelays", /* name of task. */
      10000,                       /* Stack size of task */
      NULL,                        /* parameter of the task */
      1,                           /* priority of the task */
      &g_MainTaskRelaysHandle,  /* Task handle to keep track of created task */
      1);                          /* pin task to core 1 */
                                   /* pin task to core 1 */
}

#endif