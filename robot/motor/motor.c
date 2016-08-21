#include "ch.h"
#include "motor.h"
#include "driving.h"
#include "common.h"
#include "string.h"


MotorObj M[8] = {{.id=0},{.id=1},{.id=2},
                 {.id=3},{.id=4},{.id=5},
                 {.id=6},{.id=7}};

const motor_setting_t DefaultIdle = {
    .Mode = motor_idle,
    .ScaleFactor = 1.0,
    .AccelerationLimit = 1,
    .SpeedLimit = 600,
    .CommandCycle = 4000,
    .MotorVoltage = 12000,
    .CurrentLimit = 1000,
    .kP = 0,
    .kI = 0,
    .kD = 0,
    .kFF = 0
};

const motor_setting_t DefaultBrake = {
    .Mode = motor_brake,
    .ScaleFactor = 1.0,
    .AccelerationLimit = 1,
    .SpeedLimit = 600,
    .CommandCycle = 4000,
    .MotorVoltage = 12000,
    .CurrentLimit = 1000,
    .kP = 0,
    .kI = 0,
    .kD = 0,
    .kFF = 0
};

const motor_setting_t DefaultVMode = {
    .Mode = motor_Vmode,
    .ScaleFactor = 1.0,
    .AccelerationLimit = 3,
    .SpeedLimit = 600,
    .CommandCycle = 4000,
    .MotorVoltage = 12000,
    .CurrentLimit = 1000,
    .kP = 500,
    .kI = 1,
    .kD = 1,
    .kFF = 0
};

const motor_setting_t DefaultPMode = {
    .Mode = motor_Pmode,
    .ScaleFactor = 10.0,
    .AccelerationLimit = 200,
    .SpeedLimit = 4000,
    .CommandCycle = 4000,
    .MotorVoltage = 12000,
    .CurrentLimit = 1000,
    .kP = 200,
    .kI = 1,
    .kD = 40,
    .kFF = 0
};

const motor_setting_t M0VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,                       //3000
 .kI = 700,                         //1600
 .kD = 50,                       //50
 .kFF = 1500             //1815
};

const motor_setting_t M1VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,
 .kI = 700,
 .kD = 50,
 .kFF = 1500             //1800
};

const motor_setting_t M2VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP =2000,
 .kI = 700,
 .kD = 50,
 .kFF = 1500             //1800
};

const motor_setting_t M3VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,
 .kI = 700,
 .kD = 50,
 .kFF = 1500,                //1685
};

const motor_setting_t M4VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,
 .kI = 800,
 .kD = 50,
 .kFF = 1000
};

const motor_setting_t M5VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,
 .kI = 900,
 .kD = 0,
 .kFF = 1000
};

const motor_setting_t M6VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,
 .kI = 900,
 .kD = 0,
 .kFF = 1000,
};

const motor_setting_t M7VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 14000,
 .kP = 2000,
 .kI = 800,
 .kD = 0,
 .kFF = 2000,
};

void motor_init(MotorObj *motor, const motor_setting_t *cfg) {
  motor->Setting = *cfg;
}

umd_return_e motor_send_setpoint(MotorObj *motor){
  UMD_Obj_t object;
  if(motor->Setting.Mode == motor_Vmode)
    object.id = CAL_ID_VMODE(motor->id);
  if(motor->Setting.Mode == motor_Pmode)
    object.id = CAL_ID_PMODE(motor->id);
  object.tx_data = (uint8_t*)&(motor->SetPoint);
  object.rx_data = (uint8_t*)&(motor->Feedback);
  object.tx_len = 2;
  object.rx_len = 2;
  object.rx_callback = NULL;
  object.tx_callback = NULL;
  return UMD_Poll_Single(&object);
}

//<<<<<<< HEAD
//udc_rx_state_e motor_get_status(MotorObj *motor){
//  UDC_Obj_t udc_object;
//  udc_object.id = CAL_ID_M_STATUS(motor->id);
//  udc_object.rx_data = (udc_rx_data_t)&(motor->Board);
//  udc_object.tx_len = 0;
//  udc_object.rx_len = 14;
//  udc_object.rx_callback = NULL;
//  return UDC_Poll_Single(&udc_object);
//=======
umd_return_e motor_get_status(MotorObj *motor){
  UMD_Obj_t object;
  object.id = CAL_ID_M_STATUS(motor->id);
  object.rx_data = (uint8_t*)&(motor->Board);
  object.tx_len = 0;
  object.rx_len = 14;
  object.rx_callback = NULL;
  object.tx_callback = NULL;
  return UMD_Poll_Single(&object);
//>>>>>>> b1ab300e10eec07a0da4c8f514d46b53bed302ea
}

umd_return_e motor_send_setting(MotorObj *motor){
  UMD_Obj_t object;
  object.id = CAL_ID_M_SETTING(motor->id);
  object.tx_data = (uint8_t*)&(motor->Setting);
  object.tx_len = 24;
  object.rx_len = 0;
  object.rx_callback = NULL;
  object.tx_callback = NULL;
  return UMD_Poll_Single(&object);
}

umd_return_e motor_setIdle(MotorObj *motor){
  UMD_Obj_t object;
  motor_setting_t setting;
  memcpy(&setting, &(motor->SetPoint), sizeof(motor_setting_t));
  setting.Mode = motor_idle;
  object.id = CAL_ID_M_SETTING(motor->id);
  object.tx_data = (uint8_t*)&setting;
  object.tx_len = 24;
  object.rx_len = 0;
  object.rx_callback = NULL;
  object.tx_callback = NULL;
  return UMD_Poll_Single(&object);
}

umd_return_e motor_setBrake(MotorObj *motor){
  UMD_Obj_t object;
  object.id = CAL_ID_M_SETTING(motor->id);
  object.tx_data = (uint8_t*)&DefaultBrake;
  object.tx_len = 24;
  object.rx_len = 0;
  object.rx_callback = NULL;
  object.tx_callback = NULL;
  return UMD_Poll_Single(&object);
}

void motor_setAlive(void * arg){
     MotorObj * motor = (MotorObj *) arg;
     motor->timeout = 3;
}

void motor_decAlive(void * arg){
     MotorObj * motor = (MotorObj *) arg;
     if ((motor->timeout) >0)
         (motor->timeout)--;
}

