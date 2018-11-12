#ifdef USES_P255
// #############################################################################
// ################### Plugin 255: Set System Time ########################
// #############################################################################

#define PLUGIN_255
#define PLUGIN_ID_255         255
#define PLUGIN_NAME_255       "Time - System Time [TESTING]"

#define PLUGIN_VALUENAME1_255 "System Time"
#define PLUGIN_255_EXPRESSION_SIZE	32

// A plugin has to implement the following function

boolean Plugin_255(byte function, struct EventStruct *event, String &string) {
  switch (function) {
    case PLUGIN_DEVICE_ADD: {
      // This case defines the device characteristics, edit appropriately
      Device[++deviceCount].Number = PLUGIN_ID_255;
      Device[deviceCount].Type = DEVICE_TYPE_DUMMY;  // how the device is connected
      Device[deviceCount].VType = SENSOR_TYPE_NONE;  // type of value the plugin will return, used only
                             // for Domoticz
      Device[deviceCount].Ports = 0;
      Device[deviceCount].PullUpOption = false;
      Device[deviceCount].InverseLogicOption = false;
      Device[deviceCount].FormulaOption = false;
      Device[deviceCount].ValueCount = 1;  // number of output variables. The value should match the number
              // of keys PLUGIN_VALUENAME1_xxx
      Device[deviceCount].SendDataOption = false;
      Device[deviceCount].TimerOption = false;
      Device[deviceCount].TimerOptional = false;
      Device[deviceCount].GlobalSyncOption = true;
      Device[deviceCount].DecimalsOnly = true;
      return true;
    }

    case PLUGIN_GET_DEVICENAME: {
      // return the device name
      string = F(PLUGIN_NAME_255);
      return true;
    }

    case PLUGIN_GET_DEVICEVALUENAMES: {
      // called when the user opens the module configuration page
      // it allows to add a new row for each output variable of the plugin
      strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_255));
      return true;
    }

    case PLUGIN_WEBFORM_LOAD: {
      char unix_time[PLUGIN_255_EXPRESSION_SIZE];
      LoadCustomTaskSettings(event->TaskIndex, (byte *)&unix_time, PLUGIN_255_EXPRESSION_SIZE);
      addFormTextBox(F("Unix time"), F("p255_unix_time"), unix_time, 39);
      return true;
    }

    case PLUGIN_WEBFORM_SAVE: {
      String log;
      char unix_time[PLUGIN_255_EXPRESSION_SIZE];
      strncpy(unix_time, WebServer.arg(F("p255_unix_time")).c_str(), sizeof(unix_time));
      long utime = atol(unix_time);
      if (utime != 0) {
        sysTime = utime;
        Serial.print(F("Set Time:"));
        Serial.println(sysTime);
      } else {
        log = String(F("Unix Time Expression: Error "));
        addHtmlError(log);
        addLog(LOG_LEVEL_ERROR, log);
      }

      return true;
    }

    case PLUGIN_WEBFORM_SHOW_VALUES: {
      return true;
    }

    case PLUGIN_INIT: {
      // this case defines code to be executed when the plugin is initialised
      // after the plugin has been initialised successfuly, set success and
      // break
      return true;
    }

    case PLUGIN_READ: {
      return false;
    }

    case PLUGIN_WRITE: {
      return false;
    }

    case PLUGIN_EXIT: {
      // perform cleanup tasks here. For example, free memory
      return true;
    }

    case PLUGIN_TIME_CHANGE:
    case PLUGIN_ONCE_A_SECOND: {
      // code to be executed once a second. Tasks which do not require fast
      // response can be added here
      String log;
      unsigned long time __attribute__((unused)) = now();

      if (time % 10 == 0) {
        Serial.print(F("Current Time:"));
        Serial.println(sysTime);
      }

      return true;
    }

    case PLUGIN_TEN_PER_SECOND: {
      // code to be executed 10 times per second. Tasks which require fast
      // response can be added here be careful on what is added here. Heavy
      // processing will result in slowing the module down!

      return true;
    }

  }  // switch

  return false;
}  // function

#endif  // USES_P255
